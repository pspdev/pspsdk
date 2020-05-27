/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * timing.c - Shows gu time messuaring
 *
 * Copyright (c) 2007 McZonk
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <pspge.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspctrl.h>

PSP_MODULE_INFO("Timing Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

typedef struct {
	float x, y, z;
} VERT3D;

#define TORUS_SEGMENTS 8
#define TORUS_SLICES   8
#define TORUS_IRADIUS  0.5f
#define TORUS_ORADIUS  1.0f

#define BLUR_RADIUS 4

static VERT3D __attribute__((aligned(16))) indexedTorus[TORUS_SEGMENTS][TORUS_SLICES];

static VERT3D __attribute__((aligned(16))) triangleTorus[TORUS_SEGMENTS][TORUS_SLICES*6];

static VERT3D __attribute__((aligned(16))) tristripTorus[TORUS_SEGMENTS][TORUS_SLICES*2+2];

static VERT3D __attribute__((aligned(16))) splineTorus[TORUS_SEGMENTS+3][TORUS_SLICES+3];


int SetupCallbacks();

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

void buildIndexedTorus() {
	const float thickness = TORUS_ORADIUS - TORUS_IRADIUS;

	unsigned int i, j;
	for(i = 0; i < TORUS_SEGMENTS; i++) {
		float x = cosf((float)i / (float)TORUS_SEGMENTS * (2.0f*GU_PI));
		float z = sinf((float)i / (float)TORUS_SEGMENTS * (2.0f*GU_PI));

		for(j = 0; j < TORUS_SLICES; j++) {
			float t = cosf((float)j / (float)TORUS_SLICES * (2.0f*GU_PI)) * (thickness / 2.0f) + TORUS_IRADIUS;
			float y = sinf((float)j / (float)TORUS_SLICES * (2.0f*GU_PI)) * (thickness / 2.0f);

			indexedTorus[i][j].x = x * t;
			indexedTorus[i][j].y = y;
			indexedTorus[i][j].z = z * t;
		}
	}
}

void buildTriangleTorus() {
	unsigned int i, j;
	for(i = 0; i < TORUS_SEGMENTS; i++) {
		unsigned int x0 =  i    % TORUS_SEGMENTS;
		unsigned int x1 = (i+1) % TORUS_SEGMENTS;
		for(j = 0; j < TORUS_SLICES; j++) {
			unsigned int y0 =  j    % TORUS_SLICES;
			unsigned int y1 = (j+1) % TORUS_SLICES;

			triangleTorus[i][j*6+0].x = indexedTorus[x0][y0].x;
			triangleTorus[i][j*6+0].y = indexedTorus[x0][y0].y;
			triangleTorus[i][j*6+0].z = indexedTorus[x0][y0].z;

			triangleTorus[i][j*6+1].x = indexedTorus[x1][y0].x;
			triangleTorus[i][j*6+1].y = indexedTorus[x1][y0].y;
			triangleTorus[i][j*6+1].z = indexedTorus[x1][y0].z;

			triangleTorus[i][j*6+2].x = indexedTorus[x0][y1].x;
			triangleTorus[i][j*6+2].y = indexedTorus[x0][y1].y;
			triangleTorus[i][j*6+2].z = indexedTorus[x0][y1].z;

			triangleTorus[i][j*6+3].x = indexedTorus[x1][y0].x;
			triangleTorus[i][j*6+3].y = indexedTorus[x1][y0].y;
			triangleTorus[i][j*6+3].z = indexedTorus[x1][y0].z;

			triangleTorus[i][j*6+4].x = indexedTorus[x1][y1].x;
			triangleTorus[i][j*6+4].y = indexedTorus[x1][y1].y;
			triangleTorus[i][j*6+4].z = indexedTorus[x1][y1].z;
			
			triangleTorus[i][j*6+5].x = indexedTorus[x0][y1].x;
			triangleTorus[i][j*6+5].y = indexedTorus[x0][y1].y;
			triangleTorus[i][j*6+5].z = indexedTorus[x0][y1].z;
		}
	}
}

void buildTristripTorus() {
	unsigned int i, j;
	for(i = 0; i < TORUS_SEGMENTS; i++) {
		unsigned int x0 = i     % TORUS_SEGMENTS;
		unsigned int x1 = (i+1) % TORUS_SEGMENTS;
		for(j = 0; j < TORUS_SLICES + 1; j++) {
			unsigned int y = j % TORUS_SLICES;

			tristripTorus[i][j*2+0].x = indexedTorus[x0][y].x;
			tristripTorus[i][j*2+0].y = indexedTorus[x0][y].y;
			tristripTorus[i][j*2+0].z = indexedTorus[x0][y].z;

			tristripTorus[i][j*2+1].x = indexedTorus[x1][y].x;
			tristripTorus[i][j*2+1].y = indexedTorus[x1][y].y;
			tristripTorus[i][j*2+1].z = indexedTorus[x1][y].z;
		}
	}
}

void buildSplineTorus() {
	unsigned int i, j;
	for(i = 0; i <= TORUS_SEGMENTS + 2; i++) {
		unsigned int x = i % TORUS_SEGMENTS;
		for(j = 0; j <= TORUS_SLICES + 2; j++) {
			unsigned int y = j % TORUS_SLICES;

			splineTorus[i][j].x = indexedTorus[x][y].x;
			splineTorus[i][j].y = indexedTorus[x][y].y;
			splineTorus[i][j].z = indexedTorus[x][y].z;
		}
	}
}

static unsigned int start = 0;
static unsigned int end = 0;

static const char* modenames[] = {
	"Triangles  ",
	"Tristrips  ",
	"Spline(1,1)",
	"Spline(2,2)",
	"Spline(4,4)",
	"Spline(8,8)"
};

static void gucallback(int id) {
	if(id == 1) {
		start = clock();
	} else if(id == 2) {
		end = clock();
	}
}

int main(int argc, char** argv) {
	SetupCallbacks();

	buildIndexedTorus();
	buildTriangleTorus();
	buildTristripTorus();
	buildSplineTorus();

	pspDebugScreenInit();

	sceKernelDcacheWritebackAll();

	void* frameBuffer  = (void*)0;
	void* doubleBuffer = (void*)0x88000;
	void* depthBuffer  = (void*)0x110000;

	sceGuInit();

	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,frameBuffer,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,doubleBuffer,BUF_WIDTH);
	sceGuDepthBuffer(depthBuffer,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(0xc350,0x2710);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	//sceGuEnable(GU_CULL_FACE);
	sceGuDisable(GU_TEXTURE_2D);
	sceGuSetCallback(GU_CALLBACK_SIGNAL, gucallback);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	int mode = 0;
	int val = 0;

	SceCtrlData pad;
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);
	unsigned int old = 0;

	while(1) {
		sceGuStart(GU_DIRECT, list);

		sceGuClearDepth(0);
		sceGuClearColor(0xff000000);
		sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

		sceGuColor(0xff66ccff);
		
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f, 16.0f/9.0f, 0.5f, 10.0f);

		sceGumMatrixMode(GU_VIEW);
		ScePspFVector3 pos = {0.0f,0.0f,-1.5f};
		sceGumLoadIdentity();
		sceGumTranslate(&pos);

		sceGumMatrixMode(GU_MODEL);
		ScePspFVector3 rot = {val * 0.263f * (GU_PI/180.0f), val * 0.32f * (GU_PI/180.0f), val * 0.44f * (GU_PI/180.0f)};
		sceGumLoadIdentity();
		sceGumRotateXYZ(&rot);

		switch(mode) {
			case 0 :
				sceGuSignal(GU_BEHAVIOR_SUSPEND, 1);
				sceGumDrawArray(GU_TRIANGLES, GU_VERTEX_32BITF, TORUS_SEGMENTS * TORUS_SLICES * 6, 0, triangleTorus);
				sceGuSignal(GU_BEHAVIOR_SUSPEND, 2);
				break;

			case 1 :
				sceGuSignal(GU_BEHAVIOR_SUSPEND, 1);
				sceGumDrawArrayN(GU_TRIANGLE_STRIP, GU_VERTEX_32BITF, TORUS_SLICES*2+2, TORUS_SEGMENTS, 0, tristripTorus);
				sceGuSignal(GU_BEHAVIOR_SUSPEND, 2);
				break;

			case 2 :
				sceGuPatchDivide(1, 1);
				sceGuSignal(GU_BEHAVIOR_SUSPEND, 1);
				sceGumDrawSpline(GU_VERTEX_32BITF, TORUS_SEGMENTS + 3, TORUS_SLICES + 3, GU_FILL_FILL, GU_FILL_FILL, 0, splineTorus);
				sceGuSignal(GU_BEHAVIOR_SUSPEND, 2);
				break;

			case 3 :
				sceGuPatchDivide(2, 2);
				sceGuSignal(GU_BEHAVIOR_SUSPEND, 1);
				sceGumDrawSpline(GU_VERTEX_32BITF, TORUS_SEGMENTS + 3, TORUS_SLICES + 3, GU_FILL_FILL, GU_FILL_FILL, 0, splineTorus);
				sceGuSignal(GU_BEHAVIOR_SUSPEND, 2);
				break;

			case 4 :
				sceGuPatchDivide(4, 4);
				sceGuSignal(GU_BEHAVIOR_SUSPEND, 1);
				sceGumDrawSpline(GU_VERTEX_32BITF, TORUS_SEGMENTS + 3, TORUS_SLICES + 3, GU_FILL_FILL, GU_FILL_FILL, 0, splineTorus);
				sceGuSignal(GU_BEHAVIOR_SUSPEND, 2);
				break;

			default :
				sceGuPatchDivide(8, 8);
				sceGuSignal(GU_BEHAVIOR_SUSPEND, 1);
				sceGumDrawSpline(GU_VERTEX_32BITF, TORUS_SEGMENTS + 3, TORUS_SLICES + 3, GU_FILL_FILL, GU_FILL_FILL, 0, splineTorus);
				sceGuSignal(GU_BEHAVIOR_SUSPEND, 2);
				break;
		}
		sceGuFinish();
		sceGuSync(0, 0);

		pspDebugScreenSetOffset((int)frameBuffer);
		pspDebugScreenSetXY(0,0);
		pspDebugScreenPrintf("%s: %1d.%03d ms", modenames[mode], (end - start)/1000, (end - start)%1000);

		frameBuffer = (void*)sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

		val++;

		sceCtrlReadBufferPositive(&pad, 1);
		if(old != pad.Buttons) {
			if(pad.Buttons & (PSP_CTRL_CROSS | PSP_CTRL_CIRCLE)) {
				mode+=1;
				mode%=6;
			}
		}
		old = pad.Buttons;
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
