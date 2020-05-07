/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic audio sample.
 *
 * Copyright (c) 2005 Frank Buss <fb@frank-buss.de> (aka Shine)
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspaudiolib.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("POLYPHONIC", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

void dump_threadstatus(void);

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	sceKernelExitGame();

	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", (void *) exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

int  pspAudioInit();
void pspAudioEndPre();
void pspAudioEnd();

#define SAMPLE_COUNT 0x10000
float sample[SAMPLE_COUNT];

#define SAMPLE_RATE 44100

#define OCTAVE_COUNT 6

float octaves[OCTAVE_COUNT][12];

typedef struct {
	int note;
	int octave;
	int duration;
} Note_t;

typedef struct {
	Note_t currentNote;
	int noteIndex;
	int currentTime;
	float currentsampleIndex;
	float currentsampleIncrement;
} ChannelState_t;

ChannelState_t channelStates[3];

// "S" means "#"
#define NOTE_END -2
#define NOTE_PAUSE -1
#define NOTE_C 0
#define NOTE_CS 1
#define NOTE_D 2
#define NOTE_DS 3
#define NOTE_E 4
#define NOTE_F 5
#define NOTE_FS 6
#define NOTE_G 7
#define NOTE_GS 8
#define NOTE_A 9
#define NOTE_AS 10
#define NOTE_B 11

#define EIGHT_NOTE(note, octave, duration) { note, octave, SAMPLE_RATE * duration / 8}

Note_t channel0[] = {
	EIGHT_NOTE(NOTE_D, 4, 7),
	EIGHT_NOTE(NOTE_E, 4, 1),
	EIGHT_NOTE(NOTE_F, 4, 1),
	EIGHT_NOTE(NOTE_E, 4, 1),
	EIGHT_NOTE(NOTE_F, 4, 1),
	EIGHT_NOTE(NOTE_E, 4, 1),
	EIGHT_NOTE(NOTE_A, 3, 9),
	EIGHT_NOTE(NOTE_B, 3, 2),
	EIGHT_NOTE(NOTE_C, 4, 1),
	EIGHT_NOTE(NOTE_D, 4, 7),
	EIGHT_NOTE(NOTE_E, 4, 1),
	EIGHT_NOTE(NOTE_F, 4, 1),
	EIGHT_NOTE(NOTE_E, 4, 1),
	EIGHT_NOTE(NOTE_F, 4, 1),
	EIGHT_NOTE(NOTE_E, 4, 1),
	EIGHT_NOTE(NOTE_A, 3, 9),
	EIGHT_NOTE(NOTE_G, 3, 3),
	EIGHT_NOTE(NOTE_A, 3, 7),
	EIGHT_NOTE(NOTE_B, 3, 1),
	EIGHT_NOTE(NOTE_C, 4, 1),
	EIGHT_NOTE(NOTE_B, 3, 1),
	EIGHT_NOTE(NOTE_C, 4, 1),
	EIGHT_NOTE(NOTE_B, 3, 1),
	EIGHT_NOTE(NOTE_E, 3, 9),
	EIGHT_NOTE(NOTE_F, 3, 2),
	EIGHT_NOTE(NOTE_G, 3, 1),
	EIGHT_NOTE(NOTE_A, 3, 7),
	EIGHT_NOTE(NOTE_B, 3, 1),
	EIGHT_NOTE(NOTE_C, 4, 1),
	EIGHT_NOTE(NOTE_B, 3, 1),
	EIGHT_NOTE(NOTE_C, 4, 1),
	EIGHT_NOTE(NOTE_B, 3, 1),
	EIGHT_NOTE(NOTE_E, 3, 12),
	EIGHT_NOTE(NOTE_D, 4, 9),
	EIGHT_NOTE(NOTE_C, 4, 3),
	EIGHT_NOTE(NOTE_B, 3, 6),
	EIGHT_NOTE(NOTE_A, 3, 6),
	EIGHT_NOTE(NOTE_D, 4, 7),
	EIGHT_NOTE(NOTE_E, 4, 1),
	EIGHT_NOTE(NOTE_E, 4, 1),
	EIGHT_NOTE(NOTE_C, 4, 1),
	EIGHT_NOTE(NOTE_B, 3, 1),
	EIGHT_NOTE(NOTE_C, 4, 1),
	EIGHT_NOTE(NOTE_B, 3, 6),
	EIGHT_NOTE(NOTE_A, 3, 6),
	EIGHT_NOTE(NOTE_C, 4, 9),
	EIGHT_NOTE(NOTE_B, 3, 3),
	EIGHT_NOTE(NOTE_E, 3, 12),
	EIGHT_NOTE(NOTE_C, 4, 7),
	EIGHT_NOTE(NOTE_D, 4, 1),
	EIGHT_NOTE(NOTE_C, 4, 1),
	EIGHT_NOTE(NOTE_B, 3, 1),
	EIGHT_NOTE(NOTE_C, 4, 1),
	EIGHT_NOTE(NOTE_B, 3, 1),
	EIGHT_NOTE(NOTE_E, 3, 12),
	{ NOTE_END, 0, 0 }
};

Note_t channel1[] = {
	EIGHT_NOTE(NOTE_D, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_A, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_D, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_A, 0, 1),
	EIGHT_NOTE(NOTE_E, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_B, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_B, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_E, 1, 1),
	EIGHT_NOTE(NOTE_A, 0, 1),
	EIGHT_NOTE(NOTE_E, 1, 1),
	EIGHT_NOTE(NOTE_D, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_A, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_D, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_A, 0, 1),
	EIGHT_NOTE(NOTE_E, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_B, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_B, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_E, 1, 1),
	EIGHT_NOTE(NOTE_A, 0, 1),
	EIGHT_NOTE(NOTE_E, 1, 1),
	EIGHT_NOTE(NOTE_F, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_G, 2, 1),
	EIGHT_NOTE(NOTE_A, 2, 1),
	EIGHT_NOTE(NOTE_C, 3, 1),
	EIGHT_NOTE(NOTE_A, 2, 1),
	EIGHT_NOTE(NOTE_G, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_F, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_C, 1, 1),
	EIGHT_NOTE(NOTE_G, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_G, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_G, 1, 1),
	EIGHT_NOTE(NOTE_C, 1, 1),
	EIGHT_NOTE(NOTE_G, 1, 1),
	EIGHT_NOTE(NOTE_F, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_G, 2, 1),
	EIGHT_NOTE(NOTE_A, 2, 1),
	EIGHT_NOTE(NOTE_C, 3, 1),
	EIGHT_NOTE(NOTE_A, 2, 1),
	EIGHT_NOTE(NOTE_G, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_F, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_C, 1, 1),
	EIGHT_NOTE(NOTE_G, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_G, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_G, 1, 1),
	EIGHT_NOTE(NOTE_C, 1, 1),
	EIGHT_NOTE(NOTE_G, 1, 1),
	EIGHT_NOTE(NOTE_D, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_A, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_D, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_A, 0, 1),
	EIGHT_NOTE(NOTE_E, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_B, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_B, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_E, 1, 1),
	EIGHT_NOTE(NOTE_A, 0, 1),
	EIGHT_NOTE(NOTE_E, 1, 1),
	EIGHT_NOTE(NOTE_D, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_A, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_D, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_A, 0, 1),
	EIGHT_NOTE(NOTE_E, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_B, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_B, 1, 1),
	EIGHT_NOTE(NOTE_A, 1, 1),
	EIGHT_NOTE(NOTE_E, 1, 1),
	EIGHT_NOTE(NOTE_A, 0, 1),
	EIGHT_NOTE(NOTE_E, 1, 1),
	EIGHT_NOTE(NOTE_F, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_G, 2, 1),
	EIGHT_NOTE(NOTE_A, 2, 1),
	EIGHT_NOTE(NOTE_C, 3, 1),
	EIGHT_NOTE(NOTE_A, 2, 1),
	EIGHT_NOTE(NOTE_G, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_F, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_C, 1, 1),
	EIGHT_NOTE(NOTE_G, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_G, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_G, 1, 1),
	EIGHT_NOTE(NOTE_C, 1, 1),
	EIGHT_NOTE(NOTE_G, 1, 1),
	EIGHT_NOTE(NOTE_F, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_G, 2, 1),
	EIGHT_NOTE(NOTE_A, 2, 1),
	EIGHT_NOTE(NOTE_C, 3, 1),
	EIGHT_NOTE(NOTE_A, 2, 1),
	EIGHT_NOTE(NOTE_G, 2, 1),
	EIGHT_NOTE(NOTE_F, 2, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_F, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_C, 1, 1),
	EIGHT_NOTE(NOTE_G, 1, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_G, 2, 1),
	EIGHT_NOTE(NOTE_E, 2, 1),
	EIGHT_NOTE(NOTE_D, 2, 1),
	EIGHT_NOTE(NOTE_C, 2, 1),
	EIGHT_NOTE(NOTE_G, 1, 1),
	EIGHT_NOTE(NOTE_C, 1, 1),
	EIGHT_NOTE(NOTE_G, 1, 1),
	{ NOTE_END, 0, 0 }
};

Note_t* channels[] = { channel0, channel1 };

void nextNote(int channel)
{
	ChannelState_t* state = &channelStates[channel];
	state->currentNote = channels[channel][state->noteIndex];
	state->currentTime = 0;
	state->currentsampleIndex = 0;
	int note = state->currentNote.note;
	if (note == NOTE_PAUSE) {
		state->currentsampleIncrement = 0;
	} else {
		state->currentsampleIncrement = octaves[state->currentNote.octave][note] * ((float) SAMPLE_COUNT) / ((float) SAMPLE_RATE);
	}

	state->noteIndex++;
	if (channels[channel][state->noteIndex].note == NOTE_END) state->noteIndex = 0;
}

// calculate current value of attack/delay/sustain/release envelope
float adsr(float time, float duration) {
	if (time < 0.0) return 0.0;
	const float attack = 0.004;
	const float decay = 0.02;
	const float sustain = 0.5;
	const float release = 0.08;
	duration -= attack + decay + release;
	if (time < attack) return time / attack;
	time -= attack;
	if (time < decay) return (decay - time) / decay * (1.0 - sustain) + sustain;
	time -= decay;
	if (time < duration) return sustain;
	time -= duration;
	if (time < release) return (release - time) / release * sustain;
	return 0.0;
}

void audioOutCallback(int channel, unsigned short* buf, unsigned int reqn)
{
	ChannelState_t* state = &channelStates[channel];
	unsigned int i;
	for (i = 0; i < reqn; i++) {
		float time = ((float) state->currentTime) / ((float) SAMPLE_RATE);
		if (state->currentTime++ == state->currentNote.duration) nextNote(channel);
		float value;
		if (state->currentsampleIncrement == 0.0) {
			value = 0.0;
		} else {
			value = sample[(int)state->currentsampleIndex] * adsr(time, ((float) state->currentNote.duration) / ((float) SAMPLE_RATE));
			value *= (float) 0x7000;
			state->currentsampleIndex += state->currentsampleIncrement;
			if (state->currentsampleIndex >= SAMPLE_COUNT) state->currentsampleIndex -= (float) SAMPLE_COUNT;
		}
		buf[0] = value;
		buf[1] = value;
		buf += 2;
	}
}

void audioOutCallback0(void *buf, unsigned int reqn, void *userdata) { audioOutCallback(0, buf, reqn); }
void audioOutCallback1(void *buf, unsigned int reqn, void *userdata) { audioOutCallback(1, buf, reqn); }

void createPitches(float base, float* target)
{
	int i;
	for (i = 0; i < 12; i++) {
		target[i] = base;
		base *= 1.0594630943592952645618252949463;  // 2^(1/12)
	}
}

int main(void)
{
	pspDebugScreenInit();
	SetupCallbacks();
	printf("Polyphonic sample by Shine\n\n");
	printf("Soundtrack of the movie\n");
	printf("\"Le fabuleux destin d'Amelie Poulain\"\n");
	printf("by Yann Tiersen\n");

        int i;
	int maxAt = SAMPLE_COUNT / 16;
	for (i = 0; i < SAMPLE_COUNT; i++) {
		float value;
		if (i < maxAt) {
			value = ((float) i) / ((float) maxAt) * 2.0 - 1.0;
		} else {
			value = 1.0 - ((float) (i - maxAt)) / ((float) (SAMPLE_COUNT - maxAt)) * 2.0;
		}
		sample[i] = value;
	}
	float base = 40.0;
	for (i = 0; i < OCTAVE_COUNT; i++) {
		createPitches(base, octaves[i]);
		base *= 2;
	}
	channelStates[0].noteIndex = 0; nextNote(0);
	channelStates[1].noteIndex = 0; nextNote(1);

	pspAudioInit();
	pspAudioSetVolume(0, 0x4000, 0x4000);
	pspAudioSetVolume(1, 0x4000, 0x4000);
	pspAudioSetChannelCallback(0, audioOutCallback0, NULL);
	pspAudioSetChannelCallback(1, audioOutCallback1, NULL);
	sceKernelSleepThread();

	return 0;
}
