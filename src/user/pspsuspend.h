/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsuspend.h - User interface to the PSP suspend.
 *
 * Copyright (c) 2006 James F
 *
 * $Id
 */

#ifndef __PSPSUSPEND_H__
#define __PSPSUSPEND_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Allocate the extra 4megs of RAM
 *
 * @param unk - No idea as it is never used, set to anything
 * @param ptr - Pointer to a pointer to hold the address of the memory
 * @param size - Pointer to an int which will hold the size of the memory
 *
 * @return 0 on success
 */
int sceKernelVolatileMemLock(int unk, void **ptr, int *size);

/**
 * Try and allocate the extra 4megs of RAM, will return an error if 
 * something has already allocated it
 *
 * @param unk - No idea as it is never used, set to anything
 * @param ptr - Pointer to a pointer to hold the address of the memory
 * @param size - Pointer to an int which will hold the size of the memory
 *
 * @return 0 on success
 */
int sceKernelVolatileMemTryLock(int unk, void **ptr, int *size);

/**
 * Deallocate the extra 4 megs of RAM
 *
 * @param unk - Set to 0, otherwise it fails in 3.52+, possibly earlier
 * @return 0 on success
 */
int sceKernelVolatileMemUnlock(int unk);

#ifdef __cplusplus
}
#endif

#endif
