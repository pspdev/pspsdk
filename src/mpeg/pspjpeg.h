/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspjpeg.h - Prototypes for the sceJpeg library
 *
 * Copyright (c) 2007 dot_blank
 *
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
 * @param dhtMode - Unknown, pass 0
 *
 * @return (width * 65536) + height on success, < 0 on error 
*/
int sceJpegDecodeMJpeg(u8 *jpegbuf,	SceSize size, void *rgba, u32 dhtMode);

/**
 * Decodes a mjpeg frame with YCbCr encoding.
 *
 * @param jpegbuf - the buffer with the mjpeg frame
 * @param size - size of the buffer pointed by jpegbuf
 * @param rgba - buffer where the decoded data in YCbCr format will be stored.
 * @param dhtMode - Unknown, pass 0
 *
 * @return (width * 65536) + height on success, < 0 on error 
*/
int sceJpegDecodeMJpegYCbCr(u8 *jpegbuf, SceSize size, void *yCbCr, u32 dhtMode);

/**
 * Converts a frame from YCbCr to ABGR
 *
 * @param imageAddr - buffer where the decoded data in abgr format will be stored.
 * @param yCbCrAddr - the buffer with the YCbCr data
 * @param widthHeight - width and height of the frame (width << 16) | height
 * @param bufferWidth - number of pixels per row of the buffer
 * @param colourInfo - chroma subsampling mode
 *
 * @return 0 on success, < 0 on error
*/
int sceJpegCsc(u8 *imageAddr, u8 *yCbCrAddr, int widthHeight, int bufferWidth, int colourInfo);

#ifdef __cplusplus
}
#endif

#endif
