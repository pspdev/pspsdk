/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspssl.h - Interface to the ssl library.
 *
 * Copyright (c) 2008 David Perry (InsertWittyName)
 * Copyright (c) 2008 moonlight
 *
 */

#ifndef __PSPSSL_H__
#define __PSPSSL_H__

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * Init the ssl library.
 *
 * @param unknown1 - Memory size? Pass 0x28000
 *
 * @return 0 on success
*/
int sceSslInit(int unknown1);

/**
 * Terminate the ssl library.
 *
 * @return 0 on success
*/
int sceSslEnd(void);

/**
 * Get the maximum memory size used by ssl.
 *
 * @param memory - Pointer where the maximum memory used value will be stored.
 *
 * @return 0 on success
*/
int sceSslGetUsedMemoryMax(unsigned int *memory);

/**
 * Get the current memory size used by ssl.
 *
 * @param memory - Pointer where the current memory used value will be stored.
 *
 * @return 0 on success
*/
int sceSslGetUsedMemoryCurrent(unsigned int *memory);

#if defined(__cplusplus)
};
#endif

#endif
