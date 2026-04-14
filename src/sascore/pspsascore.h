/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsas.h - Prototypes for the sceSasCore library.
 *
 * Copyright (c) 2026 IsaacTCB
 *
 */

#ifndef __SCELIBSAS_H__
#define __SCELIBSAS_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SAS SAS Core Audio Library
  * This module contains the imports for sceSasCore, the PSP's audio software mixer.
  **/

/** @addtogroup SAS */

/**@{*/

#include <psptypes.h>

/**
 * @brief Macro utility to obtain the corresponding bit of a voice index.
 *
 * @param voice - The voice index, ranging from 0 to ::PSP_SAS_VOICES_MAX-1
 */
#define PSP_SAS_GET_VOICE_BIT(voice) (1u << (voice % 32))

/**
 * @brief Macro utility for reading voice bitfield flags.
 *
 * @param flags - The 32-bit bitfield representing each voice.
 *
 * @param voice - The voice index, ranging from 0 to ::PSP_SAS_VOICES_MAX-1
 */
#define PSP_SAS_GET_FLAG_AT(flags, voice) (((flags) & (PSP_SAS_GET_VOICE_BIT(voice))) != 0)

/** The recommended sceSasCore grain size that's used by most games. */
#define PSP_SAS_GRAIN_SIZE (256)

/** The minimum sceSasCore grain size */
#define PSP_SAS_GRAIN_SIZE_MIN (64)

/** The maximum sceSasCore grain size */
#define PSP_SAS_GRAIN_SIZE_MAX (2048)

/** The maximum number of voices that sceSas can playback all at once */
#define PSP_SAS_VOICES_MAX (32)

/** The sample rate of sceSasCore mixer */
#define PSP_SAS_SAMPLE_RATE (44100)

/** The maximum output volume of sceSas voices. */
#define PSP_SAS_VOLUME_MAX (0x1000)

/** Represents 1x voice pitch. */
#define PSP_SAS_PITCH_BASE (0x1000)

/** The minimum supported voice pitch */
#define PSP_SAS_PITCH_MIN (0x1)

/** The maximum supported voice pitch */
#define PSP_SAS_PITCH_MAX (0x4000)

/** The maximum noise frequency */
#define PSP_SAS_NOISE_FREQ_MAX (0x3F)

/** Represents maximum ADSR envelope height. */
#define PSP_SAS_ENVELOPE_HEIGHT_MAX (0x40000000)

/** Represents maximum ADSR envelope frequency. */
#define PSP_SAS_ENVELOPE_FREQ_MAX (0x7FFFFFFF)

typedef enum {
    /** Interleaved stereo output (L/R), with dry + send already mixed together. */
    PSP_SAS_OUTPUTMODE_STEREO = 0,
    /** 4 separate output buffers: L, R, Send-L, Send-R (each planar, not interleaved). */
    PSP_SAS_OUTPUTMODE_MULTICHANNEL = 1,
} PspSasOutputModes;

typedef enum {
    PSP_SAS_EFFECT_TYPE_OFF    = -1,
    PSP_SAS_EFFECT_TYPE_ROOM   = 0,
    PSP_SAS_EFFECT_TYPE_SMALL  = 1,
    PSP_SAS_EFFECT_TYPE_MEDIUM = 2,
    PSP_SAS_EFFECT_TYPE_LARGE  = 3,
    PSP_SAS_EFFECT_TYPE_HALL   = 4,
    PSP_SAS_EFFECT_TYPE_SPACE  = 5,
    PSP_SAS_EFFECT_TYPE_ECHO   = 6,
    PSP_SAS_EFFECT_TYPE_DELAY  = 7,
    PSP_SAS_EFFECT_TYPE_PIPE   = 8,
} PspSasEffectTypes;

