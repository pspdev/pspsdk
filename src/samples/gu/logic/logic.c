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

#include <pspgu.h>

#include "../common/callbacks.h"

PSP_MODULE_INFO("Logic Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
 	float x,y,z;
};

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

const char* names[16] =
{
	"GU_CLEAR",
	"GU_AND",
	"GU_AND_REVERSE",
	"GU_COPY",
	"GU_AND_INVERTED",
	"GU_NOOP",
	"GU_XOR",
	"GU_OR",
	"GU_NOR",
	"GU_EQUIV",
	"GU_INVERTED",
	"GU_OR_REVERSE",
	"GU_COPY_INVERTED",
	"GU_OR_INVERTED",
	"GU_NAND",
	"GU_SET"
};

#define TIME_SLICE 5

int curr_state = 0;
struct timeval base_time;

int main(int argc, char* argv[])
{
	pspDebugScreenInit();

	setupCallbacks();

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
	sceGuDepthRange(65535,0);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	int val = 0;

	gettimeofday(&base_time,0);

	while(running())
	{
		struct Vertex* vertices;
		struct timeval tv;

		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// draw triangle 1 (normal)

		sceGuColor(0xffffffff);

		vertices = (struct Vertex*)sceGuGetMemory(3*sizeof(struct Vertex));
		vertices[0].x = (SCR_WIDTH/2) + cosf(val * (GU_PI/180)) * (SCR_HEIGHT/2);
		vertices[0].y = (SCR_HEIGHT/2) + sinf(val * (GU_PI/180)) * (SCR_HEIGHT/2);
		vertices[0].z = 0;
		vertices[1].x = (SCR_WIDTH/2) + cosf((val+120) * (GU_PI/180)) * (SCR_HEIGHT/2);
		vertices[1].y = (SCR_HEIGHT/2) + sinf((val+120) * (GU_PI/180)) * (SCR_HEIGHT/2);
		vertices[1].z = 0;
		vertices[2].x = (SCR_WIDTH/2) + cosf((val+240) * (GU_PI/180)) * (SCR_HEIGHT/2);
		vertices[2].y = (SCR_HEIGHT/2) + sinf((val+240) * (GU_PI/180)) * (SCR_HEIGHT/2);
		vertices[2].z = 0;
		sceGuDrawArray(GU_TRIANGLES,GU_VERTEX_32BITF|GU_TRANSFORM_2D,3,0,vertices);

		// draw triangle 2 (affected by logic op)

		sceGuEnable(GU_COLOR_LOGIC_OP);
		sceGuLogicalOp(curr_state);

		sceGuColor(0xffff00ff);

		vertices = (struct Vertex*)sceGuGetMemory(3*sizeof(struct Vertex));
		vertices[0].x = (SCR_WIDTH/2) + cosf((val*1.1f) * (GU_PI/180)) * (SCR_HEIGHT/2);
		vertices[0].y = (SCR_HEIGHT/2) + sinf((val*1.1f) * (GU_PI/180)) * (SCR_HEIGHT/2);
		vertices[0].z = 0;
		vertices[1].x = (SCR_WIDTH/2) + cosf((val*1.1f+120) * (GU_PI/180)) * (SCR_HEIGHT/2);
		vertices[1].y = (SCR_HEIGHT/2) + sinf((val*1.1f+120) * (GU_PI/180)) * (SCR_HEIGHT/2);
		vertices[1].z = 0;
		vertices[2].x = (SCR_WIDTH/2) + cosf((val*1.1f+240) * (GU_PI/180)) * (SCR_HEIGHT/2);
		vertices[2].y = (SCR_HEIGHT/2) + sinf((val*1.1f+240) * (GU_PI/180)) * (SCR_HEIGHT/2);
		vertices[2].z = 0;
		sceGuDrawArray(GU_TRIANGLES,GU_VERTEX_32BITF|GU_TRANSFORM_2D,3,0,vertices);

		sceGuDisable(GU_COLOR_LOGIC_OP);

		sceGuFinish();
		sceGuSync(0,0);

		gettimeofday(&tv,0);
		if ((tv.tv_sec-base_time.tv_sec) > TIME_SLICE)
		{
			curr_state = (curr_state + 1) & 15;
			base_time = tv;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
		pspDebugScreenSetXY(0,0);
		pspDebugScreenPrintf("%s",names[curr_state]);

		val++;
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
