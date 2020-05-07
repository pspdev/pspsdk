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
//#include <pspmoduleinfo.h>
#include <pspwlan.h>

/* Define the module info section */
PSP_MODULE_INFO("Wlan Sample", 0, 1, 0);

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
    thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);
    if (thid >= 0)
	sceKernelStartThread(thid, 0, 0);
    return thid;
}

/* main routine */
int main(int argc, char *argv[])
{
    u8 sVal[8];
    int retVal;
    
    //init screen and callbacks
    pspDebugScreenInit();
    pspDebugScreenClear();
    
    SetupCallbacks();

    memset(sVal, 0, 7);
    
    for(;;) {
    	sceDisplayWaitVblankStart();
    	pspDebugScreenSetXY(0, 0);
    	printf("Wlan Sample v1.0 by John_K\n\n"); 
    
    	printf("Wlan switch is %s\n", sceWlanGetSwitchState() == 0 ? "off":"on");
    	printf("Wlan power is %s\n", sceWlanDevIsPowerOn() == 0 ? "off":"on");
    	retVal = sceWlanGetEtherAddr(sVal);
    	if (retVal == 0)    	
    		printf("Wlan Ethernet Addr: %02X:%02X:%02X:%02X:%02X:%02X\n", sVal[0], sVal[1], sVal[2], sVal[3], sVal[4], sVal[5]);
    	else
    		printf("Error getting Wlan Ethernet Address (0x%08X)\n", retVal);
    }
    sceKernelSleepThread();
    sceKernelExitGame();

    return 0;
}
