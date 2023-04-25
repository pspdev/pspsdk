/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Sample to demonstrate how to use savedata utility
 *
 * Copyright (c) 2005 weltall (weltall@consoleworld.org)
 *			 (c) 2007 InsertWittyName (tias_dp@hotmail.com)
 * Based on work by Shine
 *
 */
#include <pspkernel.h>
#include <pspdisplay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pspmoduleinfo.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <pspgum.h>
#include <psputility.h>
#include <pspctrl.h>

#include "data.h"

PSP_MODULE_INFO("Savedata Sample", 0, 1, 1);

#if defined(_PSP_FW_VERSION) && _PSP_FW_VERSION >= 200
PSP_HEAP_SIZE_KB(20480);
#endif

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

#define DATABUFFLEN   0x20

static int running = 1;

char string[128];

// Exit callback
int exit_callback(int arg1, int arg2, void *common)
{
    running = 0;
	
    return 0;
}

// Callback thread
int CallbackThread(SceSize args, void *argp)
{
    int cbid;
    cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();

    return 0;
}

// Sets up the callback thread and returns its thread id
int SetupCallbacks(void)
{
    int thid = 0;
    thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
    if (thid >= 0)
	sceKernelStartThread(thid, 0, 0);
    return thid;
}


// Graphics stuff, based on cube sample
static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
    float u, v;
    unsigned int color;
    float x, y, z;
};

struct Vertex __attribute__((aligned(16))) vertices[12*3] =
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

static void SetupGu()
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

static void DrawStuff(void)
{
    static int val = 0;

    sceGuStart(GU_DIRECT,list);

    // Clear screen    
    sceGuClearColor(0xff554433);
    sceGuClearDepth(0);
    sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
    
    // Setup matrices for cube    
    sceGumMatrixMode(GU_PROJECTION);
    sceGumLoadIdentity();
    sceGumPerspective(75.0f,16.0f/9.0f,0.5f,1000.0f);
    
    sceGumMatrixMode(GU_VIEW);
    sceGumLoadIdentity();
    
    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();
    {
		ScePspFVector3 pos = { 0, 0, -2.5f };
		ScePspFVector3 rot = { val * 0.79f * (M_PI/180.0f), val * 0.98f * (M_PI/180.0f), val * 1.32f * (M_PI/180.0f) };
		sceGumRotateXYZ(&rot);
		sceGumTranslate(&pos);
    }
    
    // Draw cube
    sceGuAmbientColor(0xffffffff);
    sceGumDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,12*3,0,vertices);
    
    sceGuFinish();
    sceGuSync(0,0);

    val ++;
}

PspUtilitySavedataListSaveNewData newData;

char *titleShow = "New Save";

char nameMultiple[][20] =	// End list with ""
{
 "0000",
 "0001",
 "0002",
 "0003",
 "0004",
 ""
};

char key[] = "QTAK319JQKJ952HA";	// Key to encrypt or decrypt savedata

