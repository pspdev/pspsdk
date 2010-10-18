/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspatrac3.h - Prototypes for the sceAtrac3plus library
 *
 * Copyright (c) 2006 moonlight
 *
 * $Id: pspatrac3.h 2433 2008-10-15 10:00:27Z iwn $
 */
#ifndef __LIBATRAC3_H__
#define __LIBATRAC3_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif
