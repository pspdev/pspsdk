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

PSP_MODULE_INFO("Spline Surface Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
	unsigned int color;
	ScePspFVector3 normal;
	ScePspFVector3 position;
};

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

#define GRID_WIDTH 18
#define GRID_HEIGHT 18

int parametersSH[8] = {0,2,2,2,2,2,2,2};

float hue2rgb(float m1, float m2, float h)
{
	h += h < 0.0f ? 1.0f : h > 1.0f ? -1.0f : 0.0f;

	if ((h*6.0f) < 1.0f)
		return m1 + (m2-m1) * h * 6.0f;

	if ((h*2.0f) < 1.0f)
		return m2;

	if ((h*3.0f) < 2.0f)
		return m1 + (m2-m1) * ((2.0f/3.0f)-h) * 6.0f;

	return m1;
}

unsigned int hsl2rgb(float h, float s, float l)
{
	float m1,m2;
	int r,g,b;

	m2 = l < 0.5f ? l * (s+1.0f) : (l+s) - (l*s);
	m1 = l*2.0f-m2;

	r = (int)(255.0f * hue2rgb(m1,m2,h+(1.0f/3.0f)));
	g = (int)(255.0f * hue2rgb(m1,m2,h));
	b = (int)(255.0f * hue2rgb(m1,m2,h-(1.0f/3.0f)));

	return (0xff << 24) | (b << 16) | (g << 8) | r;
}

void evalSH(float theta, float phi, const int* m, ScePspFVector3* p)
{
	float r = 0;

	r += powf(sinf(m[0]*phi),(float)m[1]);
	r += powf(cosf(m[2]*phi),(float)m[3]);
	r += powf(sinf(m[4]*theta),(float)m[5]);
	r += powf(cosf(m[6]*theta),(float)m[7]);

	p->x = r * sinf(phi) * cosf(theta);
	p->y = r * cosf(phi);
	p->z = r * sinf(phi) * sinf(theta);
}

struct Vertex vertices[GRID_WIDTH * GRID_HEIGHT];
unsigned short indices[GRID_WIDTH * GRID_HEIGHT * 6];

void indicesSH()
{
	unsigned short i,j;

	for (i = 0; i < GRID_WIDTH; ++i)
	{
		for (j = 0; j < GRID_HEIGHT; ++j)
		{
			unsigned short* curr = &indices[(j + (i * (GRID_HEIGHT))) * 6];
			unsigned short i1 = (i+1) % GRID_WIDTH;
			unsigned short j1 = (j+1) % GRID_HEIGHT;

			*curr++ = j + i * GRID_HEIGHT;
			*curr++ = j1 + i * GRID_HEIGHT;
			*curr++ = j + i1 * GRID_HEIGHT;

			*curr++ = j1 + i * GRID_HEIGHT;
			*curr++ = j1 + i1 * GRID_HEIGHT;
			*curr++ = j + i1 * GRID_HEIGHT;
		}
	}

	sceKernelDcacheWritebackAll();
}

void setupSH()
{
	struct Vertex* vtx = vertices;
	struct Vertex* currvtx = vtx;

	float du = (GU_PI*2) / GRID_WIDTH;
	float dh = 1.0f / GRID_WIDTH;

	unsigned int i,j;

	for (i = 0; i < GRID_WIDTH; ++i)
	{
		float u = i * du;

		for (j = 0; j < GRID_HEIGHT; ++j)
		{
			currvtx->color = hsl2rgb(i * dh, 1.0f, 0.5f);
			currvtx++;
		}
	}

}

void renderSH(const int* m)
{
	struct Vertex* vtx = vertices;
	struct Vertex* currvtx = vtx;

	float du = (GU_PI*2) / (GRID_WIDTH-1);
	float dv = GU_PI / (GRID_HEIGHT-1);

	unsigned int i,j;

	// position

	for (i = 0; i < GRID_WIDTH; ++i)
	{
		float u = fmod(i * du,GU_PI*2);

		for (j = 0; j < GRID_HEIGHT; ++j)
		{
			float v = (j * dv);

			evalSH(u,v,m,&(currvtx->position));
			currvtx++;
		}
	}

	// normal

	for (i = 0; i < GRID_WIDTH; ++i)
	{
		for (j = 0; j < GRID_HEIGHT; ++j)
		{
			ScePspFVector3 l1,l2;
			unsigned short* curr = &indices[(j + (i * (GRID_HEIGHT))) * 6];
			ScePspFVector3* normal = &vtx[curr[0]].normal;

			l1.x = vtx[curr[1]].position.x - vtx[curr[0]].position.x;
			l1.y = vtx[curr[1]].position.y - vtx[curr[0]].position.y;
			l1.z = vtx[curr[1]].position.z - vtx[curr[0]].position.z;

			l2.x = vtx[curr[2]].position.x - vtx[curr[0]].position.x;
			l2.y = vtx[curr[2]].position.y - vtx[curr[0]].position.y;
			l2.z = vtx[curr[2]].position.z - vtx[curr[0]].position.z;

			gumCrossProduct(normal,&l1,&l2);
			gumNormalize(normal);
		}
	}

	sceKernelDcacheWritebackAll();

	sceGumDrawSpline(GU_NORMAL_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF,
			GRID_HEIGHT,GRID_WIDTH,3,3,indices,vertices);
}

struct LightSettings
{
	ScePspFVector3 position;
	unsigned int diffuse;
	unsigned int specular;
} lsettings[3] =
{
	{{-1,-1,-1}, 0xffffffff, 0xffffffff},	// key
	{{1,0,-1}, 0xff202020, 0xff000000},	// fill
	{{0,-1,1}, 0xff808080, 0xff000000}	// back
};

int main(int argc, char* argv[])
{
	setupCallbacks();

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
//	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	setupSH();
	indicesSH();

	// run sample

	int val = 0;

	while(running())
	{
		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0x000000);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// light settings

		sceGuEnable(GU_LIGHTING);
		sceGuEnable(GU_LIGHT0);
		sceGuEnable(GU_LIGHT1);
		sceGuEnable(GU_LIGHT2);
		sceGuLightMode(1);
		{
			unsigned int i;

			for (i = 0; i < 3; ++i)
			{
				sceGuLight(i,GU_DIRECTIONAL,GU_DIFFUSE_AND_SPECULAR,&lsettings[i].position);
				sceGuLightColor(i,GU_DIFFUSE,lsettings[i].diffuse);
				sceGuLightColor(i,GU_SPECULAR,lsettings[i].specular);
				sceGuLightAtt(i,0.0f,1.0f,0.0f);
			}
			sceGuSpecular(12.0f);
			sceGuAmbient(0x000000);
		}

		// setup matrices

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f,16.0f/9.0f,0.5f,1000.0f);

		sceGumMatrixMode(GU_VIEW);
		{
			ScePspFVector3 pos = { 0, 0, -5.0f };

			sceGumLoadIdentity();
			sceGumTranslate(&pos);
		}

		sceGumMatrixMode(GU_MODEL);
		sceGumLoadIdentity();
		{
			ScePspFVector3 rot = { val * 0.79f * (GU_PI/180.0f), val * 0.98f * (GU_PI/180.0f), val * 1.32f * (GU_PI/180.0f) };
			sceGumRotateXYZ(&rot);
		}

		// setup texture

		sceGuAmbientColor(0xffffffff);

		// draw

		renderSH(parametersSH);

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

		val++;

		if ((val%600) == 0)
		{
			unsigned int i;
			for (i = 0; i < 8; ++i)
				parametersSH[i] = (int)((rand() / ((float)RAND_MAX)) * 6.0f);
		}
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
