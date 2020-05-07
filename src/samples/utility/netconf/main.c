/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Sample to demonstrate proper use of the systemparam functions
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <stdio.h>
#include <string.h>
#include <pspmoduleinfo.h>
#include <psputility.h>
#include <pspctrl.h>

/* Define the module info section */
PSP_MODULE_INFO("NetParam Sample", 0, 1, 00);

//Just to leave room for expansion
#define NUM_NETPARAMS 17

/* Define printf, just to make typing easier */
#define printf  pspDebugScreenPrintf

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
    if (thid >= 0)
	sceKernelStartThread(thid, 0, 0);
    return thid;
}

/* main routine */
int main(int argc, char *argv[])
{
    int i;
    int netConfIndex = 1;
    int numNetConfigs = 1;
    netData data;
    SceCtrlData pad;
    u32 oldButtons;
    
    //init screen and callbacks
    pspDebugScreenInit();
    pspDebugScreenClear();
    
    SetupCallbacks();
    
    // Setup Pad
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(0);
    sceCtrlReadBufferPositive(&pad, 1);
    oldButtons = pad.Buttons;
    
    // Determine # of net configs
    while (sceUtilityCheckNetParam(numNetConfigs) == 0) {
    	numNetConfigs++;
    }
    numNetConfigs--;
    
    for (;;) {
    	pspDebugScreenSetXY(0, 0);
    	printf("NetParam Sample v1.0 by John_K\n\n");
    	
    	printf("Net Configuration #%d:\n", netConfIndex);
    	for (i = 0; i <= NUM_NETPARAMS; i++) {
    		//clear netData
    		data.asUint = 0xBADF00D;
    		memset(&data.asString[4], 0, 124);
	    	printf("param %03d: ret(0x%08X) uint(%d) string(%s)\n", i, sceUtilityGetNetParam(netConfIndex, i, &data), data.asUint, data.asString);
    	}
    	printf("\nPress X to show details for next net configuration.\n");
    	sceDisplayWaitVblankStart();
   	while (oldButtons == pad.Buttons) {
		sceCtrlReadBufferPositive(&pad, 1);
		if(pad.Buttons & PSP_CTRL_SELECT)
    			sceKernelExitGame();
	}
	if (pad.Buttons & PSP_CTRL_CROSS) {
    		netConfIndex++;
    		if(netConfIndex > numNetConfigs)
    			netConfIndex = 1;
    	}
    	oldButtons = pad.Buttons;
    }

    sceKernelSleepThread();
    sceKernelExitGame();

    return 0;
}
