/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * celshading.c Simple cel shading example
 * written as xmas present for psp community
 *
 * Copyright (c) 2005 McZonk <www.teamemergencyexit.com>
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

PSP_MODULE_INFO("Celshading", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

extern unsigned char lightmap_start[];

typedef struct Vx_v32f_n32f {
	float normal[3];
 	float vertex[3];
} Vx_v32f_n32f;

typedef struct Vx_v32f {
	float vertex[3];
} Vx_v32f;

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

Vx_v32f_n32f   __attribute__((aligned(16))) torus_v0[TORUS_SLICES * TORUS_ROWS];
Vx_v32f        __attribute__((aligned(16))) torus_v1[TORUS_SLICES * TORUS_ROWS];
unsigned short __attribute__((aligned(16))) torus_in[TORUS_SLICES * TORUS_ROWS * 6];

int main(int argc, char* argv[]) {
	/* Setup Homebutton Callbacks */
	setupCallbacks();

	/* Generate Torus */
	unsigned int i,j;
	for (j = 0; j < TORUS_SLICES; ++j) {
		for (i = 0; i < TORUS_ROWS; ++i) {
			struct Vx_v32f_n32f* v0 = &torus_v0[i + j*TORUS_ROWS];
			struct Vx_v32f*      v1 = &torus_v1[i + j*TORUS_ROWS];
			
			float s = i + 0.5f;
			float t = j;
			float cs,ct,ss,st;

			cs = cosf(s * (2*GU_PI)/TORUS_SLICES);
			ct = cosf(t * (2*GU_PI)/TORUS_ROWS);
			ss = sinf(s * (2*GU_PI)/TORUS_SLICES);
			st = sinf(t * (2*GU_PI)/TORUS_ROWS);

			v0->normal[0] = cs * ct;
			v0->normal[1] = cs * st;
			v0->normal[2] = ss;

			v0->vertex[0] = (TORUS_RADIUS + TORUS_THICKNESS * cs) * ct;
			v0->vertex[1] = (TORUS_RADIUS + TORUS_THICKNESS * cs) * st;
			v0->vertex[2] = TORUS_THICKNESS * ss;
			
			v1->vertex[0] = v0->vertex[0] + v0->normal[0] * 0.1f;
			v1->vertex[1] = v0->vertex[1] + v0->normal[1] * 0.1f;
			v1->vertex[2] = v0->vertex[2] + v0->normal[2] * 0.1f;
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

    SceCtrlData pad;
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

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
	sceGuEnable(GU_CLIP_PLANES);
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	unsigned int old = 0;
	unsigned int flags = PSP_CTRL_CIRCLE | PSP_CTRL_CROSS | PSP_CTRL_SQUARE;
	
	float rx = 0.0f, ry = 0.0f;
	
	while(running())
	{
		sceGuStart(GU_DIRECT,list);

		sceGuClearColor(0xFFFFFF);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f,16.0/9.0f,1.0f,1000.0f);

		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();
		
		sceGumMatrixMode(GU_MODEL);
		sceGumLoadIdentity();
		ScePspFVector3 pos = { 0.0f, 0.0f, -3.0f };
		ScePspFVector3 rot = { ry * (GU_PI/180.0f), rx * (GU_PI/180.0f), 0.0f };
		sceGumTranslate(&pos);
		sceGumRotateXYZ(&rot);

		sceGuTexMode(GU_PSM_8888,0,0,0);
		sceGuTexImage(0,64,64,64, lightmap_start);
		sceGuTexFunc(GU_TFX_MODULATE,GU_TCC_RGB);
		sceGuTexFilter(GU_LINEAR,GU_LINEAR);
		sceGuColor(0xff9966);
	
		ScePspFVector3 envmapMatrixColumns[2] = {
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f }
		};
		sceGuLight( 0, GU_DIRECTIONAL, GU_DIFFUSE, &envmapMatrixColumns[0] );
		sceGuLight( 1, GU_DIRECTIONAL, GU_DIFFUSE, &envmapMatrixColumns[1] );

		sceGuTexMapMode(GU_ENVIRONMENT_MAP,	0, 1);
		
		/*
			First pass: draw the torus
		*/
		if(flags & PSP_CTRL_CROSS) {
			sceGuEnable(GU_TEXTURE_2D);
		}
		sceGumDrawArray(GU_TRIANGLES,
			GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,
			sizeof(torus_in)/sizeof(unsigned short), torus_in, torus_v0
		);
		if(flags & PSP_CTRL_CROSS) {
			sceGuDisable(GU_TEXTURE_2D);
		}
		

		/*
			Seconds pass: draw the outline
		*/
		if(flags & PSP_CTRL_CIRCLE) {
			sceGuFrontFace(GU_CCW);
			sceGuColor(0x0);
			sceGumDrawArray(GU_TRIANGLES,
				GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,
				sizeof(torus_in)/sizeof(unsigned short), torus_in, torus_v1
			);
			sceGuFrontFace(GU_CW);
		}
		
		sceGuFinish();
		sceGuSync(0,0);

		sceCtrlReadBufferPositive(&pad, 1);
		
		float tx = (pad.Lx - 128) / 127.0f;
		float ty = (pad.Ly - 128) / 127.0f;
		if(fabs(tx) <= 0.2f) {
			tx = 0.0f;
		} else {
			if(tx > 0.0f) {
				tx -= 0.2f;
			} else {
				tx += 0.2f;
			}
		}
		if(fabs(ty) <= 0.2f) {
			ty = 0.0f;
		} else {
			if(ty > 0.0f) {
				ty -= 0.2f;
			} else {
				ty += 0.2f;
			}
		}

		rx += tx;
		ry += ty;
		
		if(old != pad.Buttons) {
			flags ^= pad.Buttons;
		}
		old = pad.Buttons;

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
