/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * skinning.c - Sample to demonstrate matrix skinning using 8 weights per vertex
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

PSP_MODULE_INFO("Matrix Skinning Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

#define WEIGHTS_PER_VERTEX 8
typedef struct Vertex
{
	float skinWeight[WEIGHTS_PER_VERTEX];
	float u,v;
	unsigned int color;
	float nx,ny,nz;
	float x,y,z;
} Vertex;

/* cylinder */

#define CYLINDER_SLICES 48 // numc
#define CYLINDER_ROWS 48 // numt
#define CYLINDER_RADIUS 0.35f
#define CYLINDER_LENGTH 1.25f

Vertex __attribute__((aligned(16))) cylinder_vertices[CYLINDER_SLICES*CYLINDER_ROWS];
unsigned short __attribute__((aligned(16))) cylinder_indices[CYLINDER_SLICES*(CYLINDER_ROWS-1)*6];

#define min( a, b ) ( ((a)<(b))?(a):(b) )
#define max( a, b ) ( ((a)>(b))?(a):(b) )
 
int SetupCallbacks();

void genSkinnedCylinder( unsigned slices, unsigned rows, float length, float radius, unsigned bones,
	Vertex* dstVertices, unsigned short* dstIndices );

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

#define HIERARCHY_SIZE (WEIGHTS_PER_VERTEX)

int main(int argc, char* argv[])
{
	SetupCallbacks();

	// generate geometry

	genSkinnedCylinder( CYLINDER_ROWS, CYLINDER_SLICES, CYLINDER_LENGTH, CYLINDER_RADIUS, HIERARCHY_SIZE, cylinder_vertices, cylinder_indices );

	// flush cache so that no stray data remains

	sceKernelDcacheWritebackAll();

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
	sceGuEnable(GU_DITHER);

	// setup a light
	ScePspFVector3 lightDir = { 0, 0, 1 };
	sceGuLight(0,GU_DIRECTIONAL,GU_DIFFUSE,&lightDir);
	sceGuLightColor(0,GU_DIFFUSE,0x00ff4040);
	sceGuLightAtt(0,1.0f,0.0f,0.0f);
	sceGuAmbient(0x00202020);
	sceGuEnable(GU_LIGHTING);
	sceGuEnable(GU_LIGHT0);

	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// setup matrices

	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	sceGumPerspective(75.0f,16.0f/9.0f,0.5f,1000.0f);

	sceGumMatrixMode(GU_VIEW);
	{
		ScePspFVector3 pos = {0,0,-5.0f};

		sceGumLoadIdentity();
		sceGumTranslate(&pos);
	}

	// setup bones hierarchy

	ScePspFMatrix4 bones[HIERARCHY_SIZE];
	float boneLength = CYLINDER_LENGTH;

	// run sample

	int val = 0;
	int q;

	for(;;)
	{
		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0xff554433);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// update matrices

		for( q = 0; q < HIERARCHY_SIZE; ++q )
		{
			ScePspFVector3 rot = {0,0,cosf( val * 1.0f * (GU_PI/180.0f))};

			gumLoadIdentity(&bones[q]);
			gumRotateXYZ(&bones[q],&rot);

			if( q > 0 )
			{
				ScePspFVector3 pos = {boneLength, 0, 0};

				gumTranslate(&bones[q], &pos);
				gumMultMatrix(&bones[q], &bones[q-1], &bones[q]);
			}

			// set matrices for skinning

			sceGuBoneMatrix( q, &bones[q] );
			sceGuMorphWeight( q, 1.0f );
		}

		sceGumMatrixMode(GU_MODEL);
		{
			ScePspFVector3 rot = {GU_PI/7.0f, GU_PI/9.0f, 0};

			sceGumLoadIdentity();
			sceGumRotateXYZ(&rot);
		}

		for( q = 0 ; q < 4; ++q )
		{
			ScePspFVector3 rot = {0,0,GU_PI/2.0f};
			sceGumRotateXYZ(&rot);

			sceGumDrawArray(GU_TRIANGLES,
				GU_WEIGHTS( WEIGHTS_PER_VERTEX )|GU_NORMAL_32BITF|GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_WEIGHT_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,
				sizeof(cylinder_indices)/sizeof(unsigned short),cylinder_indices,cylinder_vertices);
		}

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

/* usefull geometry functions */
void genSkinnedCylinder( unsigned slices, unsigned rows, float length, float radius, unsigned bones,
	Vertex* dstVertices, unsigned short* dstIndices )
{
	unsigned int i,j;

	float lengthStep = length / (float)rows;
	float boneStep = ((float)bones-1)/((float)rows);

	// generate torus (TODO: tri-strips)
	for (j = 0; j < slices; ++j)
	{
		for (i = 0; i < rows; ++i)
		{
			struct Vertex* curr = &dstVertices[i+j*rows];
			float s = i + 0.5f;
			float t = j;
			float cs,ct,ss,st;

			cs = cosf(s * (2*GU_PI)/slices);
			ct = cosf(t * (2*GU_PI)/rows);
			ss = sinf(s * (2*GU_PI)/slices);
			st = sinf(t * (2*GU_PI)/rows);

			curr->nx = 0;
			curr->ny = ct;
			curr->nz = st;

			curr->x = lengthStep * (float)i;
			curr->y = radius * ct;
			curr->z = radius * st;

			curr->color = 0xffffff;

			int q = 0;
			for( ; q < bones; q++ )
			{
				float b = min( ((float)bones-1), boneStep * (float)i );
				float t = b - (float)q;

				// calculate cubic blending functions for skinning weights
				// each vertex is influenced by 4 bones (matrices) at most

				float t2 = t*t;
				float t3 = t*t*t;

				float f = 0;
				if( t >= 0.0f && t < 1.0f ) f =  t3/6.0f;
				if( t >= 1.0f && t < 2.0f )	f = -0.5f*t3 + 2.0f*t2 - 2.0f*t  +  2.0f/3.0f; 			
				if( t >= 2.0f && t < 3.0f )	f =  0.5f*t3 - 4.0f*t2 + 10.0f*t - 22.0f/3.0f;
				if( t >= 3.0f && t < 4.0f )	f = -t3/6.0f + 2.0f*t2 - 8.0f*t  + 32.0f/3.0f;

				curr->skinWeight[q] = f;
			}
		}
	}

	for (j = 0; j < slices; ++j)
	{
		for (i = 0; i < rows-1; ++i)
		{
			unsigned short* curr = &dstIndices[(i+(j*(rows-1)))*6];

			*curr++ = i + j * rows;
			*curr++ = (i+1) + j * rows;
			*curr++ = i + ((j+1)%slices) * rows;

			*curr++ = (i+1) + j * rows;
			*curr++ = (i+1) + ((j+1)%slices) * rows;
			*curr++ = i + ((j+1)%slices) * rows;
		}
	}
}
