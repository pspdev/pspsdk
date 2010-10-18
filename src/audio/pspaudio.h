/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspaudio.h - Prototypes for the sceAudio library.
 *
 * Copyright (c) 2005 Adresd
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2007 cooleyes
 * Copyright (c) 2007 Alexander Berl <raphael@fx-world.org>
 * Copyright (c) 2008 David Perry <tias_dp@hotmail.com>
 *
 * $Id: pspaudio.h 2433 2008-10-15 10:00:27Z iwn $
 */
#ifndef PSPAUDIO_H
#define PSPAUDIO_H

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Audio User Audio Library */

/** @addtogroup Audio */

/*@{*/

/** The maximum output volume. */
#define PSP_AUDIO_VOLUME_MAX    0x8000

/** The maximum number of hardware channels. */
#define PSP_AUDIO_CHANNEL_MAX   8

/** Used to request the next available hardware channel. */
#define PSP_AUDIO_NEXT_CHANNEL  (-1)

enum PspAudioFormats
{
    /** Channel is set to stereo output. */
    PSP_AUDIO_FORMAT_STEREO = 0,
    /** Channel is set to mono output. */
    PSP_AUDIO_FORMAT_MONO   = 0x10
};

typedef struct
{
	/** Unknown. Pass 0 */
	int unknown1;
	int gain;
	/** Unknown. Pass 0 */
	int unknown2;
	/** Unknown. Pass 0 */
	int unknown3;
	/** Unknown. Pass 0 */
	int unknown4;
	/** Unknown. Pass 0 */
	int unknown5;
	
} pspAudioInputParams;

/** The minimum number of samples that can be allocated to a channel. */
#define PSP_AUDIO_SAMPLE_MIN    64

/** The maximum number of samples that can be allocated to a channel. */
#define PSP_AUDIO_SAMPLE_MAX    65472

/** Make the given sample count a multiple of 64. */
#define PSP_AUDIO_SAMPLE_ALIGN(s) (((s) + 63) & ~63)
 
/**
  * Allocate and initialize a hardware output channel.
  *
  * @param channel - Use a value between 0 - 7 to reserve a specific channel.
  *                   Pass PSP_AUDIO_NEXT_CHANNEL to get the first available channel.
  * @param samplecount - The number of samples that can be output on the channel per
  *                      output call.  It must be a value between ::PSP_AUDIO_SAMPLE_MIN
  *                      and ::PSP_AUDIO_SAMPLE_MAX, and it must be aligned to 64 bytes
  *                      (use the ::PSP_AUDIO_SAMPLE_ALIGN macro to align it).
  * @param format - The output format to use for the channel.  One of ::PspAudioFormats.
  *
  * @return The channel number on success, an error code if less than 0.
  */
int sceAudioChReserve(int channel, int samplecount, int format);

/**
  * Release a hardware output channel.
  *
  * @param channel - The channel to release.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioChRelease(int channel);

/**
  * Output audio of the specified channel
  *
  * @param channel - The channel number.
  *
  * @param vol - The volume.
  *
  * @param buf - Pointer to the PCM data to output.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioOutput(int channel, int vol, void *buf);

/**
  * Output audio of the specified channel (blocking)
  *
  * @param channel - The channel number.
  *
  * @param vol - The volume.
  *
  * @param buf - Pointer to the PCM data to output.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioOutputBlocking(int channel, int vol, void *buf);

/**
  * Output panned audio of the specified channel
  *
  * @param channel - The channel number.
  *
  * @param leftvol - The left volume.
  *
  * @param rightvol - The right volume.
  *
  * @param buf - Pointer to the PCM data to output.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioOutputPanned(int channel, int leftvol, int rightvol, void *buf);

/**
  * Output panned audio of the specified channel (blocking)
  *
  * @param channel - The channel number.
  *
  * @param leftvol - The left volume.
  *
  * @param rightvol - The right volume.
  *
  * @param buf - Pointer to the PCM data to output.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioOutputPannedBlocking(int channel, int leftvol, int rightvol, void *buf);

/**
  * Get count of unplayed samples remaining
  *
  * @param channel - The channel number.
  *
  * @return Number of samples to be played, an error if less than 0.
  */
