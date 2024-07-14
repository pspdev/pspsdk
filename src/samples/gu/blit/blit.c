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

#include <pspctrl.h>
#include <pspgu.h>
#include <psprtc.h>

#include "../common/callbacks.h"

PSP_MODULE_INFO("Blit Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

static unsigned short __attribute__((aligned(16))) pixels[BUF_WIDTH*SCR_HEIGHT];
static unsigned short __attribute__((aligned(16))) swizzled_pixels[BUF_WIDTH*SCR_HEIGHT];

struct Vertex
{
	unsigned short u, v;
	unsigned short color;
	short x, y, z;
};

void simpleBlit(int sx, int sy, int sw, int sh, int dx, int dy)
{
	// simple blit, this just copies A->B, with all the cache-misses that apply

	struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));

	vertices[0].u = sx; vertices[0].v = sy;
	vertices[0].color = 0;
	vertices[0].x = dx; vertices[0].y = dy; vertices[0].z = 0;

	vertices[1].u = sx+sw; vertices[1].v = sy+sh;
	vertices[1].color = 0;
	vertices[1].x = dx+sw; vertices[1].y = dy+sh; vertices[1].z = 0;

	sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_COLOR_4444|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
}

void advancedBlit(int sx, int sy, int sw, int sh, int dx, int dy, int slice)
{
	int start, end;

	// blit maximizing the use of the texture-cache

	for (start = sx, end = sx+sw; start < end; start += slice, dx += slice)
	{
		struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));
		int width = (start + slice) < end ? slice : end-start;

		vertices[0].u = start; vertices[0].v = sy;
		vertices[0].color = 0;
		vertices[0].x = dx; vertices[0].y = dy; vertices[0].z = 0;

		vertices[1].u = start + width; vertices[1].v = sy + sh;
		vertices[1].color = 0;
		vertices[1].x = dx + width; vertices[1].y = dy + sh; vertices[1].z = 0;

		sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_COLOR_4444|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
	}
}

void swizzle_fast(u8* out, const u8* in, unsigned int width, unsigned int height)
{
   unsigned int blockx, blocky;
   unsigned int j;
 
   unsigned int width_blocks = (width / 16);
   unsigned int height_blocks = (height / 8);
 
   unsigned int src_pitch = (width-16)/4;
   unsigned int src_row = width * 8;
 
   const u8* ysrc = in;
   u32* dst = (u32*)out;
 
   for (blocky = 0; blocky < height_blocks; ++blocky)
   {
      const u8* xsrc = ysrc;
      for (blockx = 0; blockx < width_blocks; ++blockx)
      {
         const u32* src = (u32*)xsrc;
         for (j = 0; j < 8; ++j)
         {
            *(dst++) = *(src++);
            *(dst++) = *(src++);
            *(dst++) = *(src++);
            *(dst++) = *(src++);
            src += src_pitch;
         }
         xsrc += 16;
     }
     ysrc += src_row;
   }
}

const char* modes[] =
{
	"normal, linear",
	"optimized, linear",
	"normal, swizzled",
	"optimized, swizzled"
};

int main(int argc, char* argv[])
{
	unsigned int x,y;

	pspDebugScreenInit();
	setupCallbacks();

	// Setup GU

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
	sceGuFrontFace(GU_CW);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(1);

	// generate dummy image to blit

	for (y = 0; y < SCR_HEIGHT; ++y)
	{
		unsigned short* row = &pixels[y * BUF_WIDTH];
		for (x = 0; x < SCR_WIDTH; ++x)
		{
			row[x] = x * y;
		}
	}

	swizzle_fast((u8*)swizzled_pixels,(const u8*)pixels,BUF_WIDTH*2,SCR_HEIGHT); // 512*2 because swizzle operates in bytes, and each pixel in a 16-bit texture is 2 bytes

	sceKernelDcacheWritebackAll();

	float curr_ms = 1.0f;
	int blit_method = 0;
	int swizzle = 0;
	SceCtrlData oldPad;
	oldPad.Buttons = 0;

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(0);

	u64 last_tick;
	sceRtcGetCurrentTick(&last_tick);
	u32 tick_frequency = sceRtcGetTickResolution();
	int frame_count = 0;

	while(running())
	{
		SceCtrlData pad;

		sceGuStart(GU_DIRECT,list);

		// switch methods if requested

		if(sceCtrlPeekBufferPositive(&pad, 1))
		{
			if (pad.Buttons != oldPad.Buttons)
			{
				if(pad.Buttons & PSP_CTRL_CROSS)
					blit_method ^= 1;
				if(pad.Buttons & PSP_CTRL_CIRCLE)
					swizzle ^= 1;
			}
			oldPad = pad;
		}

		sceGuTexMode(GU_PSM_4444,0,0,swizzle); // 16-bit RGBA
		sceGuTexImage(0,512,512,512,swizzle ? swizzled_pixels : pixels); // setup texture as a 512x512 texture, even though the buffer is only 512x272 (480 visible)
		sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA); // don't get influenced by any vertex colors
		sceGuTexFilter(GU_NEAREST,GU_NEAREST); // point-filtered sampling

		if (blit_method)
			advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);
		else
			simpleBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0);

		sceGuFinish();
		sceGuSync(0,0);

		float curr_fps = 1.0f / curr_ms;

		pspDebugScreenSetOffset((int)fbp0);
		pspDebugScreenSetXY(0,0);
		pspDebugScreenPrintf("fps: %d.%03d (%dMB/s) (X = mode, O = swizzle) %s",(int)curr_fps,(int)((curr_fps-(int)curr_fps) * 1000.0f),(((int)curr_fps * SCR_WIDTH * SCR_HEIGHT * 2)/(1024*1024)),modes[blit_method + swizzle * 2]);

//		sceDisplayWaitVblankStart();
		fbp0 = sceGuSwapBuffers();

		// simple frame rate counter

		++frame_count;
		u64 curr_tick;
		sceRtcGetCurrentTick(&curr_tick);
		if ((curr_tick-last_tick) >= tick_frequency)
		{
			float time_span = ((int)(curr_tick-last_tick)) / (float)tick_frequency;
			curr_ms = time_span / frame_count;

			frame_count = 0;
			sceRtcGetCurrentTick(&last_tick);
		}
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