/** ADSR envelope curve modes */
typedef enum {
    /** Equivalent to `height += rate` */
    PSP_SAS_ADSR_CURVE_MODE_LINEAR_INCREASE = 0,
    /** Equivalent to `height -= rate` */
    PSP_SAS_ADSR_CURVE_MODE_LINEAR_DECREASE = 1,
    PSP_SAS_ADSR_CURVE_MODE_LINEAR_BENT     = 2,
    PSP_SAS_ADSR_CURVE_MODE_EXPONENT_REV    = 3,
    PSP_SAS_ADSR_CURVE_MODE_EXPONENT        = 4,
    /** Equivalent to `height = rate` */
    PSP_SAS_ADSR_CURVE_MODE_DIRECT          = 5,
} PspSasADSRCurveModes;

/** Error codes used as return values by sceSasCore. */
enum PspSasErrorCodes {
    PSP_SAS_ERROR_ADDRESS        = 0x80420005,
    PSP_SAS_ERROR_VOICE_INDEX    = 0x80420010,
    PSP_SAS_ERROR_NOISE_CLOCK    = 0x80420011,
    PSP_SAS_ERROR_PITCH_VAL      = 0x80420012,
    PSP_SAS_ERROR_ADSR_MODE      = 0x80420013,
    PSP_SAS_ERROR_ADPCM_SIZE     = 0x80420014,
    PSP_SAS_ERROR_LOOP_MODE      = 0x80420015,
    PSP_SAS_ERROR_INVALID_STATE  = 0x80420016,
    PSP_SAS_ERROR_VOLUME_VAL     = 0x80420018,
    PSP_SAS_ERROR_ADSR_VAL       = 0x80420019,
    PSP_SAS_ERROR_FX_TYPE        = 0x80420020,
    PSP_SAS_ERROR_FX_FEEDBACK    = 0x80420021,
    PSP_SAS_ERROR_FX_DELAY       = 0x80420022,
    PSP_SAS_ERROR_FX_VOLUME_VAL  = 0x80420023,
    PSP_SAS_ERROR_BUSY           = 0x80420030,
    PSP_SAS_ERROR_NOTINIT        = 0x80420100,
    PSP_SAS_ERROR_ALRDYINIT      = 0x80420101,
};

/** ADSR envelope flags */
enum PspSasADSRFlags {
    PSP_SAS_ADSR_ATTACK  = 1,
    PSP_SAS_ADSR_DECAY   = 2,
    PSP_SAS_ADSR_SUSTAIN = 4,
    PSP_SAS_ADSR_RELEASE = 8,
};

#define PSP_SAS_ADSR_EVERYTHING (PSP_SAS_ADSR_ATTACK | PSP_SAS_ADSR_DECAY | PSP_SAS_ADSR_SUSTAIN | PSP_SAS_ADSR_RELEASE)

/**
 * @brief Contains all data related to a sceSasCore state.
 *
 * Developers are not meant to interact with this structure directly. Always prefer
 * to use the public functions over reading/writing values from here.
 */
typedef struct {
    u8 pad[3616];
} SceSasCore;

/**
 * @brief Initializes a SceSasCore instance.
 *
 * Make sure to load ::PSP_MODULE_AV_AVCODEC and ::PSP_MODULE_AV_SASCORE
 * with ::sceUtilityLoadModule or ::sceUtilityLoadAvModule before calling this function.
 *
 * @param core - Pointer to SceSasCore for initialization. Must be 64-byte aligned.
 *
 * @param grainsize - Tells how many frames (samples per channel) the mixer will process and output per iteration.
 *                    It must be a value between ::PSP_SAS_GRAIN_SIZE_MIN and ::PSP_SAS_GRAIN_SIZE_MAX, and it
 *                    must be a multiple of 64.
 *
 * @param maxvoices - The maximum number of voices SceSasCore will process. It must be a number between 1 and
 *                    ::PSP_SAS_VOICES_MAX.
 *
 * @param outputmode - The output mode to use. One of ::PspSasOutputModes.
 *
 * @param samplerate - Must be ::PSP_SAS_SAMPLE_RATE (44100). Any other value will result in an error.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasInit(SceSasCore* core, int grainsize, int maxvoices, PspSasOutputModes outputmode, int samplerate);

/**
 * @brief Gets the current output mode from the SceSasCore instance.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @return One of ::PspSasOutputModes on success, an error code if less than 0.
 */
