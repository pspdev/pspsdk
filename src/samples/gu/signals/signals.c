/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * signals.c - Sample to demonstrate usage of GE signals under libgu API.
 *
 * At the start of each frame 2 vertex buffers are allocated, filled with
 * data and submitted to the command-list. As soon as GPU finishes rendering
 * from one of the buffers, signal is raised and interrupt handler is called
 * allowing application to reuse the same buffer by filling it with data and
 * submitting it back to the command-list.
 *
 * Sample renders 64K dynamic billboards at ~25fps using 2 vertex buffers
 * pushing 3MB of vertex data to GE each frame.
 *
 *
 * Copyright (c) 2005 Jesper Svennevid
 * Copyright (c) 2005 Renaldas Zioma <rej@scene.lt>
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <pspge.h>
#include <pspgu.h>
#include <pspgum.h>

//#define ENABLE_PROFILER
//#define ENABLE_FRAMERATE
#define USING_SIGNALS

PSP_MODULE_INFO("GE Signals Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);


#define printf	pspDebugScreenPrintf

static unsigned int __attribute__((aligned(16))) list[262144];
static unsigned int __attribute__((aligned(16))) smallList1[1024];
static unsigned int __attribute__((aligned(16))) smallList2[1024];
extern unsigned char ball_start[];

typedef struct InputVertex
{
	float x,y,z;
} InputVertex;

typedef struct Vertex
{
	float u, v;				// 8
	unsigned int color;		// 4
	float x,y,z;			// 12
} Vertex;

Vertex __attribute__((aligned(16))) cubeVertices[12*3] =
{
	{0, 0, 0xff7f0000,-1,-1, 1}, // 0
	{1, 0, 0xff7f0000,-1, 1, 1}, // 4
	{1, 1, 0xff7f0000, 1, 1, 1}, // 5

	{0, 0, 0xff7f0000,-1,-1, 1}, // 0
	{1, 1, 0xff7f0000, 1, 1, 1}, // 5
	{0, 1, 0xff7f0000, 1,-1, 1}, // 1

	{0, 0, 0xff7f0000,-1,-1,-1}, // 3
	{1, 0, 0xff7f0000, 1,-1,-1}, // 2
	{1, 1, 0xff7f0000, 1, 1,-1}, // 6

	{0, 0, 0xff7f0000,-1,-1,-1}, // 3
	{1, 1, 0xff7f0000, 1, 1,-1}, // 6
	{0, 1, 0xff7f0000,-1, 1,-1}, // 7

	{0, 0, 0xff007f00, 1,-1,-1}, // 0
	{1, 0, 0xff007f00, 1,-1, 1}, // 3
	{1, 1, 0xff007f00, 1, 1, 1}, // 7

	{0, 0, 0xff007f00, 1,-1,-1}, // 0
	{1, 1, 0xff007f00, 1, 1, 1}, // 7
	{0, 1, 0xff007f00, 1, 1,-1}, // 4

	{0, 0, 0xff007f00,-1,-1,-1}, // 0
	{1, 0, 0xff007f00,-1, 1,-1}, // 3
	{1, 1, 0xff007f00,-1, 1, 1}, // 7

	{0, 0, 0xff007f00,-1,-1,-1}, // 0
	{1, 1, 0xff007f00,-1, 1, 1}, // 7
	{0, 1, 0xff007f00,-1,-1, 1}, // 4

	{0, 0, 0xff00007f,-1, 1,-1}, // 0
	{1, 0, 0xff00007f, 1, 1,-1}, // 1
	{1, 1, 0xff00007f, 1, 1, 1}, // 2

	{0, 0, 0xff00007f,-1, 1,-1}, // 0
	{1, 1, 0xff00007f, 1, 1, 1}, // 2
	{0, 1, 0xff00007f,-1, 1, 1}, // 3

	{0, 0, 0xff00007f,-1,-1,-1}, // 4
	{1, 0, 0xff00007f,-1,-1, 1}, // 7
	{1, 1, 0xff00007f, 1,-1, 1}, // 6

	{0, 0, 0xff00007f,-1,-1,-1}, // 4
	{1, 1, 0xff00007f, 1,-1, 1}, // 6
	{0, 1, 0xff00007f, 1,-1,-1}, // 5
};


int SetupCallbacks();

void create_modified_torus_billboards(Vertex* vertices, float* world, float t, int startSlice, int sliceCount );
void render_billboards(unsigned int i);
void mySignalHandler(int id);
void myFinishHandler(int id);

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

#define NUM_SLICES (128)
#define NUM_ROWS (128*4)
#define RING_SIZE (2.0f)
#define RING_RADIUS (1.0f)
#define SPRITE_SIZE (0.025f*0.5f)

#define NUM_VERTEX_BUFFERS 2
#define NUM_ITERATIONS 16


#define printf	pspDebugScreenPrintf

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

InputVertex __attribute__((aligned(64))) torus_vertices[NUM_SLICES * NUM_ROWS];
InputVertex __attribute__((aligned(16))) torus_modifiers[NUM_ROWS];

// Global data
typedef struct GlobalContext
{
	Vertex* vbuffer[NUM_VERTEX_BUFFERS];
	int vertsRendered;

	ScePspFMatrix4 world;
	int iterationCount;
	float t;
	float sint;
} GlobalContext;

GlobalContext g_context;

int main(int argc, char* argv[])
{
	unsigned int i,j;

	pspDebugScreenInit();
	SetupCallbacks();

#ifdef ENABLE_PROFILER
	// Enable profiling 
	pspDebugProfilerClear();
	pspDebugProfilerEnable();
#endif

	// initialize global context
	g_context.iterationCount = NUM_VERTEX_BUFFERS * NUM_ITERATIONS;
	g_context.t = 0;
	g_context.sint = 0;

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

	// initialize torus modifiers

	for (j = 0; j < NUM_ROWS; ++j)
	{
		float t = j;
		torus_modifiers[j].x = 0;
		torus_modifiers[j].y = 0;
		torus_modifiers[j].z = 0.3*cosf( t * 8.0f *((GU_PI*2)/NUM_ROWS) );
	}

	// init GU and set callbacks
	sceGuInit();

	// 0x01 - user callback
	// 0x04 - 'rendering finished' callback
	sceGuSetCallback(1, &mySignalHandler);
	sceGuSetCallback(4, &myFinishHandler);

	// setup GU
	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,(void*)0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,(void*)0x88000,BUF_WIDTH);
	sceGuDepthBuffer((void*)0x110000,BUF_WIDTH);
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

#ifdef USING_SIGNALS
	sceGuCallMode(1);
#endif

	// generate callable command-list with texture setup
	{
		sceGuStart(GU_CALL, smallList1);

		// setup texture
		sceGuTexMode(GU_PSM_5551,0,0,0);
		sceGuTexImage(0,32,32,32,ball_start); // width, height, buffer width, tbp
		sceGuTexFunc(GU_TFX_MODULATE,GU_TCC_RGBA); // NOTE: this enables reads of the alpha-component from the texture, otherwise blend/test won't work
		sceGuTexFilter(GU_NEAREST,GU_NEAREST);
		sceGuTexWrap(GU_CLAMP,GU_CLAMP);
		sceGuTexScale(1,1);
		sceGuTexOffset(0,0);
		sceGuAmbientColor(0xffffffff);

		sceGuFinish();
		sceGuSync(0,0);
	}

	// generate callable command-list for cube rendering
	{
		sceGuStart(GU_CALL, smallList2);

		// draw cube
		sceGuDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,12*3,0,cubeVertices);

		sceGuFinish();
		sceGuSync(0,0);
	}

	for(;;)
	{
		sceGuStart(GU_DIRECT,list);

		unsigned int i = 0;
		for( ; i < NUM_VERTEX_BUFFERS; i++ )
			g_context.vbuffer[i] = sceGuGetMemory((NUM_SLICES/g_context.iterationCount) * 2 * NUM_ROWS * sizeof(Vertex));
		g_context.vertsRendered = 0;

		// clear screen
		sceGuClearColor(0x00334455);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// setup matrices
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f,16.0f/9.0f,0.5f,1000.0f);

		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		sceGumMatrixMode(GU_MODEL);
		{
			ScePspFVector3 pos = {0.0f,0.0f,-3.5f};
			ScePspFVector3 rot = {g_context.t * 0.3f * (GU_PI/180.0f), g_context.t * 0.7f * (GU_PI/180.0f), g_context.t * 1.3f * (GU_PI/180.0f)};

			sceGumLoadIdentity();
			sceGumTranslate(&pos);
			sceGumRotateXYZ(&rot);
		}

		sceGumStoreMatrix(&g_context.world);

		// call pregenerated command-list to setup texture		
		sceGuCallList(smallList1);

		// start billboard rendering
		render_billboards(0);

		// call pregenerated command-list to render cube
		{
			ScePspFVector3 scale = {0.3f, 0.3f, 0.3f};
			sceGumScale(&scale);
		}

		sceGumUpdateMatrix();
		sceGuCallList(smallList2);	

