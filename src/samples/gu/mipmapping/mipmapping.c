///TV
/*
 * PSP Software Development Kit - http://www.pspdev.org
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


PSP_MODULE_INFO("MIP Mapping Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

extern unsigned char mip0_start[];
extern unsigned char mip1_start[];
extern unsigned char mip2_start[];

struct Vertex{
	float u, v;
	float x,y,z;
};

//A plane
struct Vertex __attribute__((aligned(16))) vertices[2*3] =
{
	{0, 0, -1, 1, 0}, // 0
	{1, 0,  1, 1, 0}, // 4
	{1, 1,  1, -1, 0}, // 5

	{0, 0, -1, 1, 0}, // 0
	{1, 1,  1,-1, 0}, // 5
	{0, 1, -1,-1, 0}, // 1

};

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

int main(int argc, char* argv[])
{
	// setup GU
	void* fbp0 = (void*)(4 * 480 * 272);
	void* fbp1 = (void*)(4 * 480 * 272);
	void* zbp = (void*)(2 * 480 * 272);

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
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuShadeModel(GU_SMOOTH);
	sceGuDisable(GU_CULL_FACE);
	sceGuEnable(GU_TEXTURE_2D);
	//sceGuEnable(GU_CLIP_PLANES);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// run sample
	float pos_z = -2.5;
	int zoom = -1;
	while(1){
		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0xff554433);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// setup matrices for cube
		//Projection
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f,16.0f/9.0f,0.5,100);

		//camera view
		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();
		{
			ScePspFVector3 cpos = { 0, 0, 0};
			sceGumTranslate(&cpos);
		}
		
		//Model
		sceGumMatrixMode(GU_MODEL);
		sceGumLoadIdentity();
		{
			ScePspFVector3 pos = { 0, 0, pos_z};
			sceGumTranslate(&pos);
		}

		//Zomm plane in and out to see mip mapping
		if (pos_z > -2) zoom = -1;
		if (pos_z < -12) zoom = 1;
		if (zoom == -1) pos_z-= 0.02;
		if (zoom == 1) pos_z+= 0.02;

		// setup texture
		sceGuTexMode(GU_PSM_8888,2, 0, 0);
		sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA); 
		sceGuTexLevelMode(GU_TEXTURE_AUTO, 0);
		//Set your filters according to what you want
		sceGuTexFilter(GU_LINEAR_MIPMAP_LINEAR, GU_LINEAR);

		//Set three textures for MIP Mapping
		sceGuTexImage(0,128,128,128,mip0_start);
		sceGuTexImage(1,64,64,64,mip1_start);
		sceGuTexImage(2,32,32,32,mip2_start);
		
		sceGuColor(0xffffffff);
		sceGuAmbientColor(0xffffffff);
		sceGumDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D,2*3,0,vertices);

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}

