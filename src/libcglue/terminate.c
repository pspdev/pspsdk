/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * terminate.c - Process exit functions.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#include <stdio.h>
#include <psptypes.h>
#include <pspkernel.h>

#ifdef F__exit
extern int sce_newlib_nocreate_thread_in_start __attribute__((weak));

int __psp_free_heap(void);
void __deinit_mutex(void);

void _exit(int status)
{
	if (&sce_newlib_nocreate_thread_in_start != NULL) {
		/* Free the heap created by _sbrk(). */
		__psp_free_heap();
		__deinit_mutex();

		sceKernelSelfStopUnloadModule(1, 0, NULL);
	} else {
		if (status == 0) {
			/* Free the heap created by _sbrk(). */
			__psp_free_heap();
			__deinit_mutex();
		}

		sceKernelExitThread(status);
	}

	while (1) ;
}
#else
void _exit(int status);
#endif

#ifdef F_abort
__attribute__((weak))
void abort()
{
	while (1)
		_exit(1);
}
#endif

#ifdef F_exit
__attribute__((weak))
void exit(int retval)
{
	while (1)
		_exit(retval);
}
#endif