#ifndef USING_SIGNALS
		// HACK: sceGuFinish() is called inside the signal interupt handler when all rendering job is done
		// this is done in order to stall GPU if it is ahead of CPU
		sceGuFinish();
#endif
		sceGuSync(0,0);

#ifndef ENABLE_FRAMERATE
		// wait for next frame
		sceDisplayWaitVblankStart();
#endif
		sceGuSwapBuffers();

		pspDebugScreenSetXY(0,0);

#ifdef ENABLE_PROFILER
		// Print profile information to the screen
		pspDebugProfilerPrint();
#endif

#ifdef ENABLE_FRAMERATE
		// simple frame rate counter
		static float curr_ms = 1.0f;
		static struct timeval time_slices[16];
		static int t = 0;

		float curr_fps = 1.0f / curr_ms;

		t++;
		
		float vertsPerSec = g_context.vertsRendered*curr_fps;
		float kbPerSec = vertsPerSec * sizeof(Vertex) / 1024.0f;
		gettimeofday(&time_slices[t & 15],0);
		pspDebugScreenPrintf("fps: %d.%03d  ms: %d  vert/s: %dK  MB/s: %d.%03d",(int)curr_fps, ((int)(curr_fps*1000.0f)%1000), (int)(curr_ms*1000.0f),
			(int)(vertsPerSec/1000.0f),
			(int)(kbPerSec/1024.0f), (int)((1000.0f/1024.0f)*((int)kbPerSec%1024)) );

		if (!(t & 15))
		{
			struct timeval last_time = time_slices[0];
			unsigned int i;

			curr_ms = 0;
			for (i = 1; i < 16; ++i)
			{
				struct timeval curr_time = time_slices[i];

				int curr_time_usec = curr_time.tv_usec + curr_time.tv_sec * 1000000;
				int last_time_usec = last_time.tv_usec + last_time.tv_sec * 1000000;

				if( last_time_usec < curr_time_usec )
					curr_ms += (( curr_time_usec - last_time_usec ) * (1.0f/1000000.0f));

				last_time = time_slices[i];
			}
			curr_ms /= 15.0f;
		}
