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
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pspthreadman.h>

#ifdef F___sbrk_mutex
SceLwMutexWorkarea __sbrk_mutex;
#else
extern SceLwMutexWorkarea __sbrk_mutex;
#endif

#ifdef F___fdman_mutex
SceLwMutexWorkarea __fdman_mutex;
#else
extern SceLwMutexWorkarea __fdman_mutex;
#endif

#ifdef F___init_mutex
/* Create mutex used for making thread safe mallock and get fd */
void __init_mutex()
{
	sceKernelCreateLwMutex(&__sbrk_mutex, "sbrk mutex", 0, 0, 0);
	sceKernelCreateLwMutex(&__fdman_mutex, "fdman mutex", 0, 0, 0);
}
#endif

#ifdef F___deinit_mutex
/* Create mutex used for making thread safe mallock and get fd */
void __deinit_mutex()
{
	sceKernelDeleteLwMutex(&__sbrk_mutex);
	sceKernelDeleteLwMutex(&__fdman_mutex);
}
#endif