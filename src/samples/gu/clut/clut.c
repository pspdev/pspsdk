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

PSP_MODULE_INFO("Clut Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
	float u,v;
	float x,y,z;
};

int SetupCallbacks();

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

#define NUM_SLICES 128
#define NUM_ROWS 128
#define RING_SIZE 2.0f
#define RING_RADIUS 1.0f
#define SPRITE_SIZE 0.025f

unsigned int colors[8] = 
{
	0xffff0000,
	0xffff00ff,
	0xff0000ff,
	0xff00ffff,
	0xff00ff00,
	0xffffff00,
	0xffffffff,
	0xff00ffff
};

unsigned int __attribute__((aligned(16))) clut256[256];
unsigned char __attribute__((aligned(16))) tex256[256*256];

int main(int argc, char* argv[])
{
	unsigned int i,j;

	SetupCallbacks();

	// initialize texture

	for (j = 0; j < 256; ++j)
	{
		for (i = 0; i < 256; ++i)
		{
			tex256[i + j * 256] = j ^ i;
		}
	}

	sceKernelDcacheWritebackAll();

	// setup GU

	sceGuInit();
	sceGuStart(GU_DIRECT,list);

	sceGuDrawBuffer(GU_PSM_8888,(void*)0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,(void*)FRAME_SIZE,BUF_WIDTH);
	sceGuDepthBuffer((void*)(FRAME_SIZE*2),BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(0xc350,0x2710);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuFrontFace(GU_CW);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// run sample

	int offset = 0;

	for(;;)
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

		// setup CLUT texture

		sceGuClutMode(GU_PSM_8888,0,0xff,0); // 32-bit palette
		sceGuClutLoad((256/8),clut256); // upload 32*8 entries (256)
		sceGuTexMode(GU_PSM_T8,0,0,0); // 8-bit image
		sceGuTexImage(0,256,256,256,tex256);
		sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGB);
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
		sceGuDrawArray(GU_SPRITES,GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_2D,2,0,vertices);

		// wait for next frame

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

		offset++;
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}

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

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x18, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}
