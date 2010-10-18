/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspdisplay_kernel.h - Prototypes for the sceDisplay_driver library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2007 Alexander Berl <raphael@fx-world.org>
 *
 * $Id: pspdisplay_kernel.h 2271 2007-07-20 13:08:41Z oopo $
 */
#ifndef __DISPLAYKERNEL_H__
#define __DISPLAYKERNEL_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Display set framebuf
 *
 * @param pri - Priority
 * @param topaddr - address of start of framebuffer
 * @param bufferwidth - buffer width (must be power of 2)
 * @param pixelformat - One of ::PspDisplayPixelFormats.
 * @param sync - One of ::PspDisplaySetBufSync
 *
 * @return 0 on success
 */
int sceDisplay_driver_63E22A26(int pri, void *topaddr, int bufferwidth, int pixelformat, int sync);

/**
 * Get Display Framebuffer information
 *
 * @param pri - Priority
 * @param topaddr - pointer to void* to receive address of start of framebuffer
 * @param bufferwidth - pointer to int to receive buffer width (must be power of 2)
 * @param pixelformat - pointer to int to receive one of ::PspDisplayPixelFormats.
 * @param sync - One of ::PspDisplaySetBufSync
 *
 * @return 0 on success
 */
int sceDisplay_driver_5B5AEFAD(int pri, void **topaddr, int *bufferwidth, int *pixelformat, int sync);

/* Define some names to make it nicer */
#define sceDisplaySetFrameBufferInternal sceDisplay_driver_63E22A26
#define sceDisplayGetFrameBufferInternal sceDisplay_driver_5B5AEFAD

/**
 * Set Display brightness to a particular level
 *
 * @param level - Level of the brightness. it goes from 0 (black screen) to 100 (max brightness)
 * @param unk1 - Unknown can be 0 or 1 (pass 0)
 */
void sceDisplaySetBrightness(int level,int unk1);

/**
 * Get current display brightness
 *
 * @param level - Pointer to int to receive the current brightness level (0-100)
 * @param unk1 - Pointer to int, receives unknown, it's 1 or 0
 */
void sceDisplayGetBrightness(int *level,int *unk1);

#ifdef __cplusplus
}
#endif

#endif
