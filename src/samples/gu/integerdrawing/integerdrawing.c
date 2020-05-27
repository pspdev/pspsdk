/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * beginobject.c Shows the usage of sceGuBeginObject/sceGuEndObject
 *
 * Copyright (c) 2007 McZonk <emergencyexit.untergrund.net>
 *
 */

/*
	This sample shows the usage of integers for 3d drawing.
	3d mode is always used when GU_TRANSFORM_2D is not specified as flag.
	Instead of spending an 32bit float for weight, normal, texcoord or postion
	a smaller integer value can be used. The behavior is equal for each type.
	The range of the int is normalized to the interval [-1, 1].
	The maximum value is +( ( 2 ^ (number of bits) ) / 2 ) - 1.
	The minimum value is -( ( 2 ^ (number of bits) ) / 2 ) - 1.
	For 8 bit it is: -127 to 127, for 16 bit is it is -32767 tp 32767.
	The values -128 and -32767 are greater than one.
	The texcoord values can be extended by using sceGuTexScale() while the
	values for positions can be scaled with sceGumScale().
	For sure there are visual differences when less bits are used.

	The behavior of 2d drawing is different. The values are directly passed
	and not normalized.
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

PSP_MODULE_INFO("IntDrawingModes", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

#define B 0xff444444
#define W 0xffffffff

/* checkerboard pattern */
static const unsigned int __attribute__((aligned(16))) texture[256] = {
#if 1
	W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
	W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
	B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
	B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
	W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
	W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
	B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
	B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
	W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
	W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
	B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
	B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
	W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
	W, W, B, B, W, W, B, B, W, W, B, B, W, W, B, B,
	B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
	B, B, W, W, B, B, W, W, B, B, W, W, B, B, W, W,
#else
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
	B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
	W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
#endif
};

#undef B
#undef W

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

typedef struct {
	float s, t;
	float x, y, z;
} VertT32V32;

typedef struct {
	signed short s, t;
	signed short x, y, z;
} VertT16V16;

typedef struct {
	signed char s, t;
	signed char x, y, z;
} VertT8V8;

typedef struct {
	signed short s, t;
	float x, y, z;
} VertT16V32;

typedef struct {
	signed char s, t;
	float x, y, z;
} VertT8V32;

static VertT32V32 __attribute__((aligned(16))) vertsT32V32[3] = {
	{ 0.0f, 0.0f,  -1.0f, -1.0f,  0.25f },
	{ 1.0f, 0.0f,   1.0f, -1.0f, -0.25f },
	{ 0.5f, 1.0f,   0.0f,  1.0f,  0.00f }
};

static VertT16V16 __attribute__((aligned(16))) vertsT16V16[3] = {
	{     0,     0,  -32767, -32767,  8191 },
	{ 32767,     0,   32767, -32767, -8191 },
	{ 16383, 32767,       0,  32767,     0 }
};

static VertT8V8 __attribute__((aligned(16))) vertsT8V8[3] = {
	{    0,   0,  -127, -127,  31 },
	{  127,   0,   127, -127, -31 },
	{   63, 127,     0,  127,   0 }
};

static VertT16V32 __attribute__((aligned(16))) vertsT16V32[3] = {
	{     0,     0,  -1.0f, -1.0f,  0.25f },
	{ 32767,     0,   1.0f, -1.0f, -0.25f },
	{ 16383, 32767,   0.0f,  1.0f,  0.00f }
};

static VertT8V32 __attribute__((aligned(16))) vertsT8V32[3] = {
	{     0,     0,  -1.0f, -1.0f,  0.25f },
	{   127,     0,   1.0f, -1.0f, -0.25f },
	{    63,   127,   0.0f,  1.0f,  0.00f }
};



typedef struct {
	int prim;
	int flags;
	int count;
	void* data;
	char text[64];
} Object;

static Object objects[] = {
	{ GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 3, vertsT32V32, "tex 32 | pos 32" },
	{ GU_TRIANGLES, GU_TEXTURE_16BIT  | GU_VERTEX_16BIT  | GU_TRANSFORM_3D, 3, vertsT16V16, "tex 16 | pos 16" },
	{ GU_TRIANGLES, GU_TEXTURE_8BIT   | GU_VERTEX_8BIT   | GU_TRANSFORM_3D, 3, vertsT8V8,   "tex  8 | pos  8" },
	{ GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 3, vertsT32V32, "tex 32 | pos 32" },
	{ GU_TRIANGLES, GU_TEXTURE_16BIT  | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 3, vertsT16V32, "tex 16 | pos 32" },
	{ GU_TRIANGLES, GU_TEXTURE_8BIT   | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 3, vertsT8V32,  "tex  8 | pos 32" },
};
static unsigned int o = 0;

int main(int argc, char* argv[]) {
	/* Setup Homebutton Callbacks */
	setupCallbacks();

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
	sceGuFrontFace(GU_CCW);
	sceGuColor(0xffffffff);
	sceGuShadeModel(GU_SMOOTH);
//	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuTexMode(GU_PSM_8888, 0, 0, 0);
	sceGuTexImage(0, 16, 16, 16, texture);
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
	sceGuTexEnvColor(0xffffff);
	sceGuTexFilter(GU_LINEAR, GU_LINEAR);
	sceGuTexWrap(GU_REPEAT, GU_REPEAT);
	sceGuTexScale(1.0f, 1.0f);
	sceGuTexOffset(0.0f, 0.0f);
	sceGuAmbientColor(0xffffffff);

	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);
	
	void* buffer = 0;

	pspDebugScreenInit();

	unsigned int old = 0;
	unsigned int flags = PSP_CTRL_CIRCLE | PSP_CTRL_CROSS;

	int tex = 1;

	while(running()) {
		sceGuStart(GU_DIRECT,list);

		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(90.0f, 480.0/272.0f, 0.1f, 10.0f);

		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();
		ScePspFVector3 trans = { 0.0f, 0.0f, -1.8f };
		sceGumTranslate(&trans);
		
		sceGumMatrixMode(GU_MODEL);
		sceGumLoadIdentity();

		sceGumDrawArray(objects[o].prim, objects[o].flags, objects[o].count, 0, objects[o].data);

		sceCtrlReadBufferPositive(&pad, 1);
		if(old != pad.Buttons) {
			if(pad.Buttons & PSP_CTRL_CROSS) {
				o++;
				if(o >= sizeof(objects) / sizeof(Object)) {
					o = 0;
				}
			}
			if(pad.Buttons & PSP_CTRL_CIRCLE) {
				tex = !tex;
				if(tex) {
					sceGuEnable(GU_TEXTURE_2D);
				} else {
					sceGuDisable(GU_TEXTURE_2D);
				}
			}
		}
		old = pad.Buttons;

		sceGuFinish();
		sceGuSync(0,0);

		pspDebugScreenSetOffset((int)buffer);
		pspDebugScreenSetXY(0, 0);
		pspDebugScreenPrintf("Mode: %s (X to change)    Texture: %s (O to change)", objects[o].text, tex ? "on " : "off");

		sceDisplayWaitVblankStart();
		buffer = sceGuSwapBuffers();
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
