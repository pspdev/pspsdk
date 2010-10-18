/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * libcglue.c - Newlib-compatible system calls.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Jim Paris <jim@jtan.com>
 *
 */
#include <errno.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/unistd.h>

#include <psptypes.h>
#include <pspiofilemgr.h>
#include <pspmodulemgr.h>
#include <pspsysmem.h>
#include <pspthreadman.h>
#include <psputils.h>

/* These functions aren't exposed in any public headers, and they probably don't need to be. */
int sceKernelStdin(void);
int sceKernelStdout(void);
int sceKernelStderr(void);

extern char * __psp_argv_0;
extern int __psp_cwd_initialized;
extern char __psp_cwd[MAXPATHLEN + 1];
extern void __psp_init_cwd(void);
extern int __psp_path_absolute(const char *in, char *out, int len);

/* If we're being built for PSPSDK's libc this function isn't defined. */
#ifdef F_glue_gettimeofday
int gettimeofday(struct timeval *tp, void *tzp)
{
	return sceKernelLibcGettimeofday(tp, tzp);
}
#endif

#if defined(F_clock) || defined(F_glue_clock)
clock_t clock(void)
{
	return sceKernelLibcClock();
}
#endif

#if defined(F_time) || defined(F_glue_time)
time_t time(time_t *t)
{
	return sceKernelLibcTime(t);
}
#endif

/* PSP-compatible sbrk(). */
#if defined(F__sbrk) || defined(F_glue__sbrk)

#define DEFAULT_PRX_HEAP_SIZE_KB 64

/* If defined it specifies the desired size of the heap, in KB. */
extern unsigned int sce_newlib_heap_kb_size __attribute__((weak));
extern int __pspsdk_is_prx __attribute__((weak));

/* UID of the memory block that represents the heap. */
static SceUID __psp_heap_blockid;

void * _sbrk(ptrdiff_t incr)
{
	static void * heap_bottom = NULL;
	static void * heap_top = NULL;
	static void * heap_ptr = NULL;

	/* Has our heap been initialized? */
	if (heap_bottom == NULL) {
		/* No, initialize the heap. */
		SceSize heap_size = (SceSize) -1;

		if (&sce_newlib_heap_kb_size != NULL) {
			heap_size = sce_newlib_heap_kb_size;
		} else if(&__pspsdk_is_prx != NULL) {
			heap_size = DEFAULT_PRX_HEAP_SIZE_KB;
		}

		if (heap_size == (unsigned int) -1) {
			heap_size = sceKernelMaxFreeMemSize();
		} else {
			heap_size *= 1024;
		}

		if (heap_size != 0) {
			__psp_heap_blockid = sceKernelAllocPartitionMemory(2, "block", PSP_SMEM_Low, heap_size, NULL);
			if (__psp_heap_blockid > 0) {
				heap_bottom = sceKernelGetBlockHeadAddr(__psp_heap_blockid);
				heap_ptr = heap_bottom;
				heap_top = (unsigned char *) heap_bottom + heap_size;
			}
		}
	}

	void * heap_addr = (void *) -1;
	void * next_heap_ptr = (void *) ((ptrdiff_t) heap_ptr + incr);
	if ((heap_bottom != NULL) && (next_heap_ptr >= heap_bottom) && (next_heap_ptr < heap_top)) {
		heap_addr = heap_ptr;
		heap_ptr = next_heap_ptr;
	}

	return heap_addr;
}

/* Free the heap. */
int __psp_free_heap(void)
{
	if (__psp_heap_blockid > 0) {
		return sceKernelFreePartitionMemory(__psp_heap_blockid);
	}

	return __psp_heap_blockid;
}
#endif

#if defined(F__exit) || defined(F_glue__exit)
extern int sce_newlib_nocreate_thread_in_start __attribute__((weak));

extern int __psp_free_heap(void);

void _exit(int status)
{
	if (&sce_newlib_nocreate_thread_in_start != NULL) {
		/* Free the heap created by _sbrk(). */
		__psp_free_heap();

		sceKernelSelfStopUnloadModule(1, 0, NULL);
	} else {
		if (status == 0) {
			/* Free the heap created by _sbrk(). */
			__psp_free_heap();
		}

		sceKernelExitThread(status);
	}

	while (1) ;
}
#endif

/* newlib's errno.h wants a function that returns a pointer to errno. */
#ifdef F_glue___errno
#undef errno

int errno;

/* TODO: Should this be made reentrant (wrapping interrupt disable/enable
   around it should do it)? */
int * __errno(void)
{
	return &errno;
}
#endif