void initSavedata(SceUtilitySavedataParam * savedata, int mode)
{
	memset(savedata, 0, sizeof(SceUtilitySavedataParam));
	savedata->base.size = sizeof(SceUtilitySavedataParam);

	savedata->base.language = PSP_SYSTEMPARAM_LANGUAGE_ENGLISH;
	savedata->base.buttonSwap = PSP_UTILITY_ACCEPT_CROSS;
	savedata->base.graphicsThread = 0x11;
	savedata->base.accessThread = 0x13;
	savedata->base.fontThread = 0x12;
	savedata->base.soundThread = 0x10;

	savedata->mode = mode;
	savedata->overwrite = 1;
	savedata->focus = PSP_UTILITY_SAVEDATA_FOCUS_LATEST; // Set initial focus to the newest file (for loading)

#if defined(_PSP_FW_VERSION) && _PSP_FW_VERSION >= 200
	strncpy(savedata->key, key, 16);
#endif

	strcpy(savedata->gameName, "DEMO11111");	// First part of the save name, game identifier name
	strcpy(savedata->saveName, "0000");	// Second part of the save name, save identifier name

	// List of multiple names
	savedata->saveNameList = nameMultiple;

	strcpy(savedata->fileName, "DATA.BIN");	// name of the data file

	// Allocate buffers used to store various parts of the save data
	savedata->dataBuf = malloc(DATABUFFLEN);
	savedata->dataBufSize = DATABUFFLEN;
	savedata->dataSize = DATABUFFLEN;

	// Set some data
	if (mode == PSP_UTILITY_SAVEDATA_LISTSAVE)
	{
	 memset(savedata->dataBuf, 0, DATABUFFLEN);
	 strcpy(savedata->dataBuf,"score: 10");

	strcpy(savedata->sfoParam.title,"Title");
	strcpy(savedata->sfoParam.savedataTitle,"Title 2");
	strcpy(savedata->sfoParam.detail,"Details");
	savedata->sfoParam.parentalLevel = 1;
	
	// No icon1
	savedata->icon1FileData.buf = NULL;
	savedata->icon1FileData.bufSize = 0;
	savedata->icon1FileData.size = 0;

	savedata->pic1FileData.buf = pic1;
	savedata->pic1FileData.bufSize = size_pic1;
	savedata->pic1FileData.size = size_pic1;

	savedata->icon0FileData.buf = icon0;
	savedata->icon0FileData.bufSize = size_icon0;
	savedata->icon0FileData.size = size_icon0;
	
	// No snd0
	savedata->snd0FileData.buf = NULL;
	savedata->snd0FileData.bufSize = 0;
	savedata->snd0FileData.size = 0;

	// Set title
	newData.title = titleShow;

	// Set new data
	savedata->newData = &newData;
	
	savedata->focus = PSP_UTILITY_SAVEDATA_FOCUS_FIRSTEMPTY; // If saving, set inital focus to the first empty slot
	}
}

static void ShowSaveDialog (int mode)
{
	SceUtilitySavedataParam dialog;
	
    initSavedata(&dialog, mode);
	
    sceUtilitySavedataInitStart(&dialog);

    while(running) {

	DrawStuff();

	switch(sceUtilitySavedataGetStatus()) {

	case PSP_UTILITY_DIALOG_VISIBLE :

	    sceUtilitySavedataUpdate(1);
	    break;

	case PSP_UTILITY_DIALOG_QUIT :

	    sceUtilitySavedataShutdownStart();
	    break;
	    
	case PSP_UTILITY_DIALOG_FINISHED :
		if(mode == PSP_UTILITY_SAVEDATA_LISTSAVE)
			sprintf(string, "Saved: score = 10");
		else
			sprintf(string, "Loaded: %s\n", (char*)dialog.dataBuf); // The actual data in the savedata file that was saved previously
			
	case PSP_UTILITY_DIALOG_NONE :
	    return;
	}

	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
    }
}

int main(int argc, char *argv[])
{
    SceCtrlData pad;
	
	SetupCallbacks();
    SetupGu();
	
	pspDebugScreenInit();
	
	int mode = 0;
	
	memset(string, 0, sizeof(string));
	
	while(running)
	{		
		pspDebugScreenSetXY(0, 0);
	
		pspDebugScreenPrintf("Press X to Save, O to Load\n");
		pspDebugScreenPrintf(string);
		
		sceCtrlReadBufferPositive(&pad, 1);
		
		if(pad.Buttons & PSP_CTRL_CROSS)
			mode = PSP_UTILITY_SAVEDATA_LISTSAVE;
		
		else if(pad.Buttons & PSP_CTRL_CIRCLE)
			mode = PSP_UTILITY_SAVEDATA_LISTLOAD;
		
		if(mode)
		{
			ShowSaveDialog(mode);
			pspDebugScreenInit();
			mode = 0;
		}
	}

    sceKernelExitGame();
	
    return 0;
}
