/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * dmac.c - A DMAC function
 *
 * Copyright (c) 2016 173210 <root.3.173210@live.com>
 */

#ifndef __DMAC_H__
#define __DMAC_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Copy data in memory using DMAC
 *
 * @param dst - The pointer to the destination
 * @param src - The pointer to the source
 * @param n - The size of data
 *
 * @return 0 on success; otherwise an error code
 */
int sceDmacMemcpy(void *dst, const void *src, SceSize n);

int sceDmacTryMemcpy(void *dst, const void *src, SceSize n);

#ifdef __cplusplus
}
#endif

#endif
