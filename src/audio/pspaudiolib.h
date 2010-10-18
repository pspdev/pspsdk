/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspaudiolib.h - Audio library build on top of sceAudio, but to provide
 *                 multiple thread usage and callbacks.
 *
 * Copyright (c) 2005 Adresd
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 *
 * $Id: pspaudiolib.h 1874 2006-04-18 13:20:58Z tyranid $
 */
#ifndef __AUDIOLIB_H__
#define __AUDIOLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PSP_NUM_AUDIO_CHANNELS 4
/** This is the number of frames you can update per callback, a frame being
 * 1 sample for mono, 2 samples for stereo etc. */
#define PSP_NUM_AUDIO_SAMPLES 1024
#define PSP_VOLUME_MAX 0x8000

typedef void (* pspAudioCallback_t)(void *buf, unsigned int reqn, void *pdata);

typedef struct {
  int threadhandle;
  int handle;
  int volumeleft;
  int volumeright;
  pspAudioCallback_t callback;
  void *pdata;
} psp_audio_channelinfo;

typedef int (* pspAudioThreadfunc_t)(int args, void *argp);

int  pspAudioInit();
void pspAudioEndPre();
void pspAudioEnd();

void pspAudioSetVolume(int channel, int left, int right);
void pspAudioChannelThreadCallback(int channel, void *buf, unsigned int reqn);
void pspAudioSetChannelCallback(int channel, pspAudioCallback_t callback, void *pdata);
int  pspAudioOutBlocking(unsigned int channel, unsigned int vol1, unsigned int vol2, void *buf);

#ifdef __cplusplus
}
#endif

#endif
