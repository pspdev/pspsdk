/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspatrac3.h - Prototypes for the sceAtrac3plus library
 *
 * Copyright (c) 2006 moonlight
 *
 */
#ifndef __LIBATRAC3_H__
#define __LIBATRAC3_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Error code definition */
#define PSP_ATRAC_SUCCESS                       SCE_OK

#define PSP_ATRAC_ERROR_PARAM_FAIL              (0x80630001)
#define PSP_ATRAC_ERROR_API_FAIL                (0x80630002)
#define PSP_ATRAC_ERROR_NO_ATRACID              (0x80630003)
#define PSP_ATRAC_ERROR_BAD_CODECTYPE           (0x80630004)
#define PSP_ATRAC_ERROR_BAD_ATRACID             (0x80630005)
#define PSP_ATRAC_ERROR_UNKNOWN_FORMAT          (0x80630006)
#define PSP_ATRAC_ERROR_UNMATCH_FORMAT          (0x80630007)
#define PSP_ATRAC_ERROR_BAD_DATA                (0x80630008)
#define PSP_ATRAC_ERROR_ALLDATA_IS_ONMEMORY     (0x80630009)
#define PSP_ATRAC_ERROR_UNSET_DATA              (0x80630010)

#define PSP_ATRAC_ERROR_READSIZE_IS_TOO_SMALL   (0x80630011)
#define PSP_ATRAC_ERROR_NEED_SECOND_BUFFER      (0x80630012)
#define PSP_ATRAC_ERROR_READSIZE_OVER_BUFFER    (0x80630013)
#define PSP_ATRAC_ERROR_NOT_4BYTE_ALIGNMENT     (0x80630014)
#define PSP_ATRAC_ERROR_BAD_SAMPLE              (0x80630015)
#define PSP_ATRAC_ERROR_WRITEBYTE_FIRST_BUFFER  (0x80630016)
#define PSP_ATRAC_ERROR_WRITEBYTE_SECOND_BUFFER (0x80630017)
#define PSP_ATRAC_ERROR_ADD_DATA_IS_TOO_BIG     (0x80630018)

#define PSP_ATRAC_ERROR_UNSET_PARAM             (0x80630021)
#define PSP_ATRAC_ERROR_NONEED_SECOND_BUFFER    (0x80630022)
#define PSP_ATRAC_ERROR_NODATA_IN_BUFFER        (0x80630023)
#define PSP_ATRAC_ERROR_ALLDATA_WAS_DECODED     (0x80630024)

/* Audio Codec ID */
#define PSP_ATRAC_AT3PLUS        (0x00001000)
#define PSP_ATRAC_AT3            (0x00001001)

/* Remain Frame typical Status */
#define PSP_ATRAC_ALLDATA_IS_ON_MEMORY             (-1)
#define PSP_ATRAC_NONLOOP_STREAM_DATA_IS_ON_MEMORY (-2)
#define PSP_ATRAC_LOOP_STREAM_DATA_IS_ON_MEMORY    (-3)

typedef struct {
	u8 *pucWritePositionFirstBuf;
	u32 uiWritableByteFirstBuf;
	u32 uiMinWriteByteFirstBuf;
	u32 uiReadPositionFirstBuf;

	u8 *pucWritePositionSecondBuf;
	u32 uiWritableByteSecondBuf;
	u32 uiMinWriteByteSecondBuf;
	u32 uiReadPositionSecondBuf;
} PspBufferInfo;

int sceAtracGetAtracID(uint  uiCodecType);

/**
 * Creates a new Atrac ID from the specified data
 *
 * @param buf - the buffer holding the atrac3 data, including the RIFF/WAVE header.
 * @param bufsize - the size of the buffer pointed by buf
 *
 * @return the new atrac ID, or < 0 on error 
*/
int sceAtracSetDataAndGetID(void *buf, SceSize bufsize);

/**
 * Decode a frame of data. 
 *
 * @param atracID - the atrac ID
 * @param outSamples - pointer to a buffer that receives the decoded data of the current frame
 * @param outN - pointer to a integer that receives the number of audio samples of the decoded frame
 * @param outEnd - pointer to a integer that receives a boolean value indicating if the decoded frame is the last one
 * @param outRemainFrame - pointer to a integer that receives either -1 if all at3 data is already on memory, 
 *  or the remaining (not decoded yet) frames at memory if not all at3 data is on memory
 *
 * 
 * @return < 0 on error, otherwise 0
 *
*/
int sceAtracDecodeData(int atracID, u16 *outSamples, int *outN, int *outEnd, int *outRemainFrame);

/**
 * Gets the remaining (not decoded) number of frames
 * 
 * @param atracID - the atrac ID
 * @param outRemainFrame - pointer to a integer that receives either -1 if all at3 data is already on memory, 
 *  or the remaining (not decoded yet) frames at memory if not all at3 data is on memory 
 *
 * @return < 0 on error, otherwise 0
 *
*/
int sceAtracGetRemainFrame(int atracID, int *outRemainFrame);

/**
 *
 * @param atracID - the atrac ID
 * @param writePointer - Pointer to where to read the atrac data
 * @param availableBytes - Number of bytes available at the writePointer location
 * @param readOffset - Offset where to seek into the atrac file before reading
 *
 * @return < 0 on error, otherwise 0
 *
*/

int sceAtracGetStreamDataInfo(int atracID, u8** writePointer, u32* availableBytes, u32* readOffset);

/**
 *
 * @param atracID - the atrac ID
 * @param bytesToAdd - Number of bytes read into location given by sceAtracGetStreamDataInfo().
 *
 * @return < 0 on error, otherwise 0
*/
int sceAtracAddStreamData(int atracID, unsigned int bytesToAdd);

/**
 * Gets the bitrate.
 *
 * @param atracID - the atracID
 * @param outBitrate - pointer to a integer that receives the bitrate in kbps
 *
 * @return < 0 on error, otherwise 0
 *
*/
int sceAtracGetBitrate(int atracID, int *outBitrate);

/**
 * Sets the number of loops for this atrac ID
 *
 * @param atracID - the atracID
 * @param nloops - the number of loops to set
 *
 * @return < 0 on error, otherwise 0
 *
*/
int sceAtracSetLoopNum(int atracID, int nloops);

/**
 * It releases an atrac ID
 *
 * @param atracID - the atrac ID to release
 *
 * @return < 0 on error
 *
*/
int sceAtracReleaseAtracID(int atracID);

/**
 * Gets the number of samples of the next frame to be decoded.
 *
 * @param atracID - the atrac ID
 * @param outN - pointer to receives the number of samples of the next frame.
 *
 * @return < 0 on error, otherwise 0
 *
 */
int sceAtracGetNextSample(int atracID, int *outN);

/**
 * Gets the maximum number of samples of the atrac3 stream.
 *
 * @param atracID - the atrac ID
 * @param outMax  - pointer to a integer that receives the maximum number of samples.
 *
 * @return < 0 on error, otherwise 0
 *
 */
int sceAtracGetMaxSample(int atracID, int *outMax); 

int sceAtracGetBufferInfoForReseting(int atracID, u32 uiSample, PspBufferInfo *pBufferInfo);

int sceAtracGetChannel(int atracID, u32 *puiChannel);

int sceAtracGetInternalErrorInfo(int atracID, int *piResult);

int sceAtracGetLoopStatus(int atracID, int *piLoopNum, u32 *puiLoopStatus);

int sceAtracGetNextDecodePosition(int atracID, u32 *puiSamplePosition);

int sceAtracGetSecondBufferInfo(int atracID, u32 *puiPosition, u32 *puiDataByte);

int sceAtracGetSoundSample(int atracID, int *piEndSample, int *piLoopStartSample, int *piLoopEndSample);

int sceAtracResetPlayPosition(int atracID, u32 uiSample, u32 uiWriteByteFirstBuf, u32 uiWriteByteSecondBuf);

int sceAtracSetData(int atracID, u8 *pucBufferAddr, u32 uiBufferByte);

int sceAtracSetHalfwayBuffer(int atracID, u8 *pucBufferAddr, u32 uiReadByte, u32 uiBufferByte);

int sceAtracSetHalfwayBufferAndGetID(u8 *pucBufferAddr, u32 uiReadByte, u32 uiBufferByte);

int sceAtracSetSecondBuffer(int atracID, u8 *pucSecondBufferAddr, u32 uiSecondBufferByte);

#ifdef __cplusplus
}
#endif

#endif
