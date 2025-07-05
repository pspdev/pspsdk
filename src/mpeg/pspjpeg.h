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

#define SCE_JPEG_ERROR_BAD_MARKER_LENGTH 	(0x80650004)
#define SCE_JPEG_ERROR_INVALID_POINTER 	    (0x80650010)
#define SCE_JPEG_ERROR_UNSUPPORT_COLORSPACE (0x80650013)
#define SCE_JPEG_ERROR_UNSUPPORT_SAMPLING 	(0x80650016)
#define SCE_JPEG_ERROR_UNSUPPORT_IMAGE_SIZE (0x80650020)
#define SCE_JPEG_ERROR_UNKNOWN_MARKER 	    (0x80650035)

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
 * Decodes a mjpeg frame to RGBA encoding.
 * @note Input frame should be encoded as either yuv420p or yuvj420p, 
 * returns SCE_JPEG_ERROR_UNSUPPORT_SAMPLING otherwise
 *
 * @param jpegbuf - the buffer with the mjpeg frame
 * @param size - size of the buffer pointed by jpegbuf
 * @param rgba - buffer where the decoded data in RGBA format will be stored.
 *				       It should have a size of (width * height * 4).
 * @param unk - Unknown, pass 0
 *
 * @return (width * 65536) + height on success, < 0 on error 
*/
int sceJpegDecodeMJpeg(u8 *jpegbuf,	SceSize size, u8 *rgba, u32 unk);

/**
 * Reads information from mjpeg frame
 *
 * @param jpegbuf - the buffer with the mjpeg frame
 * @param size - size of the mjpeg frame
 * @param colourInfo - address where the mjpeg chroma information will be stored
 * @param unk - Unknown, pass 0
 *
 * @return number of bytes needed in the buffer that will be used for YCbCr decoding, <= 0 on error
*/
int sceJpegGetOutputInfo(u8 *jpegbuf, SceSize size, int *colourInfo, int unk);

/**
 * Decodes a mjpeg frame to YCbCr encoding
 * @note Input frame should be encoded as either yuv420p or yuvj420p, 
 * returns SCE_JPEG_ERROR_UNSUPPORT_SAMPLING otherwise
 *
 * @param jpegbuf - the buffer with the mjpeg frame
 * @param size - size of the buffer pointed by jpegbuf
 * @param yCbCr - buffer where the decoded data in YCbCr format will be stored
 * @param yCbCrSize - size of the buffer pointed by yCbCr (see sceJpegGetOutputInfo())
 * @param unk - Unknown, pass 0
 *
 * @return (width * 65536) + height on success, < 0 on error 
*/
int sceJpegDecodeMJpegYCbCr(u8 *jpegbuf, SceSize size, u8 *yCbCr, SceSize yCbCrSize, u32 unk);

/**
 * Converts a frame from YCbCr to RGBA
 *
 * @param imageAddr - buffer where the converted data in RGBA format will be stored.
 * @param yCbCrAddr - the buffer with the YCbCr data
 * @param widthHeight - width and height of the frame (width * 65536) + height, 
 *                          as returned by sceJpegDecodeMJpegYCbCr() or sceJpegDecodeMJpeg()
 * @param bufferWidth - number of pixels per row of the buffer
 * @param colourInfo - chroma subsampling mode, as provided by sceJpegGetOutputInfo()
 *
 * @return 0 on success, < 0 on error
*/
int sceJpegCsc(u8 *imageAddr, u8 *yCbCrAddr, int widthHeight, int bufferWidth, int colourInfo);

#ifdef __cplusplus
}
#endif

#endif
