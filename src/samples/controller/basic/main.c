/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic Input demo -- reads from control pad and indicates button
 *          presses.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Donour Sizemore <donour@uchicago.edu>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#include <psptypes.h>

/* Define the module info section */
PSP_MODULE_INFO("CONTROLTEST", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int done = 0;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
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
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

int main(void)
{
	SceCtrlData pad;

	pspDebugScreenInit();
	SetupCallbacks();

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	while(!done){
		pspDebugScreenSetXY(0, 2);

		sceCtrlReadBufferPositive(&pad, 1);

		// 10 May 2025
		// ---
		// Depending on the configuration of the device the
		// sample is being ran on, it may support a second
		// analog stick. Known instances of this are:
		// 1. On a PSP GO system with a connected DualShock 3
		// 2. On a PS VITA system
		// 3. On the PPSSPP emulator if bound in configuration settings
		// 4. Through hardware or software modification (see https://github.com/operation-ditto)
		// Due to these instances we should also report the second
		// stick to the screen.
		pspDebugScreenPrintf("L Analog X = %3d \n", pad.Lx);
		pspDebugScreenPrintf("L Analog Y = %3d \n", pad.Ly);
		pspDebugScreenPrintf("R Analog X = %3d \n", pad.Rx);
		pspDebugScreenPrintf("R Analog Y = %3d \n", pad.Ry);

		if (pad.Buttons != 0){
			if (pad.Buttons & PSP_CTRL_SQUARE){
				pspDebugScreenPrintf("Square pressed \n");
			}
			if (pad.Buttons & PSP_CTRL_TRIANGLE){
				pspDebugScreenPrintf("Triangle pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_CIRCLE){
				pspDebugScreenPrintf("Cicle pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_CROSS){
				pspDebugScreenPrintf("Cross pressed \n");
			} 

			if (pad.Buttons & PSP_CTRL_UP){
				pspDebugScreenPrintf("Up pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_DOWN){
				pspDebugScreenPrintf("Down pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_LEFT){
				pspDebugScreenPrintf("Left pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_RIGHT){
				pspDebugScreenPrintf("Right pressed \n");
			}      

			if (pad.Buttons & PSP_CTRL_START){
				pspDebugScreenPrintf("Start pressed \n");
			}
			if (pad.Buttons & PSP_CTRL_SELECT){
				pspDebugScreenPrintf("Select pressed \n");
			}
			if (pad.Buttons & PSP_CTRL_LTRIGGER){
				pspDebugScreenPrintf("L-trigger pressed \n");
			}
			if (pad.Buttons & PSP_CTRL_RTRIGGER){
				pspDebugScreenPrintf("R-trigger pressed \n");
			}      
		}
	}

	sceKernelExitGame();
	return 0;
}
