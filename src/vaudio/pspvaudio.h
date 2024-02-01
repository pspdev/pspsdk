/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspvaudio.h - Prototypes for the sceVaudio library.
 *
 * Copyright (c) 2024 Sergey Galushko
 *
 */
#ifndef PSPVAUDIO_H
#define PSPVAUDIO_H

#ifdef __cplusplus
extern "C" {
#endif

/** The maximum output volume. */
#define PSP_VAUDIO_VOLUME_MAX       0x8000

/** The maximum number of samples that can be allocated to a channel. */

#define PSP_VAUDIO_SAMPLE_MAX       2048

/** The minimum number of samples that can be allocated to a channel. */
#define PSP_VAUDIO_SAMPLE_MIN       256


/** Channel is set to mono output. */
#define PSP_VAUDIO_FORMAT_MONO      1

/** Channel is set to stereo output. */
#define PSP_VAUDIO_FORMAT_STEREO    2

/** Effect type  */
#define PSP_VAUDIO_EFFECT_OFF       0
#define PSP_VAUDIO_EFFECT_HEAVY     1
#define PSP_VAUDIO_EFFECT_POPS      2
#define PSP_VAUDIO_EFFECT_JAZZ      3
#define PSP_VAUDIO_EFFECT_UNIQUE    4
#define PSP_VAUDIO_EFFECT_MAX       5

/** Alc mode  */
#define PSP_VAUDIO_ALC_OFF          0
#define PSP_VAUDIO_ALC_MODE1        1
#define PSP_VAUDIO_ALC_MODE_MAX     2

/**
  * Output audio (blocking)
  *
  * @param volume - It must be a value between 0 and ::PSP_VAUDIO_VOLUME_MAX
  * @param buffer - Pointer to the PCM data to output.
  *
  * @return 0 on success, an error if less than 0.
  */
int sceVaudioOutputBlocking(int volume, void *buffer);

/**
  * Allocate and initialize a virtual output channel.
  *
  * @param samplecount - The number of samples that can be output on the channel per
  *                      output call. One of 256, 576, 1024, 1152, 2048.
  *                      It must be a value between ::PSP_VAUDIO_SAMPLE_MIN and ::PSP_VAUDIO_SAMPLE_MAX.
  * @param frequency - The frequency. One of 48000, 44100, 32000, 24000, 22050, 16000, 12000, 11050, 8000.
  * @param format - The output format to use for the channel. One of ::PSP_VAUDIO_FORMAT_
  *
  * @return 0 if success, < 0 on error.
  */
int sceVaudioChReserve(int samplecount, int frequency, int format);

/**
  * Release  a virtual output channel.
  *
  * @return 0 if success, < 0 on error.
  */
int sceVaudioChRelease(void);

/**
  * Set effect type
  *
  * @param effect - The effect type. One of ::PSP_VAUDIO_EFFECT_
  * @param volume - The volume. It must be a value between 0 and ::PSP_VAUDIO_VOLUME_MAX
  *
  * @return The volume value on success, < 0 on error.
  */
int sceVaudioSetEffectType(int effect, int volume);

/**
  * Set ALC(dynamic normalizer)
  *
  * @param mode - The mode. One of ::PSP_VAUDIO_ALC_
  *
  * @return 0 if success, < 0 on error.
  */
int sceVaudioSetAlcMode(int mode);

#ifdef __cplusplus
}
#endif

#endif /* PSPVAUDIO_H */
