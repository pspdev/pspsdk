/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Demonstrates some of sceSasCore library capabilities.
 *
 * Copyright (c) 2026 IsaacTCB
 *
 */

#include <pspaudio.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspsascore.h>
#include <pspuser.h>
#include <psputility.h>

#include <stdalign.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Define the module info section */
PSP_MODULE_INFO("sastest", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#define GRAIN_SIZE (PSP_SAS_GRAIN_SIZE)
#define PCM_FILE "sound.pcm.raw"
#define VAG_FILE "fanfare.vag"

typedef enum {
    SAMPLE_AUDIO_PCM = 0,
    SAMPLE_AUDIO_VAG = 1,
} AudioClipType;

typedef struct {
    AudioClipType type;
    void* ptr;
    size_t size;
    int sample_rate;
    int channels;
} AudioClip;

__attribute__((aligned(64))) SceSasCore core;
__attribute__((aligned(64))) int16_t mixer[GRAIN_SIZE * 4];

static int exit_callback(int arg1, int arg2, void *common);
static int callback_thread(SceSize args, void *argp);
static int setup_callbacks(void);

int sas_audio_load_pcm(AudioClip* pcm, const char* path, int sample_rate, int channels);
int sas_audio_load_vag(AudioClip* pcm, const char* path);
void sas_audio_unload(AudioClip* audio);

static void print_error(const char* message);

/* --------------------------- */
/*      Wrappers for SAS       */
/* --------------------------- */

void sas_init() {
    /* The following modules must be loaded in order for sceSasCore to work */
    int result = sceUtilityLoadModule(PSP_MODULE_AV_AVCODEC);
    if (result < 0) {
        pspDebugScreenPrintf("err: 0x%08X\n", result);
        print_error("Failed to init PSP_MODULE_AV_AVCODEC");
    }

    result = sceUtilityLoadModule(PSP_MODULE_AV_SASCORE);
    if (result < 0) {
        pspDebugScreenPrintf("err: 0x%08X\n", result);
        print_error("Failed to init PSP_MODULE_AV_SASCORE");
    }

    /* Initialize sceSasCore instance */
    result = __sceSasInit(&core, GRAIN_SIZE, PSP_SAS_VOICES_MAX, PSP_SAS_OUTPUTMODE_STEREO, PSP_SAS_SAMPLE_RATE);
    if (result < 0) {
        pspDebugScreenPrintf("err: 0x%08X\n", result);
        print_error("Failed to initialize sceSasCore");
    }
}

void sas_audio_play_voice(int voice, AudioClip* audio) {
    if (audio->channels != 1) {
        return; /* sceSas can only mix mono voices. */
    }

    /* Configure a voice for playback.
     * We have to always call this before playing a voice,
     * regardless if it's the same voice index with the same arguments or not. */
    int status;
    if (audio->type == SAMPLE_AUDIO_PCM) {
        const size_t samples = audio->size / sizeof(int16_t);
        status = __sceSasSetVoicePCM(&core, voice, audio->ptr, samples, -1);
    } else if (audio->type == SAMPLE_AUDIO_VAG) {
        const size_t adpcm_offset = 0x30;
        status = __sceSasSetVoice(&core, voice, audio->ptr + adpcm_offset, audio->size - adpcm_offset, 1);
    } else {
        /* Unsupported type */
        status = -1;
    }

    if (status < 0) {
        pspDebugScreenPrintf("err: 0x%08x\n", status);
        return;
    }

    /* Makes the sound play at its intended frequency */
    const int target_pitch = (audio->sample_rate * (size_t)(PSP_SAS_PITCH_BASE)) / PSP_SAS_SAMPLE_RATE;
    status = __sceSasSetPitch(&core, voice, target_pitch);

    /* Makes all curves instant. */
    const int flags = PSP_SAS_ADSR_ATTACK | PSP_SAS_ADSR_RELEASE;
    __sceSasSetADSRmode(
        &core, voice, flags,
        PSP_SAS_ADSR_CURVE_MODE_LINEAR_INCREASE, /* Attack curve */
        0, /* Decay curve */
        0, /* Sustain curve */
        PSP_SAS_ADSR_CURVE_MODE_DIRECT /* Release curve */
    );

    /* Makes the voice instantly start and stop. No attack or release nonsense. */
    const int rate = PSP_SAS_ENVELOPE_FREQ_MAX;
    __sceSasSetADSR(&core, voice, flags, rate, 0, 0, 0);

    /* Beware that __sceSas uses PSP_SAS_VOLUME_MAX (0x1000) as the
     * maximum voice volume, not PSP_AUDIO_VOLUME_MAX (which is 0x4000). */
    const int voice_vol = PSP_SAS_VOLUME_MAX;
    const int voice_effect_vol = voice_vol;
    __sceSasSetVolume(&core, voice, voice_vol, voice_vol, voice_effect_vol, voice_effect_vol);

    /* Finally, trigger the voice. */
    __sceSasSetKeyOn(&core, voice);
}

int sas_find_free_voice(uint32_t flags) {
    if (flags == 0) {
        return 0;
    }
    for (size_t i = 0; i < PSP_SAS_VOICES_MAX; i++) {
        if (PSP_SAS_GET_FLAG_AT(flags, i) == 1) {
            return i;
        }
    }
    return 0;
}

void sas_set_reverb(int reverb) {
    /* Enables/disables reverb (space) effect */
    const PspSasEffectTypes effect = (reverb) ? PSP_SAS_EFFECT_TYPE_SPACE : PSP_SAS_EFFECT_TYPE_OFF;
    __sceSasRevType(&core, effect);

    /* Enables/disables wet signal processing */
    __sceSasRevVON(&core, 1, reverb);

    /* Set effect volume */
    const int effect_vol = (reverb) ? PSP_SAS_VOLUME_MAX : 0;
    __sceSasRevEVOL(&core, effect_vol, effect_vol);
}

/* --------------------------- */
/*        Entrypoint           */
/* --------------------------- */

int main(void) {
    setup_callbacks();

    pspDebugScreenInit();

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    sas_init();

    int channel = sceAudioChReserve(PSP_AUDIO_NEXT_CHANNEL, GRAIN_SIZE, PSP_AUDIO_FORMAT_STEREO);
    if (channel < 0) {
        pspDebugScreenPrintf("err: 0x%08X\n", channel);
        print_error("Failed to initialize sceAudio channel!");
    }

    /* Load audio */
    AudioClip audio_pcm;
    if (!sas_audio_load_pcm(&audio_pcm, PCM_FILE, 44100, 1)) {
        print_error("failed to load: " PCM_FILE);
    }
    AudioClip audio_vag;
    if (!sas_audio_load_vag(&audio_vag, VAG_FILE)) {
        print_error("failed to load: " VAG_FILE);
    }

    /* Start with reverb disabled */
    int reverb = 0;
    sas_set_reverb(reverb);

    int fanfare_voice = -1;
    int refresh_screen = 1;
    int running = 1;

    while (running) {
        SceCtrlLatch latch;
        sceCtrlReadLatch(&latch);

        if (refresh_screen) {
            refresh_screen = 0;

            pspDebugScreenSetXY(0, 0);
            pspDebugScreenPrintf("sceSasCore sample\n\n");

            pspDebugScreenPrintf(PCM_FILE "\n");
            pspDebugScreenPrintf("- channels = %d\n", audio_pcm.channels);
            pspDebugScreenPrintf("- sample rate = %dhz\n\n", audio_pcm.sample_rate);

            pspDebugScreenPrintf(VAG_FILE "\n");
            pspDebugScreenPrintf("- channels = %d\n", audio_vag.channels);
            pspDebugScreenPrintf("- sample rate = %dhz\n\n", audio_vag.sample_rate);

            pspDebugScreenPrintf("Press CROSS play a sound effect\n");
            pspDebugScreenPrintf("Press SQUARE to play/stop fanfare loop\n");
            pspDebugScreenPrintf("Press TRIANGLE to %s reverb\n\n", reverb ? "disable" : "enable");
        }

        if (latch.uiMake) {
            /* Fetch list of voices that are currently NOT playing. */
            uint32_t flags = __sceSasGetEndFlag(&core);

            /* If cross is pressed, then play the PCM sound effect. */
            if (latch.uiMake & PSP_CTRL_CROSS) {
                int voice = sas_find_free_voice(flags);
                sas_audio_play_voice(voice, &audio_pcm);
                flags &= ~PSP_SAS_GET_VOICE_BIT(voice); /* Marks the bitflag as playing */

                if (fanfare_voice == voice) {
                    fanfare_voice = -1;
                }
            }

            /* If square is pressed, then start/stop the VAG fanfare loop. */
            if (latch.uiMake & PSP_CTRL_SQUARE) {
                if (fanfare_voice < 0 || PSP_SAS_GET_FLAG_AT(flags, fanfare_voice)) {
                    fanfare_voice = sas_find_free_voice(flags);
                    sas_audio_play_voice(fanfare_voice, &audio_vag);
                    flags &= ~PSP_SAS_GET_VOICE_BIT(fanfare_voice);

                    refresh_screen = 1;
                } else if (fanfare_voice >= 0) {
                    /* Stop fanfare voice */
                    __sceSasSetKeyOff(&core, fanfare_voice);
                    fanfare_voice = -1;
                    refresh_screen = 1;
                }
            }

            /* Toggles reverb on/off */
            if (latch.uiMake & PSP_CTRL_TRIANGLE) {
                refresh_screen = 1;
                reverb = !reverb;
                sas_set_reverb(reverb);
            }
        }

        /* Run a SAS cycle, which will update and process the voices. */
        __sceSasCore(&core, mixer);

        /* Finally, output the audio. */
        sceAudioOutputPannedBlocking(
            channel,
            PSP_AUDIO_VOLUME_MAX,
            PSP_AUDIO_VOLUME_MAX,
            mixer);
    }

    /* Close stuff (there's no function to close sceSasCore, btw) */
    sas_audio_unload(&audio_vag);
    sas_audio_unload(&audio_pcm);

    sceKernelExitGame();
    return 0;
}

/* --------------------------- */
/*    Audio file operations    */
/* --------------------------- */

int sas_audio_load_pcm(AudioClip* audio, const char* path, int sample_rate, int channels) {
    SceUID fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
    if (fd < 0) { return 0; }

    /* Ideally, we obtain the pcm by decoding/parsing a proper audio format
     * like as .wav, .mp3, .ogg, etc. However, that's out-of-scope for
     * this example. Instead we load a headerless uncompressed
     * signed 16-bit PCM directly. */
    size_t size = sceIoLseek(fd, 0, SEEK_END);
    uint8_t* data = (uint8_t*)aligned_alloc(16, size);
    sceIoLseek(fd, 0, SEEK_SET);
    sceIoRead(fd, data, size);
    sceIoClose(fd);

    if (!data) {
        sas_audio_unload(audio);
        return 0;
    }

    *audio = (AudioClip) {
        .type = SAMPLE_AUDIO_PCM,
        .ptr = data,
        .size = size,
        .sample_rate = sample_rate,
        .channels = channels,
    };
    return 1;
}

int sas_audio_load_vag(AudioClip* audio, const char* path) {
    /* .vag parser is trunk-down for simplicity-sake. */
    SceUID fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
    if (fd < 0) { return 0; }

    /* For .vag files, we only need to load the file in memory
     * because sceSas handles the decoding for us! */
    size_t size = sceIoLseek(fd, 0, SEEK_END);
    uint8_t* data = (uint8_t*)aligned_alloc(16, size);
    sceIoLseek(fd, 0, SEEK_SET);
    sceIoRead(fd, data, size);
    sceIoClose(fd);

    if (!data || size <= 32) {
        sas_audio_unload(audio);
        return 0;
    }

    /* VAGp */
    uint8_t* ptr = &data[0x0];
    if (!(ptr[0] == 'V' && ptr[1] == 'A' && ptr[2] == 'G' && ptr[3] == 'p')) {
        /* Magic failed, file is not a valid .vag */
        sas_audio_unload(audio);
        return 0;
    }

    /* Parse sample_rate (stored as big-endian) */
    ptr = &data[0x10];
    int sample_rate = 0;
    sample_rate |= (*ptr++) << 24;
    sample_rate |= (*ptr++) << 16;
    sample_rate |= (*ptr++) << 8;
    sample_rate |= (*ptr++) << 0;

    *audio = (AudioClip) {
        .type = SAMPLE_AUDIO_VAG,
        .ptr = data,
        .size = size,
        .sample_rate = sample_rate,
        .channels = 1, /* .vag only stores mono audio. */
    };
    return 1;
}

void sas_audio_unload(AudioClip* audio) {
    if (audio->ptr) {
        free(audio->ptr);
    }
}

/* --------------------------- */
/*    PSP boilerplate stuff    */
/* --------------------------- */

static int exit_callback(int arg1, int arg2, void *common) {
    sceKernelExitGame();
    return 0;
}

static int callback_thread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

static int setup_callbacks(void) {
    int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
    if(thid >= 0) {
        sceKernelStartThread(thid, 0, 0);
    }
    return thid;
}

static void print_error(const char* message) {
    pspDebugScreenPrintf("ERROR: %s\n\n", message);
    pspDebugScreenPrintf("Press CROSS to close this application.\n");
    SceCtrlData pad;
    while (1) {
        sceCtrlReadBufferPositive(&pad, 1);
        if (pad.Buttons & PSP_CTRL_CROSS) {
            break;
        }
    }
    sceKernelExitGame();
}
