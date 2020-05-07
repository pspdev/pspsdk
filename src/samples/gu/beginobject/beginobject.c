/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * beginobject.c Shows the usage of sceGuBeginObject/sceGuEndObject
 *
 * Copyright (c) 2007 McZonk <www.teamemergencyexit.com>
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

PSP_MODULE_INFO("BeginObject", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

typedef struct VERT {
 	float vertex[3];
} VERT;

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

#define TORUS_SLICES 24 // numc
#define TORUS_ROWS 24 // numt
#define TORUS_RADIUS 1.0f
#define TORUS_THICKNESS 0.5f

#define LIGHT_DISTANCE 3.0f

static VERT           __attribute__((aligned(16))) torus_v0[TORUS_SLICES * TORUS_ROWS];
static unsigned short __attribute__((aligned(16))) torus_in[TORUS_SLICES * TORUS_ROWS * 6];

static unsigned int colors[6] = {
	0xffff0000,
	0xffffff00,
	0xff00ff00,
	0xff00ffff,
	0xff0000ff,
	0xffff00ff
};

static float __attribute__((aligned(16))) bbox[8][3] = {
	{ -1.0f, -1.0f, -1.0f },
	{ -1.0f, -1.0f,  1.0f },
	{ -1.0f,  1.0f, -1.0f },
	{ -1.0f,  1.0f,  1.0f },
	{  1.0f, -1.0f, -1.0f },
	{  1.0f, -1.0f,  1.0f },
	{  1.0f,  1.0f, -1.0f },
	{  1.0f,  1.0f,  1.0f }
};

unsigned int objects = 0;

void gucallback(int id) {
	objects++;
}

int main(int argc, char* argv[]) {
	/* Setup Homebutton Callbacks */
	setupCallbacks();

	/* Generate Torus */
	unsigned int i,j;
	for (j = 0; j < TORUS_SLICES; ++j) {
		for (i = 0; i < TORUS_ROWS; ++i) {
			VERT* v0 = &torus_v0[i + j*TORUS_ROWS];
			
			float s = i + 0.5f;
			float t = j;
			float cs,ct,ss,st;

			cs = cosf(s * (2*GU_PI)/TORUS_SLICES);
			ct = cosf(t * (2*GU_PI)/TORUS_ROWS);
			ss = sinf(s * (2*GU_PI)/TORUS_SLICES);
			st = sinf(t * (2*GU_PI)/TORUS_ROWS);

			v0->vertex[0] = (TORUS_RADIUS + TORUS_THICKNESS * cs) * ct;
			v0->vertex[1] = (TORUS_RADIUS + TORUS_THICKNESS * cs) * st;
			v0->vertex[2] = TORUS_THICKNESS * ss;
		}
	}
	for (j = 0; j < TORUS_SLICES; ++j) {
		for (i = 0; i < TORUS_ROWS; ++i) {
			unsigned short* in = &torus_in[(i+(j*TORUS_ROWS))*6];
			unsigned int i1 = (i+1)%TORUS_ROWS, j1 = (j+1)%TORUS_SLICES;

			*in++ = i + j  * TORUS_ROWS;
			*in++ = i1 + j * TORUS_ROWS;
			*in++ = i + j1 * TORUS_ROWS;

			*in++ = i1 + j  * TORUS_ROWS;
			*in++ = i1 + j1 * TORUS_ROWS;
			*in++ = i  + j1 * TORUS_ROWS;
		}
	}

	sceKernelDcacheWritebackAll();

	// setup GU

	SceCtrlData pad;
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

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
	sceGuEnable(GU_CLIP_PLANES);
	sceGuSetCallback(GU_CALLBACK_SIGNAL, gucallback);
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);
	
	float time = 0.0f;

	void* buffer = 0;

	pspDebugScreenInit();

	unsigned int old = 0;
	unsigned int flags = PSP_CTRL_CIRCLE | PSP_CTRL_CROSS;

	while(running()) {
		objects = 0;
		time += 0.01f;

		sceGuStart(GU_DIRECT,list);

		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(90.0f,16.0/9.0f, 0.1f,100.0f);

		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();
		
		sceGumMatrixMode(GU_MODEL);
		sceGumLoadIdentity();

		unsigned int i;
		for(i = 0; i < 12; i++) {
			sceGumPushMatrix();

			float r = (((float)i / (float)12) * M_PI * 2.0f) + time;
			sceGumRotateY(r);
			ScePspFVector3 t = { 0.0f, 0.0f, 8.0f };
			sceGumTranslate(&t);

			// Draw Bounding Box
			if(flags & PSP_CTRL_CIRCLE || 1) {
				sceGuColor(0xffffffff);
				sceGumDrawArray(GU_POINTS, GU_VERTEX_32BITF | GU_TRANSFORM_3D, 8, 0, bbox);
			}

			// Begin Object
			if(flags & PSP_CTRL_CROSS) {
				sceGuBeginObject(GU_VERTEX_32BITF, 8, 0, bbox);
			}

			sceGuSignal(1, GU_BEHAVIOR_SUSPEND);

			sceGumPushMatrix();
			sceGumRotateX(time * 0.5324f);
			sceGumRotateY(time * 1.2211f);

			sceGuColor(colors[i%6]);
			sceGumDrawArray(GU_TRIANGLES,
				GU_VERTEX_32BITF | GU_INDEX_16BIT | GU_TRANSFORM_3D,
				sizeof(torus_in)/sizeof(unsigned short), torus_in, torus_v0
			);

			sceGumPopMatrix();

			// End Object
			if(flags & PSP_CTRL_CROSS) {
				sceGuEndObject();
			}

			sceGumPopMatrix();
		}

		sceGuFinish();
		sceGuSync(0,0);

		pspDebugScreenSetOffset((int)buffer);
		pspDebugScreenSetXY(0,0);
		if(flags & PSP_CTRL_CROSS) {
			pspDebugScreenPrintf("Use culling. X to toogle. %d objects", objects);
		} else {
			pspDebugScreenPrintf("Don't use culling. X to toogle. %d objects", objects);
		}

		sceDisplayWaitVblankStart();
		buffer = sceGuSwapBuffers();

		sceCtrlReadBufferPositive(&pad, 1);
		if(old != pad.Buttons) {
			flags ^= pad.Buttons;
		}
		old = pad.Buttons;
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
