/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * shadowmap.c - Sample to demonstrate projective texture mapping
 *               used for shadowmap implementation
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


PSP_MODULE_INFO("Shadow Projection Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

static unsigned int __attribute__((aligned(16))) list[262144];

typedef struct Vertex_Normal
{
	float nx,ny,nz;
	float x,y,z;
} Vertex_Normal;

typedef struct Texture
{
	int format;
	int mipmap;
	int width, height, stride;
	const void* data;
} Texture;

/* grid */
#define GRID_COLUMNS 32
#define GRID_ROWS 32
#define GRID_SIZE 10.0f

Vertex_Normal __attribute__((aligned(16))) grid_vertices[GRID_COLUMNS*GRID_ROWS];
unsigned short __attribute__((aligned(16))) grid_indices[(GRID_COLUMNS-1)*(GRID_ROWS-1)*6];

/* torus */

#define TORUS_SLICES 48 // numc
#define TORUS_ROWS 48 // numt
#define TORUS_RADIUS 1.0f
#define TORUS_THICKNESS 0.5f

Vertex_Normal __attribute__((aligned(16))) torus_vertices[TORUS_SLICES*TORUS_ROWS];
unsigned short __attribute__((aligned(16))) torus_indices[TORUS_SLICES*TORUS_ROWS*6];

#define LIGHT_DISTANCE 3.0f


int SetupCallbacks();

void genGrid( unsigned rows, unsigned columns, float size,
	Vertex_Normal* dstVertices, unsigned short* dstIndices );
void genTorus( unsigned slices, unsigned rows, float radius, float thickness,
	Vertex_Normal* dstVertices, unsigned short* dstIndices );

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

typedef struct Geometry
{
	ScePspFMatrix4 world;
	unsigned int count;
	unsigned short* indices;
	Vertex_Normal* vertices;
	unsigned int color;
} Geometry;

void drawGeometry( Geometry* geom )
{
	sceGuSetMatrix(GU_MODEL,&geom->world);

	sceGuColor(geom->color);
	sceGuDrawArray(GU_TRIANGLES,GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,geom->count,geom->indices,geom->vertices);
}

void drawShadowCaster( Geometry* geom )
{
	sceGuSetMatrix(GU_MODEL,&geom->world);

	sceGuColor(0x00000000);
	sceGuDrawArray(GU_TRIANGLES,GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,geom->count,geom->indices,geom->vertices);
}

void drawShadowReceiver( Geometry* geom, ScePspFMatrix4 shadowProjMatrix )
{
	sceGuSetMatrix(GU_MODEL,&geom->world);

	// multiply shadowmap projection texture by geometry world matrix
	// since geometry coords are in object space

	gumMultMatrix(&shadowProjMatrix, &shadowProjMatrix, &geom->world );
	sceGuSetMatrix(GU_TEXTURE,&shadowProjMatrix);

	sceGuColor(geom->color);
	sceGuDrawArray(GU_TRIANGLES,GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,geom->count,geom->indices,geom->vertices);
}

int main(int argc, char* argv[])
{
	SetupCallbacks();

	// generate geometry

	genGrid( GRID_ROWS, GRID_COLUMNS, GRID_SIZE, grid_vertices, grid_indices );		
	genTorus( TORUS_ROWS, TORUS_SLICES, TORUS_RADIUS, TORUS_THICKNESS, torus_vertices, torus_indices );		

	// flush cache so that no stray data remains

	sceKernelDcacheWritebackAll();

	// setup VRAM buffers

	void* frameBuffer = (void*)0;
	const void* doubleBuffer = (void*)0x44000;
	const void* renderTarget = (void*)0x88000;
	const void* depthBuffer = (void*)0x110000;

	// setup GU

	sceGuInit();

	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_4444,frameBuffer,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,(void*)doubleBuffer,BUF_WIDTH);
	sceGuDepthBuffer((void*)depthBuffer,BUF_WIDTH);
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
	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_DITHER);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);


	// setup matrices

	ScePspFMatrix4 identity;
	ScePspFMatrix4 projection;
	ScePspFMatrix4 view;

	gumLoadIdentity(&identity);

	gumLoadIdentity(&projection);
	gumPerspective(&projection,75.0f,16.0f/9.0f,0.5f,1000.0f);

	{
		ScePspFVector3 pos = {0,0,-5.0f};

		gumLoadIdentity(&view);
		gumTranslate(&view,&pos);
	}

	ScePspFMatrix4 textureProjScaleTrans;
	gumLoadIdentity(&textureProjScaleTrans);
	textureProjScaleTrans.x.x = 0.5;
	textureProjScaleTrans.y.y = -0.5;
	textureProjScaleTrans.w.x = 0.5;
	textureProjScaleTrans.w.y = 0.5;

	ScePspFMatrix4 lightProjection;
	ScePspFMatrix4 lightProjectionInf;
	ScePspFMatrix4 lightView;
	ScePspFMatrix4 lightMatrix;

	gumLoadIdentity(&lightProjection);
	gumPerspective(&lightProjection,75.0f,1.0f,0.1f,1000.0f);
	gumLoadIdentity(&lightProjectionInf);
	gumPerspective(&lightProjectionInf,75.0f,1.0f,0.0f,1000.0f);

	gumLoadIdentity(&lightView);
	gumLoadIdentity(&lightMatrix);

	// define shadowmap

	Texture shadowmap = {
		GU_PSM_4444,
		0, 128, 128, 128,
		sceGeEdramGetAddr() + (int)renderTarget
	};

	// define geometry

	Geometry torus = {
		identity,
		sizeof(torus_indices)/sizeof(unsigned short),
		torus_indices,
		torus_vertices,
		0xffffff
	};
	Geometry grid = {
		identity,
		sizeof(grid_indices)/sizeof(unsigned short),
		grid_indices,
		grid_vertices,
		0xff7777
	};

	// run sample

	int val = 0;

	for(;;)
	{
		// update matrices

		// grid
		{
			ScePspFVector3 pos = {0,-1.5f,0};

			gumLoadIdentity(&grid.world);
			gumTranslate(&grid.world,&pos);
		}

		// torus
		{
			ScePspFVector3 pos = {0,0.5f,0.0f};
			ScePspFVector3 rot = {val * 0.79f * (GU_PI/180.0f), val * 0.98f * (GU_PI/180.0f), val * 1.32f * (GU_PI/180.0f)};

			gumLoadIdentity(&torus.world);
			gumTranslate(&torus.world,&pos);
			gumRotateXYZ(&torus.world,&rot);
		}

		// orbiting light
		{
			ScePspFVector3 lightLookAt = { torus.world.w.x, torus.world.w.y, torus.world.w.z };
			ScePspFVector3 rot1 = {0,val * 0.79f * (GU_PI/180.0f),0};
			ScePspFVector3 rot2 = {-(GU_PI/180.0f)*60.0f,0,0};
			ScePspFVector3 pos = {0,0,LIGHT_DISTANCE};

			gumLoadIdentity(&lightMatrix);
			gumTranslate(&lightMatrix,&lightLookAt);
			gumRotateXYZ(&lightMatrix,&rot1);
			gumRotateXYZ(&lightMatrix,&rot2);
			gumTranslate(&lightMatrix,&pos);
		}

		gumFastInverse(&lightView,&lightMatrix);

		// render to shadow map

		{
			sceGuStart(GU_DIRECT,list);

			// set offscreen texture as a render target

			sceGuDrawBufferList(GU_PSM_4444,(void*)renderTarget,shadowmap.stride);

			// setup viewport	

			sceGuOffset(2048 - (shadowmap.width/2),2048 - (shadowmap.height/2));
			sceGuViewport(2048,2048,shadowmap.width,shadowmap.height);

			// clear screen

			sceGuClearColor(0xffffffff);
			sceGuClearDepth(0);
			sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

			// setup view/projection from light

			sceGuSetMatrix(GU_PROJECTION,&lightProjection);
			sceGuSetMatrix(GU_VIEW,&lightView);

			// shadow casters are drawn in black
			// disable lighting and texturing

			sceGuDisable(GU_LIGHTING);
			sceGuDisable(GU_TEXTURE_2D);

			// draw torus to shadow map

			drawShadowCaster( &torus );

			sceGuFinish();
			sceGuSync(0,0);
		}

		// render to frame buffer

		{
			sceGuStart(GU_DIRECT,list);

			// set frame buffer

			sceGuDrawBufferList(GU_PSM_4444,(void*)frameBuffer,BUF_WIDTH);

			// setup viewport

			sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
			sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
			
			// clear screen

			sceGuClearColor(0xff554433);
			sceGuClearDepth(0);
			sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

			// setup view/projection from camera

			sceGuSetMatrix(GU_PROJECTION,&projection);
			sceGuSetMatrix(GU_VIEW,&view);
			sceGuSetMatrix(GU_MODEL,&identity);

			// setup a light
			ScePspFVector3 lightPos = { lightMatrix.w.x, lightMatrix.w.y, lightMatrix.w.z };
			ScePspFVector3 lightDir = { lightMatrix.z.x, lightMatrix.z.y, lightMatrix.z.z };

			sceGuLight(0,GU_SPOTLIGHT,GU_DIFFUSE,&lightPos);
			sceGuLightSpot(0,&lightDir, 5.0, 0.6);
			sceGuLightColor(0,GU_DIFFUSE,0x00ff4040);
			sceGuLightAtt(0,1.0f,0.0f,0.0f);
			sceGuAmbient(0x00202020);
			sceGuEnable(GU_LIGHTING);
			sceGuEnable(GU_LIGHT0);

			// draw torus

			drawGeometry( &torus );

			// setup texture projection

			sceGuTexMapMode( GU_TEXTURE_MATRIX, 0, 0 );
			sceGuTexProjMapMode( GU_POSITION );

			// set shadowmap as a texture

			sceGuTexMode(shadowmap.format,0,0,0);
			sceGuTexImage(shadowmap.mipmap,shadowmap.width,shadowmap.height,shadowmap.stride,shadowmap.data);
			sceGuTexFunc(GU_TFX_MODULATE,GU_TCC_RGB);
			sceGuTexFilter(GU_LINEAR,GU_LINEAR);
			sceGuTexWrap(GU_CLAMP,GU_CLAMP);
			sceGuEnable(GU_TEXTURE_2D);

			// calculate texture projection matrix for shadowmap
 
			ScePspFMatrix4 shadowProj;
			gumMultMatrix(&shadowProj, &lightProjectionInf, &lightView);
			gumMultMatrix(&shadowProj, &textureProjScaleTrans, &shadowProj);

			// draw grid receiving shadow

			drawShadowReceiver( &grid, shadowProj );

			sceGuFinish();
			sceGuSync(0,0);
		}

		sceDisplayWaitVblankStart();
		frameBuffer = sceGuSwapBuffers();

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
void genGrid( unsigned rows, unsigned columns, float size, Vertex_Normal* dstVertices, unsigned short* dstIndices )
{
	unsigned int i,j;

	// generate grid (TODO: tri-strips)
	for (j = 0; j < rows; ++j)
	{
		for (i = 0; i < columns; ++i)
		{
			Vertex_Normal* curr = &dstVertices[i+j*columns];

			curr->nx = 0.0f;
			curr->ny = 1.0f;
			curr->nz = 0.0f;

			curr->x = ((i * (1.0f/((float)columns)))-0.5f) * size;
			curr->y = 0;
			curr->z = ((j * (1.0f/((float)columns)))-0.5f) * size;
		}
	}

	for (j = 0; j < rows-1; ++j)
	{
		for (i = 0; i < columns-1; ++i)
		{
			unsigned short* curr = &dstIndices[(i+(j*(columns-1)))*6];

			*curr++ = i + j * columns;
			*curr++ = (i+1) + j * columns;
			*curr++ = i + (j+1) * columns;

			*curr++ = (i+1) + j * columns;
			*curr++ = (i+1) + (j+1) * columns;
			*curr++ = i + (j + 1) * columns;
		}
	}
}

void genTorus( unsigned slices, unsigned rows, float radius, float thickness, Vertex_Normal* dstVertices, unsigned short* dstIndices )
{
	unsigned int i,j;

	// generate torus (TODO: tri-strips)
	for (j = 0; j < slices; ++j)
	{
		for (i = 0; i < rows; ++i)
		{
			struct Vertex_Normal* curr = &dstVertices[i+j*rows];
			float s = i + 0.5f;
			float t = j;
			float cs,ct,ss,st;

			cs = cosf(s * (2*GU_PI)/slices);
			ct = cosf(t * (2*GU_PI)/rows);
			ss = sinf(s * (2*GU_PI)/slices);
			st = sinf(t * (2*GU_PI)/rows);

			curr->nx = cs * ct;
			curr->ny = cs * st;
			curr->nz = ss;

			curr->x = (radius + thickness * cs) * ct;
			curr->y = (radius + thickness * cs) * st;
			curr->z = thickness * ss;
		}
	}

	for (j = 0; j < slices; ++j)
	{
		for (i = 0; i < rows; ++i)
		{
			unsigned short* curr = &dstIndices[(i+(j*rows))*6];
			unsigned int i1 = (i+1)%rows, j1 = (j+1)%slices;

			*curr++ = i + j * rows;
			*curr++ = i1 + j * rows;
			*curr++ = i + j1 * rows;

			*curr++ = i1 + j * rows;
			*curr++ = i1 + j1 * rows;
			*curr++ = i + j1 * rows;
		}
	}
}
