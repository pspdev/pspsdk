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
#include <unistd.h>
#include <string.h>
#include <sys/param.h>

#include <pspuser.h>

void __init_cwd(char *argv_0);
void __timezone_update();
void __fdman_init();
void __init_mutex();
void pthread_init();
void __psp_free_heap();
void __deinit_mutex();
void __locks_init();
void __locks_deinit();

extern int sce_newlib_nocreate_thread_in_start __attribute__((weak));

#if defined(F___libpthreadglue_init) && !defined(PSP_WITHOUT_PTHREAD)
/* Note: This function is being called from __libcglue_init.
* It is a weak function because can be override by user program
*/
__attribute__((weak))
void __libpthreadglue_init()
{
    pthread_init();
}
#elif defined(PSP_WITHOUT_PTHREAD)
#define __libpthreadglue_init() do{}while(0)
#else
void __libpthreadglue_init();
#endif

#ifdef F___libcglue_init
/* Note: This function is being called from crt0.c/crt0_prx.c.
* It is a weak function because can be override by user program, 
* saving a lot of space in your binary, however you will loose
  all the basic libc operation
*/
__attribute__((weak))
void __libcglue_init(int argc, char *argv[])
{
    (void) argc;
    /* Initialize lock API */
	__locks_init();

    /* Initialize mutex used in malloc and fdman */
    __init_mutex();

	/* Initialize filedescriptor management */
	__fdman_init();

	/* Initialize pthread library */
	__libpthreadglue_init();

	/* Initialize cwd from this program's path */
	__init_cwd(argv[0]);

	/* Initialize timezone */
	__timezone_update();
}
#endif

#ifdef F___libcglue_deinit
/* Note: This function is being called from terminate.c.
* It is a weak function because can be override by user program
*/
__attribute__((weak))
void __libcglue_deinit()
{
    __psp_free_heap();
	__deinit_mutex();
	__locks_deinit();
}
#else
void __libcglue_deinit();
#endif

#ifdef F__exit
__attribute__((__noreturn__))
void _exit (int __status)
{
	__libcglue_deinit();

	if (&sce_newlib_nocreate_thread_in_start != NULL) {
		sceKernelSelfStopUnloadModule(1, 0, NULL);
	} else {
		sceKernelExitGame();
	}
	
	while (1); // Avoid warning
}
#else
__attribute__((__noreturn__))
void _exit (int __status);
#endif

#ifdef F_abort
__attribute__((weak))
void abort()
{
	_exit(1);
}
#endif

#ifdef F_exit
__attribute__((weak))
void exit(int retval)
{
	_exit(retval);
}
#endif
