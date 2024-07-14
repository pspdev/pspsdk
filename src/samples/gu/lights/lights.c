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

#include "../common/callbacks.h"
#include "../common/geometry.h"

PSP_MODULE_INFO("Lights Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

#define GRID_COLUMNS 32
#define GRID_ROWS 32
#define GRID_SIZE 10.0f

NPVertex __attribute__((aligned(16))) grid_vertices[GRID_COLUMNS*GRID_ROWS];
unsigned short __attribute__((aligned(16))) grid_indices[(GRID_COLUMNS-1)*(GRID_ROWS-1)*6];

#define TORUS_SLICES 48 // numc
#define TORUS_ROWS 48 // numt
#define TORUS_RADIUS 1.0f
#define TORUS_THICKNESS 0.5f

#define LIGHT_DISTANCE 3.0f

NPVertex __attribute__((aligned(16))) torus_vertices[TORUS_SLICES*TORUS_ROWS];
unsigned short __attribute__((aligned(16))) torus_indices[TORUS_SLICES*TORUS_ROWS*6];

unsigned int colors[4] =
{
	0xffff0000,
	0xff00ff00,
	0xff0000ff,
	0xffff00ff
};

int main(int argc, char* argv[])
{
	unsigned int i;

	setupCallbacks();

	// generate geometry

	generateGridNP(GRID_COLUMNS,GRID_ROWS,GRID_SIZE,GRID_SIZE,grid_vertices,grid_indices);
	generateTorusNP(TORUS_SLICES,TORUS_ROWS,TORUS_RADIUS,TORUS_THICKNESS,torus_vertices,torus_indices);

	// flush cache so that no stray data remains

	sceKernelDcacheWritebackAll();

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
	sceGuDepthRange(0xc350,0x2710);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuEnable(GU_LIGHTING);
	sceGuEnable(GU_LIGHT0);
	sceGuEnable(GU_LIGHT1);
	sceGuEnable(GU_LIGHT2);
	sceGuEnable(GU_LIGHT3);
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// run sample

	int val = 0;

	while(running())
	{
		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0x554433);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// setup a light
	
		for (i = 0; i < 4; ++i)
		{
			ScePspFVector3 pos = { cosf(i*(GU_PI/2) + val * (GU_PI/180)) * LIGHT_DISTANCE, 0, sinf(i*(GU_PI/2) + val * (GU_PI/180)) * LIGHT_DISTANCE };
			sceGuLight(i,GU_POINTLIGHT,GU_DIFFUSE_AND_SPECULAR,&pos);
			sceGuLightColor(i,GU_DIFFUSE,colors[i]);
			sceGuLightColor(i,GU_SPECULAR,0xffffffff);
			sceGuLightAtt(i,0.0f,1.0f,0.0f);
		}

		sceGuSpecular(12.0f);
		sceGuAmbient(0x00222222);

		// setup matrices for cube

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f,16.0f/9.0f,1.0f,1000.0f);

		sceGumMatrixMode(GU_VIEW);
		{
			ScePspFVector3 pos = {0,0,-3.5f};

			sceGumLoadIdentity();
			sceGumTranslate(&pos);
		}

		// draw grid

		sceGumMatrixMode(GU_MODEL);
		{
			ScePspFVector3 pos = {0,-1.5f,0};

			sceGumLoadIdentity();
			sceGumTranslate(&pos);
		}

		sceGuColor(0xff7777);
		sceGumDrawArray(GU_TRIANGLES,NP_VERTEX_FORMAT|GU_INDEX_16BIT|GU_TRANSFORM_3D,sizeof(grid_indices)/sizeof(unsigned short),grid_indices,grid_vertices);

		// draw torus

		sceGumMatrixMode(GU_MODEL);
		{
			ScePspFVector3 rot = {val * 0.79f * (GU_PI/180.0f), val * 0.98f * (GU_PI/180.0f), val * 1.32f * (GU_PI/180.0f)};

			sceGumLoadIdentity();
			sceGumRotateXYZ(&rot);
		}

		sceGuColor(0xffffff);
		sceGumDrawArray(GU_TRIANGLES,NP_VERTEX_FORMAT|GU_INDEX_16BIT|GU_TRANSFORM_3D,sizeof(torus_indices)/sizeof(unsigned short),torus_indices,torus_vertices);

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
