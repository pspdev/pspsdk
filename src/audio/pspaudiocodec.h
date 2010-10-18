/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspaudiocodec.h - Prototypes for the sceAudiocodec library.
 *
 * Copyright (c) 2006 hitchhikr
 *
 * $Id: pspaudiocodec.h 2430 2008-08-28 12:04:04Z Raphael $
 */

#ifdef __cplusplus
extern "C" {
#endif

#define PSP_CODEC_AT3PLUS	(0x00001000)
#define PSP_CODEC_AT3		(0x00001001)
#define PSP_CODEC_MP3		(0x00001002)
#define PSP_CODEC_AAC		(0x00001003)


int sceAudiocodecCheckNeedMem(unsigned long *Buffer, int Type);
int sceAudiocodecInit(unsigned long *Buffer, int Type);
int sceAudiocodecDecode(unsigned long *Buffer, int Type);
int sceAudiocodecGetEDRAM(unsigned long *Buffer, int Type);
int sceAudiocodecReleaseEDRAM(unsigned long *Buffer);

#ifdef __cplusplus
}
#endif
