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

PSP_MODULE_INFO("Sprite Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];
extern unsigned char ball_start[];

struct InputVertex
{
	float x,y,z;
};

struct Vertex
{
	float u, v;
	unsigned int color;
	float x,y,z;
};

void create_torus_billboards(struct Vertex* vertices, float* world);

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

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
	0xff101010
};

struct InputVertex torus_vertices[NUM_SLICES * NUM_ROWS];

int main(int argc, char* argv[])
{
	unsigned int i,j;

	setupCallbacks();

	// initialize torus

	for (i = 0; i < NUM_SLICES; ++i)
	{
		for (j = 0; j < NUM_ROWS; ++j)
		{
			float s = i + 0.5f, t = j;
			float x,y,z;

			x = (RING_SIZE + RING_RADIUS * cosf(s * ((GU_PI*2)/NUM_SLICES))) * cosf(t * ((GU_PI*2)/NUM_ROWS));
			y = (RING_SIZE + RING_RADIUS * cosf(s * ((GU_PI*2)/NUM_SLICES))) * sinf(t * ((GU_PI*2)/NUM_ROWS));
			z = RING_RADIUS * sinf(s * ((GU_PI*2)/NUM_SLICES));

			torus_vertices[j + i * NUM_ROWS].x = x;
			torus_vertices[j + i * NUM_ROWS].y = y;
			torus_vertices[j + i * NUM_ROWS].z = z;
		}
	}

	// setup GU

	sceGuInit();

	void* fbp0 = guGetStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	void* fbp1 = guGetStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	void* zbp = guGetStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_4444);

	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,fbp0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,fbp1,BUF_WIDTH);
	sceGuDepthBuffer(zbp,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(0xc350,0x2710);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuAlphaFunc(GU_GREATER,0,0xff);
	sceGuEnable(GU_ALPHA_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// run sample

	ScePspFMatrix4 world;

	float val = 0;

	while(running())
	{
		struct Vertex* vertices;

		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0xff554433);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// setup texture

		sceGuTexMode(GU_PSM_5551,0,0,0);
		sceGuTexImage(0,32,32,32,ball_start); // width, height, buffer width, tbp
		sceGuTexFunc(GU_TFX_MODULATE,GU_TCC_RGBA); // NOTE: this enables reads of the alpha-component from the texture, otherwise blend/test won't work
		sceGuTexFilter(GU_NEAREST,GU_NEAREST);
		sceGuTexWrap(GU_CLAMP,GU_CLAMP);
		sceGuTexScale(1,1);
		sceGuTexOffset(0,0);
		sceGuAmbientColor(0xffffffff);

		// setup transforms

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f,16.0f/9.0f,0.5f,1000.0f);

		sceGumMatrixMode(GU_VIEW);
		{
			ScePspFVector3 pos = {0.0f,0.0f,-3.5f};

			sceGumLoadIdentity();
			sceGumTranslate(&pos);
		}

		sceGumMatrixMode(GU_MODEL);
		{
			ScePspFVector3 rot = {val * 0.3f * (GU_PI/180.0f), val * 0.7f * (GU_PI/180.0f), val * 1.3f * (GU_PI/180.0f)};

			sceGumLoadIdentity();
			sceGumRotateXYZ(&rot);
		}
		sceGumStoreMatrix(&world);

		// render torus

		vertices = sceGuGetMemory(NUM_SLICES * NUM_ROWS * 2 * sizeof(struct Vertex));
		create_torus_billboards(vertices,(float*)&world);

		sceGumDrawArray(GU_SPRITES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,NUM_SLICES*NUM_ROWS*2,0,vertices);

		// wait for next frame

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

		val += 0.6f;
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}

/* this function generates the billboards rendered by sceGuDrawArray() */
void create_torus_billboards(struct Vertex* vertices, float* world)
{
	unsigned int i,j;
	float sx, sy, sz;

	// calculate billboard world offsets

	sx = SPRITE_SIZE * world[(0 << 2)+0] + SPRITE_SIZE * world[(0 << 2)+1];
	sy = SPRITE_SIZE * world[(1 << 2)+0] + SPRITE_SIZE * world[(1 << 2)+1];
	sz = SPRITE_SIZE * world[(2 << 2)+0] + SPRITE_SIZE * world[(2 << 2)+1];

	for (i = 0; i < NUM_SLICES; ++i)
	{
		struct Vertex* row = &vertices[i * NUM_ROWS * 2];
		struct InputVertex* inrow = &torus_vertices[i * NUM_ROWS];

		for (j = 0; j < NUM_ROWS; ++j)
		{
			struct Vertex* curr = &row[j << 1];
			struct InputVertex* incurr = &inrow[j];
			float x, y, z;

			x = incurr->x;
			y = incurr->y;
			z = incurr->z;

			curr[0].u = 0;
			curr[0].v = 0;
			curr[0].color = colors[(i+j)&7];
			curr[0].x = x - sx;
			curr[0].y = y - sy;
			curr[0].z = z - sz;

			curr[1].u = 1;
			curr[1].v = 1;
			curr[1].color = colors[(i+j)&7];
			curr[1].x = x + sx;
			curr[1].y = y + sy;
			curr[1].z = z + sz;
		}
	}
}
