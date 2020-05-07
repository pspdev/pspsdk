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
#include <pspgum.h>

PSP_MODULE_INFO("Morph Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

static unsigned int __attribute__((aligned(16))) list[262144];

#define max(a,b) ((a)<(b)) ? (b) : (a)
#define min(a,b) ((a)<(b)) ? (a) : (b)

struct Vertex
{
	unsigned int color;
	ScePspFVector3 normal;
	ScePspFVector3 pos;
};

struct MorphVertex
{
	struct Vertex v0;
	struct Vertex v1;
};

int SetupCallbacks();

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

#define ROWS (64)
#define COLS (64)

unsigned short __attribute__((aligned(16))) indices[(ROWS+1)*(COLS+1)*6];
struct MorphVertex __attribute__((aligned(16))) vertices[ROWS*COLS];

int main(int argc, char* argv[])
{
	unsigned int i,j;
	SetupCallbacks();

	// generate sphere & cube that can blend between each other (a bit messy right now)

	for (i = 0; i < ROWS; ++i)
	{
		float di = (((float)i)/ROWS);
		float s = di * GU_PI * 2;
		ScePspFVector3 v = { cosf(s), cosf(s), sinf(s) };

		for(j = 0; j < COLS; ++j)
		{
			unsigned short* curr = &indices[(j+(i*COLS))*6];
			unsigned int i1 = (i+1)%ROWS, j1 = (j+1)%COLS;

			float t = (((float)j)/COLS) * GU_PI * 2;

			ScePspFVector3 v2 = { v.x * cosf(t), v.y * sinf(t), v.z };
			ScePspFVector3 v3;

			// cheap mans sphere -> cube algo :D
			v3.x = v2.x > 0 ? min(v2.x * 10.0f,1.0f) : max(v2.x * 10.0f,-1.0f);
			v3.y = v2.y > 0 ? min(v2.y * 10.0f,1.0f) : max(v2.y * 10.0f,-1.0f);
			v3.z = v2.z > 0 ? min(v2.z * 10.0f,1.0f) : max(v2.z * 10.0f,-1.0f);

			vertices[j+i*COLS].v0.color = (0xff<<24)|((int)(fabsf(v2.x) * 255.0f) << 16)|((int)(fabsf(v2.y) * 255.0f) << 8)|((int)(fabsf(v2.z) * 255.0f));
			vertices[j+i*COLS].v0.normal = v2;
			vertices[j+i*COLS].v0.pos = v2;

			vertices[j+i*COLS].v1.color = vertices[j+i*COLS].v0.color;
			vertices[j+i*COLS].v1.normal = v3;
			gumNormalize(&vertices[j+i*COLS].v1.normal);
			vertices[j+i*COLS].v1.pos = v3;

			// indices
			*curr++ = j + i * COLS;
			*curr++ = j1 + i * COLS;
			*curr++ = j + i1 * COLS;

			*curr++ = j1 + i * COLS;
			*curr++ = j1 + i1 * COLS;
			*curr++ = j + i1 * COLS;
		}
	}

	sceKernelDcacheWritebackAll();

	// setup GU

	sceGuInit();

	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,(void*)0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,(void*)0x88000,BUF_WIDTH);
	sceGuDepthBuffer((void*)0x110000,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(0xc350,0x2710);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_LIGHTING);
	sceGuEnable(GU_LIGHT0);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	sceGumPerspective(75.0f,16.0f/9.0f,0.5f,1000.0f);

	sceGumMatrixMode(GU_VIEW);
	{
		ScePspFVector3 pos = {0.0f,0.0f,-2.5f};

		sceGumLoadIdentity();
		sceGumTranslate(&pos);
	}

	// run sample

	int val = 0;

	for(;;)
	{
		ScePspFVector3 lpos = { 1, 0, 1 };
		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0xff554433);
		sceGuClearDepth(0);
		sceGuLight(0,GU_DIRECTIONAL,GU_DIFFUSE_AND_SPECULAR,&lpos);
		sceGuLightColor(0,GU_DIFFUSE_AND_SPECULAR,0xffffffff);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
		sceGuSpecular(12.0f);
                                                                        

		// rotate morphing mesh

		sceGumMatrixMode(GU_MODEL);
		{
			ScePspFVector3 rot = {val * 0.79f * (GU_PI/180.0f), val * 0.98f * (GU_PI/180.0f), val * 1.32f * (GU_PI/180.0f)};

			sceGumLoadIdentity();
			sceGumRotateXYZ(&rot);
		}

		sceGuAmbientColor(0xffffffff);

		// draw cube

		sceGuMorphWeight(0,0.5f * sinf(val * (GU_PI/180.0f)) + 0.5f);
		sceGuMorphWeight(1,-0.5f * sinf(val * (GU_PI/180.0f)) + 0.5f);
		sceGumDrawArray(GU_TRIANGLES,GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_VERTICES(2)|GU_INDEX_16BIT|GU_TRANSFORM_3D,sizeof(indices)/sizeof(unsigned short),indices,vertices);

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

		val++;
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

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}