int __sceSasGetOutputmode(SceSasCore* core);

/**
 * @brief Sets the current output mode of the SceSasCore instance.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param outputmode - The output mode to use. One of ::PspSasOutputModes.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetOutputmode(SceSasCore* core, PspSasOutputModes outputmode);

/**
 * @brief Sets the reverb effect of the SceSasCore instance.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param type - The reverb effect to use. One of ::PspSasEffectTypes.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasRevType(SceSasCore* core, PspSasEffectTypes type);

/**
 * @brief Sets the effect volume of the SceSasCore instance.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param leftvol - Must be a number between 0 and ::PSP_SAS_VOLUME_MAX.
 *
 * @param rightvol - Must be a number between 0 and ::PSP_SAS_VOLUME_MAX.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasRevEVOL(SceSasCore* core, int leftvol, int rightvol);

/**
 * @brief Toggles dry and wet audio signals of the SceSasCore instance.
 *
 * @param core - A valid sceSas instance.
 *
 * @param dry - Enable/disable dry signal.
 *
 * @param wet - Enable/disable wet/send signal.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasRevVON(SceSasCore* core, int dry, int wet);

/**
 * @brief Sets the effect delay and feedback parameters of the SceSasCore instance.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param delay - Must be a number between 0 and 128.
 *
 * @param feedback - Must be a number between 0 and 128.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasRevParam(SceSasCore* core, int delay, int feedback);

/**
 * @brief Gets the grain size of the SceSasCore instance.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @return The grain size on success, an error code if less than 0.
 */
int __sceSasGetGrain(SceSasCore* core);

/**
 * @brief Sets the grain size of the SceSasCore instance.
 *
 * @param core - A valid sceSas instance.
 *
 * @param grainsize - The new grain size to set. It must be a value between ::PSP_SAS_GRAIN_SIZE_MIN and ::PSP_SAS_GRAIN_SIZE_MAX,
 *                    and it must be a multiple of 64.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetGrain(SceSasCore* core, int grainsize);

/**
 * @brief Gets the end status of the voices from an SceSasCore nstance.
 *
 * Each bit corresponds to a voice index:
 * - Bit N == 1 -> voice N has ended.
 * - Bit N == 0 -> voice N is currently playing.
 *
 * @note On real hardware, the end flags are refreshed only
 * *AFTER* ::__sceSasCore is called.
 *
 * @param core - Pointer to a valid Sas instance
 *
 * @return 32-bit bitmask of voice end flags. To read a specific
 * voice bit, use ::PSP_SAS_GET_FLAG_AT.
 */
u32 __sceSasGetEndFlag(SceSasCore* core);

