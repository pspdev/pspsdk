/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspvideocodec.h - Prototypes for the sceVideocodec library.
 *
 * Copyright (c) 2007 cooleyes
 *
 * $Id: pspvideocodec.h 2418 2008-08-13 23:29:18Z Raphael $
 */
 
#ifndef __SCELIBVIDEOCODEC_H__
#define __SCELIBVIDEOCODEC_H__

#ifdef __cplusplus
extern "C" {
#endif

int sceVideocodecOpen(unsigned long *Buffer, int Type);
int sceVideocodecGetEDRAM(unsigned long *Buffer, int Type);
int sceVideocodecInit(unsigned long *Buffer, int Type);
int sceVideocodecDecode(unsigned long *Buffer, int Type);
int sceVideocodecReleaseEDRAM(unsigned long *Buffer);

// sceVideocodecGetVersion
// sceVideocodecScanHeader
// sceVideocodecDelete
// sceVideocodecSetMemory
// sceVideocodecStop

#ifdef __cplusplus
}
#endif

#endif