int sceAudioGetChannelRestLen(int channel);

/**
  * Get count of unplayed samples remaining
  *
  * @param channel - The channel number.
  *
  * @return Number of samples to be played, an error if less than 0.
  */
int sceAudioGetChannelRestLength(int channel);

/**
  * Change the output sample count, after it's already been reserved
  *
  * @param channel - The channel number.
  * @param samplecount - The number of samples to output in one output call.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioSetChannelDataLen(int channel, int samplecount);

/**
  * Change the format of a channel
  *
  * @param channel - The channel number.
  *
  * @param format - One of ::PspAudioFormats
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioChangeChannelConfig(int channel, int format);

/**
  * Change the volume of a channel
  *
  * @param channel - The channel number.
  *
  * @param leftvol - The left volume.
  *
  * @param rightvol - The right volume.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioChangeChannelVolume(int channel, int leftvol, int rightvol);

//sceAudioOneshotOutput ???

/**
  * Reserve the audio output and set the output sample count
  *
  * @param samplecount - The number of samples to output in one output call (min 17, max 4111).
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioOutput2Reserve(int samplecount);

/**
  * Release the audio output
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioOutput2Release(void);

/**
  * Change the output sample count, after it's already been reserved
  *
  * @param samplecount - The number of samples to output in one output call (min 17, max 4111).
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioOutput2ChangeLength(int samplecount);

/**
  * Output audio (blocking)
  *
  * @param vol - The volume.
  *
  * @param buf - Pointer to the PCM data.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioOutput2OutputBlocking(int vol, void *buf);

/**
  * Get count of unplayed samples remaining
  *
  * @return Number of samples to be played, an error if less than 0.
  */
int sceAudioOutput2GetRestSample(void);

/**
  * Reserve the audio output
  *
  * @param samplecount - The number of samples to output in one output call (min 17, max 4111).
  *
  * @param freq - The frequency. One of 48000, 44100, 32000, 24000, 22050, 16000, 12000, 11050, 8000.
  *
  * @param channels - Number of channels. Pass 2 (stereo).
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioSRCChReserve(int samplecount, int freq, int channels);

/**
  * Release the audio output
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioSRCChRelease(void);

/**
  * Output audio
  *
  * @param vol - The volume.
  *
  * @param buf - Pointer to the PCM data to output.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioSRCOutputBlocking(int vol, void *buf);

/**
  * Init audio input
  *
  * @param unknown1 - Unknown. Pass 0.
  *
  * @param gain - Gain.
  *
  * @param unknown2 - Unknown. Pass 0.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioInputInit(int unknown1, int gain, int unknown2);

/**
  * Init audio input (with extra arguments)
  *
  * @param params - A pointer to a ::pspAudioInputParams struct.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioInputInitEx(pspAudioInputParams *params);

/**
  * Perform audio input (blocking)
  *
  * @param samplecount - Number of samples.
  *
  * @param freq - Either 44100, 22050 or 11025.
  *
  * @param buf - Pointer to where the audio data will be stored.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioInputBlocking(int samplecount, int freq, void *buf);

/**
  * Perform audio input
  *
  * @param samplecount - Number of samples.
  *
  * @param freq - Either 44100, 22050 or 11025.
  *
  * @param buf - Pointer to where the audio data will be stored.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioInput(int samplecount, int freq, void *buf);

/**
  * Get the number of samples that were acquired
  *
  * @return Number of samples acquired, an error if less than 0.
  */
int sceAudioGetInputLength(void);

/**
  * Wait for non-blocking audio input to complete
  *
  * @return 0 on success, an error if less than 0.
  */
int sceAudioWaitInputEnd(void);

/**
  * Poll for non-blocking audio input status
  *
  * @return 0 if input has completed, 1 if not completed or an error if less than 0.
  */
int sceAudioPollInputEnd(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSPAUDIO_H */
