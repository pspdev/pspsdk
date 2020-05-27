/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 * Copyright (c) 2005 McZonk <mczonk@gmx.net>
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

PSP_MODULE_INFO("Reflection Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

static unsigned int __attribute__((aligned(16))) list[262144];
extern unsigned char logo_start[];

struct Vertex
{
	float u, v;
	unsigned int color;
	float x,y,z;
};

struct Vertex __attribute__((aligned(16))) obj[36] = {
	{0, 0, 0xff6666ff,-1,-1, 1},
	{1, 0, 0xff6666ff, 1,-1, 1},
	{1, 1, 0xff6666ff, 1, 1, 1},
	{0, 0, 0xff6666ff,-1,-1, 1},
	{1, 1, 0xff6666ff, 1, 1, 1},
	{0, 1, 0xff6666ff,-1, 1, 1},
	
	{1, 1, 0xff66ff66, 1, 1, 1},
	{0, 1, 0xff66ff66, 1,-1, 1},
	{0, 0, 0xff66ff66, 1,-1,-1},
	{1, 1, 0xff66ff66, 1, 1, 1},
	{0, 0, 0xff66ff66, 1,-1,-1},
	{1, 0, 0xff66ff66, 1, 1,-1},
	
	{0, 1, 0xffff6666,-1, 1, 1},
	{0, 0, 0xffff6666, 1, 1, 1},
	{1, 0, 0xffff6666, 1, 1,-1},
	{0, 1, 0xffff6666,-1, 1, 1},
	{1, 0, 0xffff6666, 1, 1,-1},
	{1, 1, 0xffff6666,-1, 1,-1},
	
	
	{1, 1, 0xff6666ff, 1,-1,-1},
	{0, 1, 0xff6666ff,-1,-1,-1},
	{0, 0, 0xff6666ff,-1, 1,-1},
	{1, 1, 0xff6666ff, 1,-1,-1},
	{0, 0, 0xff6666ff,-1, 1,-1},
	{1, 0, 0xff6666ff, 1, 1,-1},
	
	{1, 0, 0xff66ff66,-1,-1,-1},
	{1, 1, 0xff66ff66,-1,-1, 1},
	{0, 1, 0xff66ff66,-1, 1, 1},
	{1, 0, 0xff66ff66,-1,-1,-1},
	{0, 1, 0xff66ff66,-1, 1, 1},
	{0, 0, 0xff66ff66,-1, 1,-1},
	
	{0, 1, 0xffff6666,-1,-1,-1},
	{0, 0, 0xffff6666, 1,-1,-1},
	{1, 0, 0xffff6666, 1,-1, 1},
	{0, 1, 0xffff6666,-1,-1,-1},
	{1, 0, 0xffff6666, 1,-1, 1},
	{1, 1, 0xffff6666,-1,-1, 1},
};

struct Vertex __attribute__((aligned(16))) mirror[6] = {
	{0, 0, 0xaa000000, -2.0f,  0, -2.0f},
	{2, 2, 0xaa000000,  2.0f,  0,  2.0f},
	{2, 0, 0xaa000000,  2.0f,  0, -2.0f},
	
	{0, 0, 0xaa000000, -2.0f,  0, -2.0f},
	{0, 2, 0xaa000000, -2.0f,  0,  2.0f},
	{2, 2, 0xaa000000,  2.0f,  0,  2.0f}
};

struct Vertex __attribute__((aligned(16))) border[6] = {
	{0, 0, 0xff0055aa, -2.125f,  -0.01, -2.125f},
	{2, 2, 0xff0055aa,  2.125f,  -0.01,  2.125f},
	{2, 0, 0xff0055aa,  2.125f,  -0.01, -2.125f},
	
	{0, 0, 0xff0055aa, -2.125f,  -0.01, -2.125f},
	{0, 2, 0xff0055aa, -2.125f,  -0.01,  2.125f},
	{2, 2, 0xff0055aa,  2.125f,  -0.01,  2.125f}
};

int SetupCallbacks();

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

int main(int argc, char* argv[])
{
	SetupCallbacks();

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
	sceGuFrontFace(GU_CCW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// run sample

	int val = 0;

	for(;;)
	{
		float move = sinf(((float)val / 180.0f) * GU_PI);
		if(move < 0) {
			move *= -1;
		}
		move += 1;
		
		float rot = ((float)val / 180.0f) * GU_PI;
	
		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0xff554433);
		sceGuClearDepth(0);
		sceGuClearStencil(0);
		sceGuClear(GU_COLOR_BUFFER_BIT | GU_STENCIL_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

		// setup matrices for cube

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(60.0f,16.0f/9.0f,0.5f,1000.0f);

		sceGumMatrixMode(GU_VIEW);
		{
			ScePspFVector3 pos = {0,-0.5f,-5.5f};
			ScePspFVector3 rot = {(30.0f * GU_PI) / 180.0f, (val * 0.2f * GU_PI) / 180.0f, 0.0f};

			sceGumLoadIdentity();
			sceGumTranslate(&pos);
			sceGumRotateXYZ(&rot);
		}

		sceGumMatrixMode(GU_MODEL);
		sceGumLoadIdentity();
		
		// draw mirrored view

		sceGumPushMatrix();
		{
			ScePspFVector3 scale = {1,-1,1};
			sceGumScale(&scale);
		}

		sceGuFrontFace(GU_CCW);
		sceGuEnable(GU_STENCIL_TEST); // Stencil test
		sceGuDepthMask(GU_TRUE);
		sceGuStencilFunc(GU_ALWAYS, 1, 1); // always set 1 bit in 1 bit mask
		sceGuStencilOp(GU_KEEP, GU_KEEP, GU_REPLACE); // keep value on failed test (fail and zfail) and replace on pass
		sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, 0, mirror);
		sceGuDepthMask(GU_FALSE);
		
		sceGuTexMode(GU_PSM_4444,0,0,0);
		sceGuTexImage(0,64,64,64,logo_start);
		sceGuTexFunc(GU_TFX_ADD,GU_TCC_RGB);
		sceGuTexFilter(GU_LINEAR,GU_LINEAR);
		sceGuTexScale(1.0f,1.0f);
		sceGuTexOffset(0.0f,0.0f);
		sceGuEnable(GU_TEXTURE_2D);
		sceGuFrontFace(GU_CW);
		sceGuStencilFunc(GU_EQUAL, 1, 1); // allow drawing where stencil is 1
		sceGuStencilOp(GU_KEEP, GU_KEEP, GU_KEEP); // keep the stencil buffer unchanged

		{
			ScePspFVector3 pos = {0,move,0};
			ScePspFVector3 rvec = {0,rot * -0.83f, 0};

			sceGumTranslate(&pos);
			sceGumRotateXYZ(&rvec);
		}

		sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 36, 0, obj);
		sceGuDisable(GU_TEXTURE_2D);
		sceGuDisable(GU_STENCIL_TEST);
		
		sceGumPopMatrix();

		// draw normal view
		sceGuEnable(GU_TEXTURE_2D);
		sceGuTexMode(GU_PSM_4444,0,0,0);
		sceGuTexImage(0,64,64,64,logo_start);
		sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
		sceGuTexFilter(GU_LINEAR,GU_LINEAR);
		sceGuTexScale(1.0f,1.0f);
		sceGuTexOffset(0.0f,0.0f);
		sceGuFrontFace(GU_CCW);
		sceGuEnable(GU_BLEND);
		sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
		sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, 0, mirror);
		sceGuDisable(GU_BLEND);
		sceGuDisable(GU_TEXTURE_2D);
		
		sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, 0, border);
		
		sceGuEnable(GU_TEXTURE_2D);
		sceGuTexMode(GU_PSM_4444,0,0,0);
		sceGuTexImage(0,64,64,64,logo_start);
		sceGuTexFunc(GU_TFX_ADD,GU_TCC_RGB);
		sceGuTexFilter(GU_LINEAR,GU_LINEAR);
		sceGuTexScale(1.0f,1.0f);
		sceGuTexOffset(0.0f,0.0f);

		{
			ScePspFVector3 pos = {0,move,0};
			ScePspFVector3 rvec = {0,rot * -0.83f, 0};

			sceGumTranslate(&pos);
			sceGumRotateXYZ(&rvec);
		}

		sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 36, 0, obj);
		sceGuDisable(GU_TEXTURE_2D);

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