#endif
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}

/* user signal handler */
void mySignalHandler(int id)
{
	render_billboards(id);
}

/* 'rendering finished' signal handler */
void myFinishHandler(int id)
{
	// do some animations
	g_context.t += 0.6f;
	g_context.sint = sinf(g_context.t / 2.0f);
}

/* renders subset of billboards array */
void render_billboards(unsigned int i)
{
	if (i >= g_context.iterationCount) return;


	Vertex* vbuffer = g_context.vbuffer[i%NUM_VERTEX_BUFFERS];
	int sliceCount = NUM_SLICES / g_context.iterationCount;

	// fill current vertex buffer if we just started
	if (i == 0)
	{
		create_modified_torus_billboards(vbuffer,(float*)&g_context.world, g_context.sint, sliceCount*i, sliceCount);
	}

	// render previously generated vertex buffer
	sceGumMatrixMode(GU_MODEL);
	sceGumLoadMatrix(&g_context.world);
	sceGumDrawArray(GU_SPRITES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,sliceCount*NUM_ROWS*2,0,vbuffer);
	g_context.vertsRendered += sliceCount*NUM_ROWS*2;

	// fill next vertex buffer for future rendering
	int nextI = i + 1;
	if (nextI < g_context.iterationCount )
	{	
		Vertex* vbufferNext;
		vbufferNext = g_context.vbuffer[nextI%NUM_VERTEX_BUFFERS];
		create_modified_torus_billboards(vbufferNext,(float*)&g_context.world, g_context.sint, sliceCount*nextI, sliceCount);
	}

#ifdef USING_SIGNALS
	// send a signal when rendering was completed
	// signals 0x01..0x03 - seems to be available for custom usage
	sceGuSignal( 1, nextI );

	// HACK: keeps CPU waiting until all jobs were submitted for GPU
	if (nextI == g_context.iterationCount)
		sceGuFinish();
#endif
}

/* this function generates the billboards rendered by sceGumDrawArray() */
void create_modified_torus_billboards( Vertex* vertices, float* world, float t, int startSlice, int sliceCount )
{
	unsigned int i,j;
	float sx, sy, sz;

	// calculate billboard world offsets

	sx = SPRITE_SIZE * world[(0 << 2)+0] + SPRITE_SIZE * world[(0 << 2)+1];
	sy = SPRITE_SIZE * world[(1 << 2)+0] + SPRITE_SIZE * world[(1 << 2)+1];
	sz = SPRITE_SIZE * world[(2 << 2)+0] + SPRITE_SIZE * world[(2 << 2)+1];

	Vertex* curr = vertices;
	for (i = startSlice; i < startSlice + sliceCount; ++i)
	{
		InputVertex* inrow = &torus_vertices[i * NUM_ROWS];

		for (j = 0; j < NUM_ROWS; ++j)
		{
			InputVertex* incurr = &inrow[j];

			float x, y, z;

			x = incurr->x;
			y = incurr->y;
			z = incurr->z;

			x += torus_modifiers[j].x * t;
			y += torus_modifiers[j].y * t;
			z += torus_modifiers[j].z * t;

			curr->u = 0.0f;
			curr->v = 0.0f;
			curr->color = colors[(i+j)&7];
			curr->x = x - sx;
			curr->y = y - sy;
			curr->z = z - sz;
			++curr;

			curr->u = 1.0f;
			curr->v = 1.0f;
			curr->color = colors[(i+j)&7];
			curr->x = x + sx;
			curr->y = y + sy;
			curr->z = z + sz;
			++curr;
		}
	}
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

