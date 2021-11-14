/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * fdman.c - Manager for fd.
 *
 * Copyright (c) 2021 Francisco Javier Trujillo Mata <fjtrujy@gmail.com>
 *
 */

#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <pspstdio.h>
#include <psptypes.h>
#include <pspsdk.h>

#include "fdman.h"

/* Functions from mutexman.c */
extern SceLwMutexWorkarea __fdman_mutex;

#ifdef F___descriptor_data_pool
__descriptormap_type  __descriptor_data_pool[__FILENO_MAX];
#else
extern __descriptormap_type  __descriptor_data_pool[__FILENO_MAX];
#endif

#ifdef F___descriptormap
__descriptormap_type *__descriptormap[__FILENO_MAX];
#else
extern __descriptormap_type *__descriptormap[__FILENO_MAX];
#endif


#ifdef F___fdman_init
void __fdman_init()
{
	int scefd;

	/* Initialize descriptor data*/
	memset(__descriptor_data_pool, 0, sizeof(__descriptormap_type) *__FILENO_MAX);
	/* Initialize descriptor map*/
	memset(__descriptormap, 0, sizeof(__descriptormap_type*)*__FILENO_MAX);

	scefd = sceKernelStdin();
	if (scefd >= 0) {
		__descriptormap[0] = &__descriptor_data_pool[0];
		__descriptormap[0]->descriptor = scefd;
		__descriptormap[0]->type = __DESCRIPTOR_TYPE_TTY;
	}
	scefd = sceKernelStdout();
	if (scefd >= 0) {
		__descriptormap[1] = &__descriptor_data_pool[1];
		__descriptormap[1]->descriptor = scefd;
		__descriptormap[1]->type = __DESCRIPTOR_TYPE_TTY;
	}
	scefd = sceKernelStderr();
	if (scefd >= 0) {
		__descriptormap[2] = &__descriptor_data_pool[2];
		__descriptormap[2]->descriptor = scefd;
		__descriptormap[2]->type = __DESCRIPTOR_TYPE_TTY;
	}
}
#endif


#ifdef F___fdman_get_new_descriptor
int __fdman_get_new_descriptor()
{
	int i = 0;

	sceKernelLockLwMutex(&__fdman_mutex, 1, 0); /* lock here to make thread safe */
	for (i = 0; i < __FILENO_MAX; i++) {
		if (__descriptormap[i] == NULL) {
			__descriptormap[i] = &__descriptor_data_pool[i];
			__descriptormap[i]->ref_count++;
			sceKernelUnlockLwMutex(&__fdman_mutex, 1);; /* release lock */
			return i;
		}
	}
	sceKernelUnlockLwMutex(&__fdman_mutex, 1);; /* release lock */
		
	errno = ENOMEM;
	return -1;
}
#endif


#ifdef F___fdman_get_dup_descriptor
int __fdman_get_dup_descriptor(int fd)
{
	int i = 0;
	
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return -1;
	}

	sceKernelLockLwMutex(&__fdman_mutex, 1, 0); /* lock here to make thread safe */
	for (i = 0; i < __FILENO_MAX; i++) {
		if (__descriptormap[i] == NULL) {
			__descriptormap[i] = &__descriptor_data_pool[fd];
			__descriptormap[i]->ref_count++;
			sceKernelUnlockLwMutex(&__fdman_mutex, 1);; /* release lock */
			return i;
		}
	}
	sceKernelUnlockLwMutex(&__fdman_mutex, 1);; /* release lock */
	
	errno = ENOMEM;
	return -1;
}
#endif


#ifdef F___fdman_release_descriptor
void __fdman_release_descriptor(int fd)
{
	if (!__IS_FD_VALID(fd)) {
		errno = EBADF;
		return;
	}

	__descriptormap[fd]->ref_count--;
	
	if (__descriptormap[fd]->ref_count == 0) {
		
		if (__descriptormap[fd]->filename != NULL) {
			free(__descriptormap[fd]->filename);
		}
		__descriptormap[fd]->filename = NULL;
		__descriptormap[fd]->descriptor = 0;
		__descriptormap[fd]->type = 0;
		__descriptormap[fd]->flags = 0;
		
	}
	__descriptormap[fd] = NULL;
}
#endif