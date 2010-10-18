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

#include <pspctrl.h>
#include <pspgu.h>
#include <psprtc.h>

#include "../common/callbacks.h"
#include "../common/vram.h"

PSP_MODULE_INFO("Memory Speed Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define SLICE_SIZE 32 // change this to experiment with different page-cache sizes

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

static unsigned int __attribute__((aligned(16))) list[262144];

static u32 __attribute__((aligned(16))) pixels[BUF_WIDTH*SCR_HEIGHT];
static u32 __attribute__((aligned(16))) swizzled_pixels[BUF_WIDTH*SCR_HEIGHT];

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

struct StripWidthDeclaration
{
	int width;
	const char* name;
} strip_widths[] =
{
	{16,"16"},
	{32,"32"},
	{64,"64"},
	{128,"128"}
};

struct PixelFormatDeclaration
{
	int psm;
	int size;
	int row_pitch;
	const char* name;
} pixel_formats[] =
{
	{GU_PSM_4444,SCR_WIDTH*SCR_HEIGHT*2,1024,"16-bit RGBA"},
	{GU_PSM_T4,(SCR_WIDTH*SCR_HEIGHT)>>1,256,"4-bit CLUT"},
	{GU_PSM_T8,SCR_WIDTH*SCR_HEIGHT,512,"8-bit CLUT"},
	{GU_PSM_8888,SCR_WIDTH*SCR_HEIGHT*4,2048,"32-bit RGBA"}
};

u16 __attribute__((aligned(16))) palette[256];

int main(int argc, char* argv[])
{
	unsigned int i;

	setupCallbacks();

	for (i = 0; i < 256; ++i)
		palette[i] = i;

	sceKernelDcacheWritebackAll();

	// setup GU

	void* fbp0 = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	void* fbp1 = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	void* zbp = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_4444);

	pspDebugScreenInit();
	sceGuInit();

	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_5650,fbp0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,fbp1,BUF_WIDTH);
	sceGuDepthBuffer(zbp,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(65535,0);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuFrontFace(GU_CW);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuDepthMask(0xffff);
	sceGuDisable(GU_DEPTH_TEST);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

	sceGuClutMode(GU_PSM_4444,0,255,0);
	sceGuClutLoad(256/8,palette);

	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(1);

	// get vram buffer for vram -> vram blit

	void* vram_buffer;
	vram_buffer = getStaticVramTexture(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);

	// flush caches to make sure no stray data remains

	sceKernelDcacheWritebackAll();

	float curr_ms = 1.0f;
	int blit_method = 0;
	int swizzle = 0;
	int vram_select = 0;
	int strip_width = 0;
	int pixel_format = 0;
	int initialized = 0;

	SceCtrlData oldPad;
	oldPad.Buttons = 0;
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(0);

	u64 last_tick;
	sceRtcGetCurrentTick(&last_tick);
	u32 tick_res = sceRtcGetTickResolution();
	int frame_count = 0;

	while (running())
	{
		int texture_change = 0;

		// deal with input

		SceCtrlData pad;
		if(sceCtrlPeekBufferPositive(&pad, 1))
		{
			if (pad.Buttons != oldPad.Buttons)
			{
				if (pad.Buttons & PSP_CTRL_CROSS)
					blit_method ^= 1;

				if (pad.Buttons & PSP_CTRL_CIRCLE)
				{
					swizzle ^= 1;
					texture_change = 1;
				}

				if (pad.Buttons & PSP_CTRL_SQUARE)
				{
					vram_select ^= 1;
					texture_change = 1;
				}

				if (pad.Buttons & PSP_CTRL_TRIANGLE)
					strip_width = (strip_width+1) % (sizeof(strip_widths)/sizeof(struct StripWidthDeclaration));

				if (pad.Buttons & (PSP_CTRL_RTRIGGER|PSP_CTRL_LTRIGGER))
				{
					if (pad.Buttons & PSP_CTRL_RTRIGGER)
						++pixel_format;
					else
						--pixel_format;
					pixel_format %= sizeof(pixel_formats) / sizeof(struct PixelFormatDeclaration);
					texture_change = 1;
				}
			}
			oldPad = pad;
		}

		// generate new texture if settings have changed

		if (texture_change || !initialized)
		{
			u8* output = (u8*)pixels;
			unsigned int x,y;

			for (y = 0; y < 512; ++y)
				for (x = 0; x < pixel_formats[pixel_format].row_pitch; ++x)
					*output++ = x*y;

			if (swizzle)
			{
				if (vram_select)
					swizzle_fast((u8*)vram_buffer,(const u8*)pixels,pixel_formats[pixel_format].row_pitch,SCR_HEIGHT);
				else
					swizzle_fast((u8*)swizzled_pixels,(const u8*)pixels,pixel_formats[pixel_format].row_pitch,SCR_HEIGHT);
			}
			else
			{
				if (vram_select)
					memcpy(vram_buffer,pixels,pixel_formats[pixel_format].row_pitch * SCR_HEIGHT);
			}

			sceKernelDcacheWritebackAll();
			initialized = 1;
		}

		// begin rendering

		sceGuStart(GU_DIRECT,list);

		sceGuTexMode(pixel_formats[pixel_format].psm,0,0,swizzle); // 16-bit RGBA
		sceGuTexImage(0,512,512,512,vram_select ? vram_buffer : swizzle ? swizzled_pixels : pixels); // setup texture as a 512x512 texture, even though the buffer is only 512x272 (480 visible)
		sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA); // don't get influenced by any vertex colors
		sceGuTexFilter(GU_NEAREST,GU_NEAREST); // point-filtered sampling

		if (blit_method)
			advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0, strip_widths[strip_width].width);
		else
			simpleBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0);

		sceGuFinish();
		sceGuSync(0,0);

		// sum results and update report if more than one second has passed since last time

		++frame_count;

		u64 curr_tick;
		sceRtcGetCurrentTick(&curr_tick);
		if ((curr_tick-last_tick) >= tick_res)
		{
			float curr_fps = 1.0f / curr_ms;
			int transfer_rate = (curr_fps * pixel_formats[pixel_format].size) / (1024*1024);

			pspDebugScreenSetOffset((int)fbp0);
			pspDebugScreenSetXY(0,0);
			pspDebugScreenPrintf("fps: %d.%03d (%dMB/s)",(int)curr_fps,(int)((curr_fps-(int)curr_fps) * 1000.0f),transfer_rate);
			pspDebugScreenSetXY(0,1);
			pspDebugScreenPrintf("%s %s %s %s",blit_method ? "optimized" : "normal", swizzle ? "swizzled" : "linear",vram_select ? "video ram" : "system ram", strip_widths[strip_width].name);
			pspDebugScreenSetXY(0,2);
			pspDebugScreenPrintf("%s",pixel_formats[pixel_format].name);

			pspDebugScreenSetXY(0,32);
			pspDebugScreenPrintf("L/R = pixel format");
			pspDebugScreenSetXY(0,33);
			pspDebugScreenPrintf("X = blit method, O = swizzling, [] = memory, /\\ = strip width");

			fbp0 = sceGuSwapBuffers();

			// update timing for next pass

			double time_span = ((curr_tick-last_tick)) / (float)tick_res;
			curr_ms = time_span / frame_count;

			frame_count = 0;

			sceRtcGetCurrentTick(&last_tick);
		}

	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