/**
 * @brief Sets PlayStation VAG data for a given sceSas voice
 *
 * - For raw PCM playback, see ::__sceSasSetVoicePCM.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index.
 *
 * @param vag - A stable pointer to VAG data.
 *
 * @param size - The size in bytes of the VAG file.
 *
 * @param loop - Whether this voice should loop or not. The VAG file itself has to
 *               contain the end loop flag in its data in order for looping to work.
 *               Must be 0 or 1.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetVoice(SceSasCore* core, int voice, void* vag, int size, int loop);

/**
 * @brief Sets PCM data for the given sceSas voice
 *
 * - For PlayStation VAG playback, see ::__sceSasSetVoice.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index.
 *
 * @param pcm - A stable pointer to the audio PCM data. The audio *MUST* be mono
 *              and its format *HAS* to be in 16-bit signed integer (little-endian).
 *
 * @param samplecount - The amount of samples the voice will play.
 *
 * @param loopstart - The sample position the loop will start from. Pass -1 to disable looping.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetVoicePCM(SceSasCore* core, int voice, void* pcm, int samplecount, int loopstart);

/**
 * @brief Plays the voice (starts Attack phase).
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetKeyOn(SceSasCore* core, int voice);

/**
 * @brief Stops the voice (starts Release phase).
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetKeyOff(SceSasCore* core, int voice);

/**
 * @brief Sets the pitch value of a voice.
 *
 * Can be used to set the playback speed of the voice.
 * For waveform voices (such as steep/triangular/noise waves),
 * this value gets treated as the tonal frequency (in hertz).
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index.
 *
 * @param pitch - Fixed-point ratio where ::PSP_SAS_PITCH_BASE means 1x in pitch-scale,
 *                or the tonal frequency (in hertz) of waveform voices. It must be a
 *                number between ::PSP_SAS_PITCH_MIN ad ::PSP_SAS_PITCH_MAX.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetPitch(SceSasCore* core, int voice, int pitch);

/**
 * @brief Sets the voice ADSR envelope curves.
 *
 * Configures "how" the envelope progresses through its Attack, Decay,
 * Sustain, and Release phases. Often used alongside ::__sceSasSetADSR to
 * set the envelope rates.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index.
 *
 * @param mask - Bitmask selecting which ADSR parameters to update.
 *               Use ::PspSasADSRFlags values or ::PSP_SAS_ADSR_EVERYTHING.
 *
 * @param attackcurve - Attack step curve. One of ::PspSasADSRCurveModes
 *
 * @param decaycurve - Decay step curve. One of ::PspSasADSRCurveModes
 *
 * @param sustaincurve - Sustain step curve. One of ::PspSasADSRCurveModes
 *
 * @param releasecurve - Release step curve. One of ::PspSasADSRCurveModes
 *
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetADSRmode(SceSasCore* core, int voice, u32 mask, PspSasADSRCurveModes attackcurve, PspSasADSRCurveModes decaycurve, PspSasADSRCurveModes sustaincurve, PspSasADSRCurveModes releasecurve);

/**
 * @brief Sets the voice ADSR envelope rates for a voice.
 *
 * Configures how fast the envelope progresses through its Attack, Decay,
 * Sustain, and Release phases.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index.
 *
 * @param mask - Bitmask selecting which ADSR parameters to update.
 *               Use ::PspSasADSRFlags values or ::PSP_SAS_ADSR_EVERYTHING.
 *
 * @param attackrate - Attack step rate (rise towards ::PSP_SAS_ENVELOPE_HEIGHT_MAX).
 *
 * @param decayrate - Decay step rate (fall towards sustain level).
 *
 * @param sustainrate - Sustain phase rate (envelope change while key is held)
 *
 * @param releaserate - Release step rate (fall toward 0 after key is off).
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetADSR(SceSasCore* core, int voice, u32 mask, int attackrate, int decayrate, int sustainrate, int releaserate);

/**
 * @brief Configures the entire voice ADSR envelope (rates & curves).
 *
 * @todo Explain how to set ADSR parameters via `envelope1` and `envelope2`.
 *
 * This is used to set the entire ADSR envelope
 * in a single call, acting as a replacement to
 * ::__sceSasSetADSR and ::__sceSasSetADSRmode.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index.
 *
 * @param envelope1 - First envelope config value.
 *
 * @param envelope2 - Second envelope config value.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetSimpleADSR(SceSasCore* core, int voice, u32 envelope1, u32 envelope2);

/**
 * @brief Sets the voice ADSR envelope sustain level height.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index.
 *
 * @param level - A number between 0 and ::PSP_SAS_ENVELOPE_HEIGHT_MAX
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetSL(SceSasCore* core, int voice, int level);

/**
 * @brief Sets the output volume of the voice.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index.
 *
 * @param leftvol - Left dry channel volume. Must be a number between 0 and ::PSP_SAS_VOLUME_MAX.
 *
 * @param rightvol - Right dry channel volume. Must be a number between 0 and ::PSP_SAS_VOLUME_MAX.
 *
 * @param sendleftvol - Send-Left channel volume. Must be a number between 0 and ::PSP_SAS_VOLUME_MAX.
 *
 * @param sendrightvol - Send-Right channel volume. Must be a number between 0 and ::PSP_SAS_VOLUME_MAX.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetVolume(SceSasCore* core, int voice, int leftvol, int rightvol, int sendleftvol, int sendrightvol);

/**
 * @brief Runs a sceSas cycle iteration and outputs samples onto destination buffer.
 *
 * This is the heart of sceSasCore, hence its name. Processes and updates
 * voices, mixes them together and updates end/pause flags.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param dst - A destination buffer of N bytes, where `N == (grainSize * 4 * sizeof(int16_t))`.
 *              The data layout gets decided from the current output mode, which is one of ::PspSasOutputModes.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasCore(SceSasCore* core, void* dst);

/**
 * @brief Runs a sceSas cycle iteration and mixes samples onto destination buffer.
 *
 * This is similar to ::__sceSasCore, except that the destination buffer does not get cleared.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param dst - A destination buffer of N bytes, where `N == (grainSize * 4 * sizeof(int16_t))`.
 *              The data layout gets decided from the current output mode, which is one of ::PspSasOutputModes.
 *
 * @param leftvol - A number between 0 and ::PSP_SAS_VOLUME_MAX.
 *
 * @param rightvol - A number between 0 and ::PSP_SAS_VOLUME_MAX.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasCoreWithMix(SceSasCore* core, void* dst, int leftvol, int rightvol);

/**
 * @brief Get the pause status of every voice in a bitfield.
 *
 * Each bit corresponds to a voice index:
 * - Bit N == 1 -> voice N is paused.
 * - Bit N == 0 -> voice N is currently playing.
 *
 * @param core - Pointer to a valid Sas instance
 *
 * @return 32-bit bitmask of voice pause flags. To read a specific
 * voice bit, use ::PSP_SAS_GET_FLAG_AT.
 */
