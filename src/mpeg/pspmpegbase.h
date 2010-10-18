/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmpegbase.h - Prototypes for the sceMpegbase library
 *
 * Copyright (c) 2006 Sorin P. C. <magik@hypermagik.com>
 * Copyright (c) 2007 cooleyes
 * Copyright (c) 2007 Alexander Berl <raphael@fx-world.org>
 *
 * $Id: pspmpegbase.h 2341 2007-12-06 20:05:52Z raphael $
 */

#ifndef __SCELIBMPEGBASE_H__
#define __SCELIBMPEGBASE_H__


#include <psptypes.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct SceMpegLLI
{
	ScePVoid pSrc;
	ScePVoid pDst;
	ScePVoid Next;
	SceInt32 iSize;
} __attribute__((aligned(64))) SceMpegLLI;



typedef struct SceMpegYCrCbBuffer
{
	SceInt32	iFrameBufferHeight16;
	SceInt32	iFrameBufferWidth16;
	SceInt32	iUnknown;			// Set to 0
	SceInt32	iUnknown2;			// Set to 1
	ScePVoid	pYBuffer;			// pointer to YBuffer (in VME EDRAM?)
	ScePVoid	pYBuffer2;			// pointer to YBuffer + framebufferwidth*(frameheight/32)
	ScePVoid	pCrBuffer;			// pointer to CrBuffer (in VME EDRAM?)
	ScePVoid	pCbBuffer;			// pointer to CbBuffer (in VME EDRAM?)
	ScePVoid	pCrBuffer2;			// pointer to CrBuffer + (framebufferwidth/2)*(frameheight/64)
	ScePVoid	pCbBuffer2;			// pointer to CbBuffer + (framebufferwidth/2)*(frameheight/64)
	SceInt32	iFrameHeight;
	SceInt32	iFrameWidth;
	SceInt32	iFrameBufferWidth;
	SceInt32	iUnknown3[11];
} __attribute__((aligned(64))) SceMpegYCrCbBuffer;


SceInt32 sceMpegBaseYCrCbCopyVme(ScePVoid YUVBuffer, SceInt32 *Buffer, SceInt32 Type);
SceInt32 sceMpegBaseCscInit(SceInt32 width);
SceInt32 sceMpegBaseCscVme(ScePVoid pRGBbuffer, ScePVoid pRGBbuffer2, SceInt32 width, SceMpegYCrCbBuffer* pYCrCbBuffer);

SceInt32 sceMpegbase_BEA18F91(SceMpegLLI *pLLI);

#ifdef __cplusplus
}
#endif

#endif
