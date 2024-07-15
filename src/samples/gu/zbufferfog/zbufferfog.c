/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * This implements unswizzled depth-fog using the hardware unswizzling
 * figured out by Jeremy Fitzhardinge.
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
#include <pspctrl.h>

#include "../common/callbacks.h"
#include "../common/geometry.h"

PSP_MODULE_INFO("Depth Buffer Fog Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

#define BUFFER_WIDTH 512 // actual screen width
#define SCREEN_WIDTH 480 // visible screen width
#define SCREEN_HEIGHT 272 // visible screen height
#define SCREEN_PSM GU_PSM_8888 // screen pixel format

#define TORUS_SLICES 48 // numc
#define TORUS_ROWS 48 // numt
#define TORUS_RADIUS 1.0f
#define TORUS_THICKNESS 0.5f

TCPVertex __attribute__((aligned(16))) torus_vertices[TORUS_SLICES*TORUS_ROWS];
unsigned short __attribute__((aligned(16))) torus_indices[TORUS_SLICES*TORUS_ROWS*6];

#define ZBUFFER_LINEAR(x) (0x600000 + x)
#define ZBUFFER_SLICE 64
#define VRAM_OFFSET(x) (0x4000000 + x)
#define ZFAR_LIMIT 64
#define ZNEAR_LIMIT 256
#define FOG_COLOR 0x554433

unsigned int __attribute__((aligned(16))) fogPalette[256];
unsigned int __attribute__((aligned(16))) rawPalette[256];

void RenderFog(void* zbuffer)
{
	int i;

	// split in two passes since the depth buffer won't fit in a 512x512 texture when using 8-bit textures

	for (i = 0; i < 2; ++i)
	{
		int j;

		sceGuTexMode(GU_PSM_T8,0,0,0);
		sceGuTexImage(0,512,512,1024,(void*)VRAM_OFFSET(ZBUFFER_LINEAR(((unsigned int)zbuffer) + i * (256*2))));
		sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
		sceGuTexFilter(GU_NEAREST,GU_NEAREST);
		sceGuColor(0);

		for (j = 0; j < (256/ZBUFFER_SLICE); ++j)
		{
			TPVertex* vertices = (TPVertex*)sceGuGetMemory(sizeof(TPVertex)*2);

			// shift texture 1 pixel to avoid the 8 LSB, since they change very rapidly

			vertices[0].texture.x = 1 + j*(ZBUFFER_SLICE * 2);
			vertices[0].texture.y = 0;
			vertices[0].position.x = j*ZBUFFER_SLICE + i * 256;
			vertices[0].position.y = 0;
			vertices[0].position.z = 0;

			vertices[1].texture.x = 1 + (j+1)*(ZBUFFER_SLICE * 2);
			vertices[1].texture.y = SCREEN_HEIGHT;
			vertices[1].position.x = (j+1)*ZBUFFER_SLICE + i * 256;
			vertices[1].position.y = SCREEN_HEIGHT;
			vertices[1].position.z = 0;

			sceGuDrawArray(GU_SPRITES,TP_VERTEX_FORMAT|GU_TRANSFORM_2D,2,0,vertices);
		}
	}
}

int main(int argc, char* argv[])
{
	setupCallbacks();

	// generate geometry & palettes

	int i;

	generateTorusTCP(TORUS_SLICES,TORUS_ROWS,TORUS_RADIUS,TORUS_THICKNESS,torus_vertices,torus_indices);

	for (i = 0; i < 256; ++i)
	{
		unsigned int far = (i - ZFAR_LIMIT) < 0 ? 0 : (i - ZFAR_LIMIT);
		unsigned int near = (far * 256) / (ZNEAR_LIMIT-ZFAR_LIMIT);
		unsigned int k = near > 255 ? 255 : near;
		fogPalette[i] = (k << 24)|FOG_COLOR;

		rawPalette[i] = (i << 24)|(i << 16)|(i << 8)|i;
	}

	sceKernelDcacheWritebackAll();

	// setup GU

	sceGuInit();

	void* fbp0 = guGetStaticVramBuffer(BUFFER_WIDTH,SCREEN_HEIGHT,SCREEN_PSM); // drawbuffer 1, 512x272 (480x272 visible)
	void* fbp1 = guGetStaticVramBuffer(BUFFER_WIDTH,SCREEN_HEIGHT,SCREEN_PSM); // drawbuffer 2
	void* zbp = guGetStaticVramBuffer(BUFFER_WIDTH,SCREEN_HEIGHT,GU_PSM_4444); // zbuffer, always 16bit

	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(SCREEN_PSM,fbp0,BUFFER_WIDTH);
	sceGuDispBuffer(SCREEN_WIDTH,SCREEN_HEIGHT,fbp1,BUFFER_WIDTH);
	sceGuDepthBuffer(zbp,BUFFER_WIDTH);
	sceGuOffset(2048 - (SCREEN_WIDTH/2),2048 - (SCREEN_HEIGHT/2));
	sceGuViewport(2048,2048,SCREEN_WIDTH,SCREEN_HEIGHT);
	sceGuDepthRange(65535,0);
	sceGuDisable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	pspDebugScreenInit();

	// run sample

	int val = 0;
	int split = 0;
	SceCtrlData oldPad;
	oldPad.Buttons = 0;

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(0);

	while(running())
	{
		sceGuStart(GU_DIRECT,list);

		// switch mode if requested

		SceCtrlData pad;
		if (sceCtrlPeekBufferPositive(&pad,1))
		{
			if (pad.Buttons != oldPad.Buttons)
			{
				if (pad.Buttons & PSP_CTRL_CROSS)
					split ^= 1;
			}
			oldPad = pad;
		}

		// clear screen

		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// setup matrices for cube

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f,16.0f/9.0f,1.0f,100.0f);

		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		sceGumMatrixMode(GU_MODEL);
		sceGumLoadIdentity();
		{
			ScePspFVector3 pos = { 0, 0, -5.0f + sinf(val * (GU_PI/180.0f)) * 2.5f };
			ScePspFVector3 rot = { val * 0.79f * (GU_PI/180.0f), val * 0.98f * (GU_PI/180.0f), val * 1.32f * (GU_PI/180.0f) };
			sceGumTranslate(&pos);
			sceGumRotateXYZ(&rot);
		}

		// draw cube

		sceGumDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,sizeof(torus_indices)/sizeof(unsigned short),torus_indices,torus_vertices);

		// fog using the zbuffer

		sceGuEnable(GU_TEXTURE_2D);
		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(0xffff);
		sceGuColor(0);

		sceGuClutMode(GU_PSM_8888,0,255,0);
		sceGuClutLoad(256/8,fogPalette);

		sceGuEnable(GU_BLEND);
		sceGuBlendFunc(GU_ADD,GU_ONE_MINUS_SRC_ALPHA,GU_SRC_ALPHA,0,0);

		RenderFog(zbp);

		sceGuDisable(GU_BLEND);

		// render raw fog if enabled

		if (split)
		{
			sceGuEnable(GU_SCISSOR_TEST);
			sceGuScissor(SCREEN_WIDTH/2,0,SCREEN_WIDTH,SCREEN_HEIGHT);

			sceGuClutMode(GU_PSM_8888,0,255,0);
			sceGuClutLoad(256/8,rawPalette);

			RenderFog(zbp);

			sceGuDisable(GU_SCISSOR_TEST);
		}

		sceGuDisable(GU_TEXTURE_2D);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);	

		sceGuFinish();
		sceGuSync(0,0);

		pspDebugScreenSetOffset((int)fbp0);
		pspDebugScreenSetXY(0,0);
		pspDebugScreenPrintf("X = normal/split screen");

		sceDisplayWaitVblankStart();
		fbp0 = sceGuSwapBuffers();


		val++;
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
