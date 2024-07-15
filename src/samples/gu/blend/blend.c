/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <pspgu.h>

#include "../common/callbacks.h"

PSP_MODULE_INFO("Blend Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
	float u,v;
	unsigned int color;
	float x,y,z;
};

struct BlendState
{
	char* name;
	int op;
	int src;
	int dest;
	unsigned int srcfix;
	unsigned int destfix;
};

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

#define NUM_SLICES 128
#define NUM_ROWS 128
#define RING_SIZE 2.0f
#define RING_RADIUS 1.0f
#define SPRITE_SIZE 0.025f

unsigned int __attribute__((aligned(16))) clut256[256];
unsigned char __attribute__((aligned(16))) tex256[256*256];

struct BlendState states[] =
{
	{"GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA", GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0},
	{"GU_SUBTRACT, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA", GU_SUBTRACT, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0},
	{"GU_ALPHA_ADD, GU_SRC_COLOR, GU_DST_COLOR", GU_ADD, GU_SRC_COLOR, GU_DST_COLOR, 0, 0},
	{"GU_ADD, GU_FIX(0x700f7f7f), GU_FIX(0x3f3f3f00)", GU_ADD, GU_FIX, GU_FIX, 0x7f007f7f, 0x3f3f3f00},
	{"GU_ADD, GU_FIX(0x7f7f7f7f), GU_FIX(0x7f7f7f7f)", GU_ADD, GU_FIX, GU_FIX, 0x7f7f7f7f, 0x7f7f7f7f}
};
int curr_state = 0;
float blend_time = 0;

#define BLEND_LENGTH 5.0f

int main(int argc, char* argv[])
{
	unsigned int i,j;
	float start, curr;
	struct timeval tval;

	setupCallbacks();

	// initialize texture

	for (j = 0; j < 256; ++j)
	{
		for (i = 0; i < 256; ++i)
		{
			tex256[i + j * 256] = j & i;
		}
	}

	sceKernelDcacheWritebackAll();

	pspDebugScreenInit();

	// setup GU

	void* fbp0 = guGetStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	void* fbp1 = guGetStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	void* zbp = guGetStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_4444);

	sceGuInit();
	sceGuStart(GU_DIRECT,list);

	sceGuDrawBuffer(GU_PSM_8888,fbp0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,fbp1,BUF_WIDTH);
	sceGuDepthBuffer(zbp,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(0xc350,0x2710);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuFrontFace(GU_CW);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_BLEND);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// run sample

	int offset = 0;

	gettimeofday(&tval,0);
	curr = start = tval.tv_sec + (((float)tval.tv_usec) / 1000000);

	while(running())
	{
		sceGuStart(GU_DIRECT,list);

		// animate palette

		unsigned int* clut = (unsigned int*)(((unsigned int)clut256)|0x40000000);
		for (i = 0; i < 256; ++i)
		{
			unsigned int j = (i + offset)&0xff;
			*(clut++) = (j << 24)|(j << 16)|(j << 8)|(j);
		}

		// clear screen

		sceGuClearColor(0xff00ff);
		sceGuClear(GU_COLOR_BUFFER_BIT);

		// setup blend-mode

		sceGuBlendFunc(states[curr_state].op,states[curr_state].src,states[curr_state].dest,states[curr_state].srcfix,states[curr_state].destfix);

		// setup CLUT texture

		sceGuClutMode(GU_PSM_8888,0,0xff,0); // 32-bit palette
		sceGuClutLoad((256/8),clut256); // upload 32*8 entries (256)
		sceGuTexMode(GU_PSM_T8,0,0,0); // 8-bit image
		sceGuTexImage(0,256,256,256,tex256);
		sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
		sceGuTexFilter(GU_LINEAR,GU_LINEAR);
		sceGuTexScale(1.0f,1.0f);
		sceGuTexOffset(0.0f,0.0f);
		sceGuAmbientColor(0xffffffff);

		// render sprite

		sceGuColor(0xffffffff);
		struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));
		vertices[0].u = 0; vertices[0].v = 0;
		vertices[0].x = 0; vertices[0].y = 0; vertices[0].z = 0;
		vertices[1].u = 256; vertices[1].v = 256;
		vertices[1].x = 480; vertices[1].y = 272; vertices[1].z = 0;
		sceGuDrawArray(GU_SPRITES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D,2,0,vertices);

		// switch blend-modes if time has expired

		gettimeofday(&tval,0);
		curr = tval.tv_sec + (((float)tval.tv_usec) / 1000000);
		if ((curr-start) >= BLEND_LENGTH)
		{
			curr_state = (curr_state + 1) % (sizeof(states)/sizeof(struct BlendState));
			start = curr;
		}

		// wait for next frame

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
		pspDebugScreenSetXY(0,0);
		pspDebugScreenPrintf("%s",states[curr_state].name);

		offset++;
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
