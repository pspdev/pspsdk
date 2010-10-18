/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspjpeg.h - Prototypes for the sceJpeg library
 *
 * Copyright (c) 2007 dot_blank
 *
 * $Id: pspjpeg.h 2433 2008-10-15 10:00:27Z iwn $
 */
#ifndef __PSPJPEG_H__
#define __PSPJPEG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <psptypes.h>

/**
 * Inits the MJpeg library 
 *
 * @return 0 on success, < 0 on error
*/
int sceJpegInitMJpeg(void);

/**
 * Finishes the MJpeg library
 *
 * @return 0 on success, < 0 on error
*/
int sceJpegFinishMJpeg(void);

/**
 * Creates the decoder context.
 *
 * @param width - The width of the frame
 * @param height - The height of the frame
 *
 * @return 0 on success, < 0 on error
*/
int sceJpegCreateMJpeg(int width, int height);

/**
 * Deletes the current decoder context.
 *
 * @return 0 on success, < 0 on error
*/
int sceJpegDeleteMJpeg(void);

/**
 * Decodes a mjpeg frame.
 *
 * @param jpegbuf - the buffer with the mjpeg frame
 * @param size - size of the buffer pointed by jpegbuf
 * @param rgba - buffer where the decoded data in RGBA format will be stored.
 *				       It should have a size of (width * height * 4).
 * @param unk - Unknown, pass 0
 *
 * @return (width * 65536) + height on success, < 0 on error 
*/
int sceJpegDecodeMJpeg(u8 *jpegbuf,	SceSize size, void *rgba, u32 unk);

#ifdef __cplusplus
}
#endif

#endif
