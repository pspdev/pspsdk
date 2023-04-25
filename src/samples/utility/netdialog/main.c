/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Net dialog sample for connecting to an access point
 *
 * For OE firmwares, this sample must be run under the 3.xx kernel.
 *
 * Copyright (c) 2007 David Perry (Insert_Witty_Name)
 *
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <string.h>
#include <math.h>
#include <psputility.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspsdk.h>
#include <pspnet.h>
#include <pspnet_inet.h>
#include <pspnet_apctl.h>

#if defined(_PSP_FW_VERSION) && _PSP_FW_VERSION >= 200
PSP_MODULE_INFO("Net Dialog Sample", 0, 1, 1);
#else
PSP_MODULE_INFO("Net Dialog Sample", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(0);
#endif

static int running = 1;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	running = 0;
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
	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, PSP_THREAD_ATTR_USER, 0);

	if (thid >= 0)
		sceKernelStartThread(thid, 0, 0);

	return thid;
}

/* Graphics stuff, based on cube sample */
static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
	unsigned int color;
	float x,y,z;
};

struct Vertex __attribute__((aligned(16))) vertices[12*3] =
{
		{0xff7f0000,-1,-1, 1}, // 0
    	{0xff7f0000,-1, 1, 1}, // 4
    	{0xff7f0000, 1, 1, 1}, // 5

    	{0xff7f0000,-1,-1, 1}, // 0
    	{0xff7f0000, 1, 1, 1}, // 5
    	{0xff7f0000, 1,-1, 1}, // 1

    	{0xff7f0000,-1,-1,-1}, // 3
    	{0xff7f0000, 1,-1,-1}, // 2
    	{0xff7f0000, 1, 1,-1}, // 6

    	{0xff7f0000,-1,-1,-1}, // 3
    	{0xff7f0000, 1, 1,-1}, // 6
    	{0xff7f0000,-1, 1,-1}, // 7

    	{0xff007f00, 1,-1,-1}, // 0
    	{0xff007f00, 1,-1, 1}, // 3
    	{0xff007f00, 1, 1, 1}, // 7

    	{0xff007f00, 1,-1,-1}, // 0
    	{0xff007f00, 1, 1, 1}, // 7
    	{0xff007f00, 1, 1,-1}, // 4

    	{0xff007f00,-1,-1,-1}, // 0
    	{0xff007f00,-1, 1,-1}, // 3
    	{0xff007f00,-1, 1, 1}, // 7

    	{0xff007f00,-1,-1,-1}, // 0
    	{0xff007f00,-1, 1, 1}, // 7
    	{0xff007f00,-1,-1, 1}, // 4

    	{0xff00007f,-1, 1,-1}, // 0
    	{0xff00007f, 1, 1,-1}, // 1
    	{0xff00007f, 1, 1, 1}, // 2

    	{0xff00007f,-1, 1,-1}, // 0
    	{0xff00007f, 1, 1, 1}, // 2
    	{0xff00007f,-1, 1, 1}, // 3

    	{0xff00007f,-1,-1,-1}, // 4
    	{0xff00007f,-1,-1, 1}, // 7
    	{0xff00007f, 1,-1, 1}, // 6

    	{0xff00007f,-1,-1,-1}, // 4
    	{0xff00007f, 1,-1, 1}, // 6
    	{0xff00007f, 1,-1,-1}, // 5
};

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4)
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2)

static void setupGu()
{
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
    	sceGuEnable(GU_CLIP_PLANES);
    	sceGuFinish();
    	sceGuSync(0,0);

    	sceDisplayWaitVblankStart();
    	sceGuDisplay(GU_TRUE);
}

static void drawStuff(void)
{
	static int val = 0;

	sceGuStart(GU_DIRECT, list);

	sceGuClearColor(0xff554433);
	sceGuClearDepth(0);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	sceGumPerspective(75.0f,16.0f/9.0f,0.5f,1000.0f);
	   
	sceGumMatrixMode(GU_VIEW);
	sceGumLoadIdentity();
	
	sceGumMatrixMode(GU_MODEL);
	sceGumLoadIdentity();
	    
	ScePspFVector3 pos = { 0, 0, -5.0f };
	ScePspFVector3 rot = { val * 0.79f * (M_PI/180.0f), val * 0.98f * (M_PI/180.0f), val * 1.32f * (M_PI/180.0f) };
	sceGumTranslate(&pos);
	sceGumRotateXYZ(&rot);

	sceGumDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0, vertices);

	sceGuFinish();
	sceGuSync(0,0);
	
	val++;
}

int netDialog()
{
	int done = 0;

   	pspUtilityNetconfData data;

	memset(&data, 0, sizeof(data));
	data.base.size = sizeof(data);
	data.base.language = PSP_SYSTEMPARAM_LANGUAGE_ENGLISH;
	data.base.buttonSwap = PSP_UTILITY_ACCEPT_CROSS;
	data.base.graphicsThread = 17;
	data.base.accessThread = 19;
	data.base.fontThread = 18;
	data.base.soundThread = 16;
	data.action = PSP_NETCONF_ACTION_CONNECTAP;
	
	struct pspUtilityNetconfAdhoc adhocparam;
	memset(&adhocparam, 0, sizeof(adhocparam));
	data.adhocparam = &adhocparam;

	sceUtilityNetconfInitStart(&data);
	
	while(running)
	{
		drawStuff();

		switch(sceUtilityNetconfGetStatus())
		{
			case PSP_UTILITY_DIALOG_NONE:
				break;

			case PSP_UTILITY_DIALOG_VISIBLE:
				sceUtilityNetconfUpdate(1);
				break;

			case PSP_UTILITY_DIALOG_QUIT:
				sceUtilityNetconfShutdownStart();
				break;
				
			case PSP_UTILITY_DIALOG_FINISHED:
				done = 1;
				break;

			default:
				break;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
		
		if(done)
			break;
	}
	
	return 1;
}

void netInit(void)
{
	sceNetInit(128*1024, 42, 4*1024, 42, 4*1024);
	
	sceNetInetInit();
	
	sceNetApctlInit(0x8000, 48);
}

void netTerm(void)
{
	sceNetApctlTerm();
	
	sceNetInetTerm();
	
	sceNetTerm();
}

int user_thread(SceSize args, void *argp)
{
	netInit();
	
	SetupCallbacks();
	
	setupGu();

	netDialog();
	
	netTerm();
	
	return 0;
}

/* main routine */
int main(int argc, char *argv[])
{
	#if defined(_PSP_FW_VERSION) && _PSP_FW_VERSION >= 200
	sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);

	sceUtilityLoadNetModule(PSP_NET_MODULE_INET);
	
	netInit();
	
	SetupCallbacks();
	
	setupGu();

	netDialog();
	
	netTerm();

	#else

	pspSdkLoadInetModules();

	SceUID thid = sceKernelCreateThread("user_thread", user_thread, 0x18, 0x10000, PSP_THREAD_ATTR_USER, NULL);

	sceKernelStartThread(thid, 0, NULL);
	
	sceKernelWaitThreadEnd(thid, 0);
	#endif
	
	sceKernelExitGame();

	return 0;
}
