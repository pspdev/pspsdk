/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * VSYNC 30FPS Sample
 * With the sceKernelRegisterSubIntrHandler(PSP_VBLANK_INT, 0, on_vblank, NULL);,
 * the on_vblank function is going to be executed each PSP_VBLANK_INT interruption.
 * To force 30 FPS, we must ensure the VBLANK interruption happens exactly twice,
 * in order to achieve this, we have used 2 semaphores, so before swapping buffers,
 * we need to ensure that both semaphores are being signaled already, 
 * and this is what vsync30 method does.
 * 
 * How there are plenty of applications whose FPS are set to 30FPS,
 * this is just an example of how we could achieve this.
 *
 * Copyright (c) 2005 Jesper Svennevid
 * Copyright (c) 2025, Francisco Javier Trujillo Mata <fjtrujy@gmail.com>
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

PSP_MODULE_INFO("VSYNC 30FPS Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

static unsigned int __attribute__((aligned(16))) list[262144];
static unsigned int __attribute__((aligned(16))) pixels[512 * 272];

static int vsync_sema_1st_id;
static int vsync_sema_2nd_id;
static int vsync_sema_id = -1;

struct Vertex
{
	unsigned short u, v;
	unsigned short color;
	short x, y, z;
};

static void on_vblank(int sub, void *data)
{
	sceKernelSignalSema(vsync_sema_id ? vsync_sema_2nd_id : vsync_sema_1st_id, 1);
	vsync_sema_id ^= 1;
}

static void vsync30(void)
{
	sceKernelWaitSema(vsync_sema_1st_id, 1, NULL);
	sceKernelWaitSema(vsync_sema_2nd_id, 1, NULL);
}

static void prepare_sema(void)
{
	vsync_sema_1st_id = sceKernelCreateSema("vsync_sema_1st", 0, 0, 1, NULL);
	vsync_sema_2nd_id = sceKernelCreateSema("vsync_sema_2nd", 0, 0, 1, NULL);
}

int main(int argc, char *argv[])
{
	unsigned int x, y;

	setupCallbacks();

	// setup

	void *fbp0 = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, GU_PSM_8888);
	void *fbp1 = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, GU_PSM_8888);
	void *zbp = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, GU_PSM_4444);

	pspDebugScreenInit();
	sceGuInit();

	sceGuStart(GU_DIRECT, list);
	sceGuDrawBuffer(GU_PSM_8888, fbp0, BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, fbp1, BUF_WIDTH);
	sceGuDepthBuffer(zbp, BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH / 2), 2048 - (SCR_HEIGHT / 2));
	sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
	sceGuDepthRange(65535, 0);
	sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuFrontFace(GU_CW);
	sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
	sceGuFinish();
	sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

	prepare_sema();
	vsync_sema_id = 0;
	sceKernelRegisterSubIntrHandler(PSP_VBLANK_INT, 0, on_vblank, NULL);
	sceKernelEnableSubIntr(PSP_VBLANK_INT, 0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(1);

	int val = 0;

	// generate dummy image to blit

	for (y = 0; y < 272; ++y)
	{
		unsigned int *row = &pixels[y * 512];
		for (x = 0; x < 480; ++x)
		{
			row[x] = x * y;
		}
	}

	sceKernelDcacheWritebackAll();

	float curr_ms = 1.0f;
	struct timeval time_slices[16];

	void *framebuffer = 0;

	while (running())
	{
		sceGuStart(GU_DIRECT, list);

		// copy image from ram to vram

		sceGuCopyImage(GU_PSM_8888, 0, 0, 480, 272, 512, pixels, 0, 0, 512, (void *)(0x04000000 + (u32)framebuffer));
		sceGuTexSync();

		sceGuFinish();
		sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

		float curr_fps = 1.0f / curr_ms;

		vsync30();
		pspDebugScreenSetOffset((int)framebuffer);

		pspDebugScreenSetXY(0, 0);
		pspDebugScreenPrintf("%d.%03d FPS", (int)curr_fps, (int)((curr_fps - (int)curr_fps) * 1000.0f));

		framebuffer = sceGuSwapBuffers();
		// simple frame rate counter

		gettimeofday(&time_slices[val & 15], 0);

		val++;

		if (!(val & 15))
		{
			struct timeval last_time = time_slices[0];
			unsigned int i;

			curr_ms = 0;
			for (i = 1; i < 16; ++i)
			{
				struct timeval curr_time = time_slices[i];

				if (last_time.tv_usec > curr_time.tv_usec)
				{
					curr_time.tv_sec++;
					curr_time.tv_usec -= 1000000;
				}

				curr_ms += ((curr_time.tv_usec - last_time.tv_usec) + (curr_time.tv_sec - last_time.tv_sec) * 1000000) * (1.0f / 1000000.0f);

				last_time = time_slices[i];
			}
			curr_ms /= 15.0f;
		}
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}