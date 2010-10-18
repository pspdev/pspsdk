/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspidstorage.h - Interface to sceIdstorage_driver.
 *
 * Copyright (c) 2006 Harley G. <harleyg@0x89.org>
 *
 * $Id: pspidstorage.h 2120 2006-12-30 23:19:33Z tyranid $
 */

#ifndef PSPIDSTORAGE_H
#define PSPIDSTORAGE_H

#include <psptypes.h>

/** @defgroup IdStorage Interface to the sceIdStorage_driver library.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup IdStorage Interface to the sceIdStorage_driver library.*/
/*@{*/

/**Retrieves the value associated with a key
 * @param key    - idstorage key
 * @param offset - offset within the 512 byte leaf
 * @param buf    - buffer with enough storage
 * @param len    - amount of data to retrieve (offset + len must be <= 512 bytes)
 */
int sceIdStorageLookup(u16 key, u32 offset, void *buf, u32 len);

/** Retrieves the whole 512 byte container for the key
 * @param key - idstorage key
 * @param buf - buffer with at last 512 bytes of storage
 */
int sceIdStorageReadLeaf(u16 key, void *buf);

/** sceIdStorageWriteLeaf() - Writes 512-bytes to idstorage key
 * @param key - idstorage key
 * @param buf - buffer with 512-btes of data
 */
int sceIdStorageWriteLeaf(u16 key, void *buf);

/** sceIdStorageIsReadOnly() - Checks idstorage for readonly status */
int sceIdStorageIsReadOnly(void);

/** sceIdStorageFlush() - Finalizes a write */
int sceIdStorageFlush(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
