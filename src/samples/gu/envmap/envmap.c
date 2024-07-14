/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * envmap.c - Sample to demonstrate environment mapping functionality
 *
 * Copyright (c) 2005 Jesper Svennevid
 * Copyright (c) 2005 Renaldas Zioma <rej@scene.lt>
 *
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pspctrl.h>

#include <pspgu.h>
#include <pspgum.h>

#include "../common/callbacks.h"
#include "../common/geometry.h"

PSP_MODULE_INFO("EnvMap Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];
extern unsigned char env0_start[];

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

#define TORUS_SLICES 48 // numc
#define TORUS_ROWS 48 // numt
#define TORUS_RADIUS 1.0f
#define TORUS_THICKNESS 0.5f

#define LIGHT_DISTANCE 3.0f

NPVertex __attribute__((aligned(16))) torus_vertices[TORUS_SLICES*TORUS_ROWS];
unsigned short __attribute__((aligned(16))) torus_indices[TORUS_SLICES*TORUS_ROWS*6];

int main(int argc, char* argv[])
{
	setupCallbacks();

	// generate geometry

	generateTorusNP(TORUS_ROWS,TORUS_SLICES,TORUS_RADIUS,TORUS_THICKNESS,torus_vertices,torus_indices);

	// flush cache so that no stray data remains

	sceKernelDcacheWritebackAll();

	//setup Pad

	SceCtrlData pad;
	u32 oldButtons = 0;
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(0);

	// setup GU

	void* fbp0 = guGetStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	void* fbp1 = guGetStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	void* zbp = guGetStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_4444);

	pspDebugScreenInit();
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
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_LIGHTING);
	sceGuEnable(GU_LIGHT0);
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// run sample

	int valTorus = 0;
	int valEnvMap = 0;
	int rotateTorus = 1;
	int rotateEnvMap = 1;

	while(running())
	{
		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0x554433);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// setup a light

		ScePspFVector3 dir = { 0, 0, 1 };
		sceGuLight(0,GU_DIRECTIONAL,GU_DIFFUSE,&dir);
		sceGuLightColor(0,GU_DIFFUSE,0x00ff4040 );
		sceGuLightAtt(0,1.0f,0.0f,0.0f);
		sceGuAmbient(0x00202020);

		// setup proj/view matrices

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f,16.0/9.0f,1.0f,1000.0f);

		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		// setup envmap texture

		sceGuTexMode(GU_PSM_4444,0,0,0);
		sceGuTexImage(0,64,64,64,env0_start);
		sceGuTexFunc(GU_TFX_MODULATE,GU_TCC_RGB);
		sceGuTexFilter(GU_LINEAR,GU_LINEAR);
		sceGuAmbientColor(0xffffffff);
	
		// setup envmap matrix (2x3)
		// 2d rotation/translation matrix
		// [ cosa  -sina ]
		// [ sina   cosa ]
		// [  tx     ty  ]

		// envmap matrix is transposed
		// since it is passed to GU as columns
		float angle = -2.0f * valEnvMap * (GU_PI/180.0f);
		float cs = cosf(angle);
		float sn = sinf(angle);
		ScePspFVector3 envmapMatrixColumns[2] = {
			{ cs,  sn, 0.0f },
			{ -sn, cs, 0.0f }
		};
		sceGuLight( 2, GU_DIRECTIONAL, GU_DIFFUSE, &envmapMatrixColumns[0] );
		sceGuLight( 3, GU_DIRECTIONAL, GU_DIFFUSE, &envmapMatrixColumns[1] );

		// setup envmap texture coord generation
		sceGuTexMapMode(
			GU_ENVIRONMENT_MAP,	// envmap mode on
			2,	// use 2nd light position as an envmap matrix 1st column
			3	// use 3rd light position as an envmap matrix 2nd column
			);

		// draw torus

		sceGumMatrixMode(GU_MODEL);
		{
			ScePspFVector3 pos = {0,0,-2.5f};
			ScePspFVector3 rot = {valTorus * 0.79f * (GU_PI/180.0f), valTorus * 0.98f * (GU_PI/180.0f), valTorus * 1.32f * (GU_PI/180.0f)};
			sceGumLoadIdentity();
			sceGumTranslate(&pos);
			sceGumRotateXYZ(&rot);
		}

		sceGuColor(0xffffff);
		sceGumDrawArray(GU_TRIANGLES,GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,sizeof(torus_indices)/sizeof(unsigned short),torus_indices,torus_vertices);

		pspDebugScreenSetXY(0,0);
		pspDebugScreenPrintf( "Press X to toggle environment map rotation" );
		pspDebugScreenSetXY(0,1);
		pspDebugScreenPrintf( "Press O to toggle torus rotation" );

		sceCtrlReadBufferPositive(&pad, 1);
		if(oldButtons != pad.Buttons)
		{
			if(pad.Buttons & PSP_CTRL_CROSS)
				rotateTorus ^= 0x01;
			if(pad.Buttons & PSP_CTRL_CIRCLE)
				rotateEnvMap ^= 0x01;
		}
		oldButtons = pad.Buttons;

		sceGuFinish();
		sceGuSync(0,0);

//		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

		if(rotateTorus) valTorus++;
		if(rotateEnvMap) valEnvMap++;
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
