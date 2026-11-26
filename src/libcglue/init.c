/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * init.c - The global init/deinit code for our crt0.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2021 Francisco Javier Trujillo Mata <fjtrujy@gmail.com>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/param.h>

#include <pspuser.h>

void __init_cwd(char *argv_0);
void __timezone_update();
void __fdman_init();
void __init_mutex();
int pthread_init(void);
void pthread_terminate(void);
void __psp_free_heap();
void __deinit_mutex();
void __locks_init();
void __locks_deinit();

#ifdef F___gprof_cleanup
/* Note: This function is being called from _exit and it is overrided when compiling with -pg */
__attribute__((weak))
void __gprof_cleanup() {}
#else
void __gprof_cleanup();
#endif

/* Optional profiler hook: stop the timer without dumping through stdio. */
extern void __gprof_abort(void) __attribute__((weak));

#if defined(F___libpthreadglue_init) && !defined(PSP_WITHOUT_PTHREAD)
/* Note: This function is being called from __libcglue_init.
* It is a weak function because can be override by user program
*/
__attribute__((weak))
void __libpthreadglue_init()
{
    if (!pthread_init())
        _exit(EXIT_FAILURE);
}
#elif defined(PSP_WITHOUT_PTHREAD)
#define __libpthreadglue_init() do{}while(0)
#else
void __libpthreadglue_init();
#endif

#if defined(F___libpthreadglue_deinit) && !defined(PSP_WITHOUT_PTHREAD)
/* Match the initialization hook while keeping the heap and locks available. */
__attribute__((weak))
void __libpthreadglue_deinit(void)
{
    pthread_terminate();
}
#elif defined(PSP_WITHOUT_PTHREAD)
#define __libpthreadglue_deinit() do{}while(0)
#else
void __libpthreadglue_deinit(void);
#endif

#if defined(F___libpthreadglue_abort) && !defined(PSP_WITHOUT_PTHREAD)
/* The process is ending: release OSAL resources without user TLS destructors. */
extern void __pte_osExit(void);
__attribute__((weak))
void __libpthreadglue_abort(void)
{
    __pte_osExit();
}
#elif defined(PSP_WITHOUT_PTHREAD)
#define __libpthreadglue_abort() do{}while(0)
#else
void __libpthreadglue_abort(void);
#endif

#ifdef F___libcglue_init
extern void _fini(void);
extern int __pte_osCanTerminate(void) __attribute__((weak));
extern int __pte_osBeginTerminate(void) __attribute__((weak));
static SceUID runtime_thread;

/* A module cannot release memory or synchronization objects still in use. */
int __libcglue_can_deinit(void)
{
    return sceKernelGetThreadId() == runtime_thread &&
           (!__pte_osCanTerminate || __pte_osCanTerminate());
}

int __libcglue_begin_deinit(void)
{
    return sceKernelGetThreadId() == runtime_thread &&
           (!__pte_osBeginTerminate || __pte_osBeginTerminate());
}

static void __libcglue_profile_cleanup(void)
{
    if (__libcglue_can_deinit())
        __gprof_cleanup();
}

static int exit_initialized;

void __libcglue_exit(int status)
{
    if (exit_initialized)
        exit(status);
}

#ifndef PSP_WITHOUT_PTHREAD
static int pthread_active;

void __libcglue_pthread_cleanup(void)
{
    if (pthread_active && __libcglue_begin_deinit()) {
        pthread_active = 0;
        __libpthreadglue_deinit();
    }
}

void __libcglue_pthread_abort(void)
{
    if (pthread_active) {
        pthread_active = 0;
        __libpthreadglue_abort();
    }
}
#endif

/* Note: This function is being called from crt0.c/crt0_prx.c.
* It is a weak function because can be override by user program, 
* saving a lot of space in your binary, however you will loose
  all the basic libc operation
*/
__attribute__((weak))
void __libcglue_init(int argc, char *argv[])
{
    (void) argc;
    runtime_thread = sceKernelGetThreadId();
    /* Initialize lock API */
	__locks_init();

    /* Initialize mutex used in malloc and fdman */
    __init_mutex();

	/* Initialize filedescriptor management */
	__fdman_init();

	/* Initialize pthread library */
	__libpthreadglue_init();
#ifndef PSP_WITHOUT_PTHREAD
    /* Run TLS cleanup after C++ finalizers, while stdio and the heap live. */
    pthread_active = 1;
    if (atexit(__libcglue_pthread_cleanup) != 0)
        _exit(EXIT_FAILURE);
#endif

	/* Initialize cwd from this program's path */
	__init_cwd(argv[0]);

	/* Initialize timezone */
	__timezone_update();

    if (atexit(__libcglue_profile_cleanup) != 0 || atexit(_fini) != 0)
        _exit(EXIT_FAILURE);
    exit_initialized = 1;
}
#endif

#ifdef F___libcglue_deinit
extern void __libcglue_pthread_abort(void) __attribute__((weak));
/* Note: This function is being called from terminate.c.
* It is a weak function because can be override by user program
*/
__attribute__((weak))
void __libcglue_deinit()
{
    /* Normal exit has already dumped the profile and finalized pthreads.
       Immediate exit must not invoke application callbacks or reopen stdio. */
    if (__gprof_abort)
        __gprof_abort();
    if (__libcglue_pthread_abort) {
        __libcglue_pthread_abort();
    }

	__deinit_mutex();
	__locks_deinit();
    __psp_free_heap();
}
#else
void __libcglue_deinit();
#endif