int __sceSasGetPauseFlag(SceSasCore* core);

/**
 * @brief Gets the current envelope height of a voice.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The voice index to read from.
 *
 * @return The voice height, ranging from 0 and ::PSP_SAS_ENVELOPE_HEIGHT_MAX
 *         on success, an error code if less than 0.
 */
int __sceSasGetEnvelopeHeight(SceSasCore* core, int voice);

/**
 * @brief Gets the current envelope height of all voices.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param heights - An `int` array of 32 indices where the results will be inserted into.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasGetAllEnvelopeHeights(SceSasCore* core, int heights[32]);

/**
 * @brief Pauses/unpauses voice playback using a bitmask.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voicebit - 32-bit bitmask selecting which voices to
 *                   update. Each bit corresponds to a voice index.
 *                   You can use ::PSP_SAS_GET_VOICE_BIT to convert a voice
 *                   index into a proper bitmask.
 *
 * @param pause - Whether to pause or unpause the selected voices
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetPause(SceSasCore* core, u32 voicebit, int pause);

/**
 * @brief Configures the voice to play a noise waveform.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index
 *
 * @param freq - How often the wave will randomly alternate? Must be a number from 0 to
 *               ::PSP_SAS_NOISE_FREQ_MAX.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetNoise(SceSasCore* core, int voice, int freq);

/**
 * @brief Configures the voice to play a triangular waveform.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index
 *
 * @param unk - Unsure. Probably duty cycle + some other thing that gets packed into 7 bits?
 *              Apparently it must be a number from 0 to 100.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetTrianglarWave(SceSasCore* core, int voice, int unk);

/** @brief A function alias of ::__sceSasSetTrianglarWave. */
int __sceSasSetTriangularWave(SceSasCore* core, int voice, int unk);

/**
 * @brief Configures the voice to play a square waveform.
 *
 * @param core - Pointer to a valid sceSas instance.
 *
 * @param voice - The target voice index
 *
 * @param duty - The percentage of the square's duty cycle (e.g. a value of 50 means
 *               a symmetrical 50% duty cycle). Must be a number from 0 to 100.
 *
 * @return 0 on success, an error code if less than 0.
 */
int __sceSasSetSteepWave(SceSasCore* core, int voice, int duty);

/* TODO: Expose Atrac3 context struct */
int __sceSasSetVoiceATRAC3(SceSasCore* core, int voice, void* atrac3ctx);
int __sceSasConcatenateATRAC3(SceSasCore* core, int voice, void* data, int size);
int __sceSasUnsetATRAC3(SceSasCore* core, int voice);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* __SCELIBSAS_H__ */
