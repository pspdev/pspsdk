/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmp3.h - Prototypes for the sceMp3 library
 *
 * Copyright (c) 2008 David Perry <tias_dp@hotmail.com>
 * Copyright (c) 2008 Alexander Berl <raphael@fx-world.org>
 *
 * $Id: $
 */

#ifndef __SCELIBMP3_H__
#define __SCELIBMP3_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceMp3InitArg {
	/** Stream start position */
	SceUInt32	mp3StreamStart;
	/** Unknown - set to 0 */
	SceUInt32	unk1;
	/** Stream end position */
	SceUInt32	mp3StreamEnd;
	/** Unknown - set to 0 */
	SceUInt32	unk2;
	/** Pointer to a buffer to contain raw mp3 stream data (+1472 bytes workspace) */
	SceVoid*	mp3Buf;
	/** Size of mp3Buf buffer (must be >= 8192) */
	SceInt32	mp3BufSize;
	/** Pointer to decoded pcm samples buffer */
	SceVoid*	pcmBuf;
	/** Size of pcmBuf buffer (must be >= 9216) */
	SceInt32	pcmBufSize;
} SceMp3InitArg;

/**
 * sceMp3ReserveMp3Handle
 *
 * @param args - Pointer to SceMp3InitArg structure
 *
 * @return sceMp3 handle on success, < 0 on error.
 */
SceInt32 sceMp3ReserveMp3Handle(SceMp3InitArg* args);

/**
 * sceMp3ReleaseMp3Handle
 *
 * @param handle - sceMp3 handle
 *
 * @return 0 if success, < 0 on error.
 */
SceInt32 sceMp3ReleaseMp3Handle(SceInt32 handle);

/**
 * sceMp3InitResource
 *
 * @return 0 if success, < 0 on error.
 */
SceInt32 sceMp3InitResource();

/**
 * sceMp3TermResource
 *
 * @return 0 if success, < 0 on error.
 */
SceInt32 sceMp3TermResource();

/**
 * sceMp3Init
 *
 * @param handle - sceMp3 handle
 *
 * @return 0 if success, < 0 on error.
 */
SceInt32 sceMp3Init(SceInt32 handle);

/**
 * sceMp3Decode
 *
 * @param handle - sceMp3 handle
 * @param dst - Pointer to destination pcm samples buffer
 *
 * @return number of bytes in decoded pcm buffer, < 0 on error.
 */
SceInt32 sceMp3Decode(SceInt32 handle, SceShort16** dst);

/**
 * sceMp3GetInfoToAddStreamData
 *
 * @param handle - sceMp3 handle
 * @param dst - Pointer to stream data buffer
 * @param towrite - Space remaining in stream data buffer
 * @param srcpos - Position in source stream to start reading from
 *
 * @return 0 if success, < 0 on error.
 */
SceInt32 sceMp3GetInfoToAddStreamData(SceInt32 handle, SceUChar8** dst, SceInt32* towrite, SceInt32* srcpos);

/**
 * sceMp3NotifyAddStreamData
 *
 * @param handle - sceMp3 handle
 * @param size - number of bytes added to the stream data buffer
 *
 * @return 0 if success, < 0 on error.
 */
SceInt32 sceMp3NotifyAddStreamData(SceInt32 handle, SceInt32 size);

/**
 * sceMp3CheckStreamDataNeeded
 *
 * @param handle - sceMp3 handle
 *
 * @return 1 if more stream data is needed, < 0 on error.
 */
SceInt32 sceMp3CheckStreamDataNeeded(SceInt32 handle);

/**
 * sceMp3SetLoopNum
 *
 * @param handle - sceMp3 handle
 * @param loop - Number of loops
 *
 * @return 0 if success, < 0 on error.
 */
SceInt32 sceMp3SetLoopNum(SceInt32 handle, SceInt32 loop);

/**
 * sceMp3GetLoopNum
 *
 * @param handle - sceMp3 handle
 *
 * @return Number of loops
 */
SceInt32 sceMp3GetLoopNum(SceInt32 handle);

/**
 * sceMp3GetSumDecodedSample
 *
 * @param handle - sceMp3 handle
 *
 * @return Number of decoded samples
 */
SceInt32 sceMp3GetSumDecodedSample(SceInt32 handle);

/**
 * sceMp3GetMaxOutputSample
 *
 * @param handle - sceMp3 handle
 *
 * @return Number of max samples to output
 */
SceInt32 sceMp3GetMaxOutputSample(SceInt32 handle);

/**
 * sceMp3GetSamplingRate
 *
 * @param handle - sceMp3 handle
 *
 * @return Sampling rate of the mp3
 */
SceInt32 sceMp3GetSamplingRate(SceInt32 handle);

/**
 * sceMp3GetBitRate
 *
 * @param handle - sceMp3 handle
 *
 * @return Bitrate of the mp3
 */
SceInt32 sceMp3GetBitRate(SceInt32 handle);

/**
 * sceMp3GetMp3ChannelNum
 *
 * @param handle - sceMp3 handle
 *
 * @return Number of channels of the mp3
 */
SceInt32 sceMp3GetMp3ChannelNum(SceInt32 handle);

/**
 * sceMp3ResetPlayPosition
 *
 * @param handle - sceMp3 handle
 *
 * @return < 0 on error
 */
SceInt32 sceMp3ResetPlayPosition(SceInt32 handle); 


#ifdef __cplusplus
}
#endif

#endif
