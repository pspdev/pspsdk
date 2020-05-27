/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Sample to demonstrate USB Mass Storage functionality
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * Derived from code written by PspPet
 * Code flow and API usage from VSH module "sysconf_plugin.prx"
 *
 */
#include <pspkernel.h>
#include <pspiofilemgr.h>
#include <pspmodulemgr.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspusb.h>
#include <pspusbstor.h>
#include <pspthreadman.h>
#include <pspctrl.h>
#include <pspsdk.h>

/**
 * Define the module info section
 *
 * 2nd arg must 0x1000 so __init is executed in
 * kernelmode for our loaderInit function
 */
PSP_MODULE_INFO("USBSample", 0x1000, 1, 0);

/**
 * THREAD_ATTR_USER causes the thread that the startup
 * code (ctr0.c) starts this program in to be in usermode
 * even though the module was started in kernelmode
 */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

/* Define printf, just to make typing easier */
#define printf  pspDebugScreenPrintf

//make this global so we can check it in the exit_callback
u32 state;

/**
 * Function that is called from _init in kernelmode before the
 * main thread is started in usermode.
 */
__attribute__ ((constructor))
void loaderInit()
{
    pspKernelSetKernelPC();
    pspSdkInstallNoDeviceCheckPatch();
    pspDebugInstallKprintfHandler(NULL);
}

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
    int retVal;

    //cleanup drivers
    if (state & PSP_USB_ACTIVATED) {
	retVal = sceUsbDeactivate(0);
	if (retVal != 0)
	    printf("Error calling sceUsbDeactivate (0x%08X)\n", retVal);
    }
    retVal = sceUsbStop(PSP_USBSTOR_DRIVERNAME, 0, 0);
    if (retVal != 0)
	printf("Error stopping USB Mass Storage driver (0x%08X)\n",
	       retVal);

    retVal = sceUsbStop(PSP_USBBUS_DRIVERNAME, 0, 0);
    if (retVal != 0)
	printf("Error stopping USB BUS driver (0x%08X)\n", retVal);

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

    thid = sceKernelCreateThread("update_thread", CallbackThread,
				 0x11, 0xFA0, 0, 0);
    if (thid >= 0) {
	sceKernelStartThread(thid, 0, 0);
    }

    return thid;
}

//helper function to make things easier
int LoadStartModule(char *path)
{
    u32 loadResult;
    u32 startResult;
    int status;

    loadResult = sceKernelLoadModule(path, 0, NULL);
    if (loadResult & 0x80000000)
	return -1;
    else
	startResult =
	    sceKernelStartModule(loadResult, 0, NULL, &status, NULL);

    if (loadResult != startResult)
	return -2;

    return 0;
}

int main(void)
{
    SceCtrlData pad;
    u32 oldButtons = 0;
    u32 retVal;

    state = 0;
    pspDebugScreenInit();
    pspDebugScreenClear();
    SetupCallbacks();

    //setup Pad
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(0);

    //print header now in case we have any errors
    printf("USB Sample v1.0 by John_K - Based off work by PSPPet\n");

    //start necessary drivers
    LoadStartModule("flash0:/kd/semawm.prx");
    LoadStartModule("flash0:/kd/usbstor.prx");
    LoadStartModule("flash0:/kd/usbstormgr.prx");
    LoadStartModule("flash0:/kd/usbstorms.prx");
    LoadStartModule("flash0:/kd/usbstorboot.prx");

    //setup USB drivers
    retVal = sceUsbStart(PSP_USBBUS_DRIVERNAME, 0, 0);
    if (retVal != 0) {
	printf("Error starting USB Bus driver (0x%08X)\n", retVal);
	sceKernelSleepThread();
    }
    retVal = sceUsbStart(PSP_USBSTOR_DRIVERNAME, 0, 0);
    if (retVal != 0) {
	printf("Error starting USB Mass Storage driver (0x%08X)\n",
	       retVal);
	sceKernelSleepThread();
    }
    retVal = sceUsbstorBootSetCapacity(0x800000);
    if (retVal != 0) {
	printf
	    ("Error setting capacity with USB Mass Storage driver (0x%08X)\n",
	     retVal);
	sceKernelSleepThread();
    }
    retVal = 0;

    //if everything worked we now enter our main loop
    for (;;) {

	sceCtrlReadBufferPositive(&pad, 1);
	state = sceUsbGetState();
	pspDebugScreenSetXY(0, 0);
	printf("USB Sample v1.0 by John_K - Based off work by PSPPet\n\n");
	printf("%-14s: %s\n", "USB Driver",
	       state & PSP_USB_ACTIVATED ? "activated     " :
	       "deactivated");
	printf("%-14s: %s\n", "USB Cable",
	       state & PSP_USB_CABLE_CONNECTED ? "connected    " :
	       "disconnected");
	printf("%-14s: %s\n", "USB Connection",
	       state & PSP_USB_CONNECTION_ESTABLISHED ? "established" :
	       "not present");
	printf("\nPress X to establish or destroy the USB connection\n");

	if (oldButtons != pad.Buttons) {
	    if (pad.Buttons & PSP_CTRL_CROSS) {
		if (state & PSP_USB_ACTIVATED)
		    retVal = sceUsbDeactivate(0x1c8);
		else
		    retVal = sceUsbActivate(0x1c8);
	    }
	}
	oldButtons = pad.Buttons;
	sceDisplayWaitVblankStart();
    }


    //Exit program
    sceKernelExitGame();

    return 0;
}
