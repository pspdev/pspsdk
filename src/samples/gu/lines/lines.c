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
#include <time.h>

#include <pspgu.h>

#include "../common/callbacks.h"

PSP_MODULE_INFO("Lines Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
	float x,y,z;
};

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
	0xff00ffff
};

#define NUM_LINES 12
#define NUM_VERTICES 8
#define SPEED 4.0f
#define FADE_SPEED 0.015f;

struct Vertex lines[NUM_LINES][NUM_VERTICES];
unsigned int curr_line = 0;
struct Vertex position[8];
struct Vertex direction[8];

float fade = 0;
unsigned int color_index = 0;

int main(int argc, char* argv[])
{
	unsigned int i;

	setupCallbacks();

	// initialize lines

	memset(lines,0,sizeof(lines));

	srand(time(0));

	for (i = 0; i < NUM_VERTICES; ++i)
	{
		position[i].x = (((float)rand())/RAND_MAX) * (SCR_WIDTH-1);
		position[i].y = (((float)rand())/RAND_MAX) * (SCR_HEIGHT-1);

		direction[i].x = (((float)rand())/(RAND_MAX/2)-1.0f) * SPEED;
		direction[i].y = (((float)rand())/(RAND_MAX/2)-1.0f) * SPEED;
	}

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
	sceGuDepthRange(65535,0);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// run sample

	while(running())
	{
		unsigned int i,j;
		unsigned int result;

		// update lines

		for (i = 0; i < NUM_VERTICES; ++i)
		{
			position[i].x += direction[i].x;
			position[i].y += direction[i].y;

			if (position[i].x < 0)
			{
				position[i].x = 0;
				direction[i].x = (((float)rand())/RAND_MAX) * SPEED;
				direction[i].y += 0.1f * (direction[i].y / fabsf(direction[i].y));
			}
			else if (position[i].x >= SCR_WIDTH)
			{
				position[i].x = (SCR_WIDTH-1);
				direction[i].x = -(((float)rand())/RAND_MAX) * SPEED;
				direction[i].y += 0.1f * (direction[i].y / fabsf(direction[i].y));
			}

			if (position[i].y < 0)
			{
				position[i].y = 0;
				direction[i].x += 0.1f * (direction[i].x / fabsf(direction[i].x));
				direction[i].y = (0.1f+((float)rand())/RAND_MAX) * SPEED;
			}
			else if (position[i].y >= SCR_HEIGHT)
			{
				position[i].y = (SCR_HEIGHT-1);
				direction[i].x += 0.1f * (direction[i].x / fabsf(direction[i].x));
				direction[i].y = -(0.1f+((float)rand())/RAND_MAX) * SPEED;
			}

			lines[curr_line][i].x = position[i].x;
			lines[curr_line][i].y = position[i].y;
		}
		curr_line = (curr_line+1) % NUM_LINES;

		fade += FADE_SPEED;
		if (fade >= 1.0f)
		{
			fade -= 1.0f;
			color_index = (color_index+1) & 7;
		}

		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0);
		sceGuClear(GU_COLOR_BUFFER_BIT);

		// render lines

		result = 0;
		for (i = 0; i < 4; ++i)
		{
			int ca = (colors[color_index] >> (i*8)) & 0xff;
			int cb = (colors[(color_index+1)&7] >> (i*8)) & 0xff;
			result |= ((unsigned char)(ca + (cb-ca) * fade)) << (i*8);
		}
		
		sceGuColor(result);

		for (i = 0; i < NUM_LINES; ++i)
		{
			// we make local copies of the line into the main buffer here, so we don't have to flush the cache

			struct Vertex* vertices = sceGuGetMemory((NUM_VERTICES+1) * sizeof(struct Vertex));

			// create a lineloop

			for (j = 0; j < NUM_VERTICES; ++j)
				vertices[j] = lines[i][j];
			vertices[NUM_VERTICES] = lines[i][0];
		
			sceGuDrawArray(GU_LINE_STRIP,GU_VERTEX_32BITF|GU_TRANSFORM_2D,(NUM_VERTICES+1),0,vertices);
		}

		// wait for next frame

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
