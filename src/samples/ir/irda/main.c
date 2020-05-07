/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - IrDA example
 *
 * Copyright (c) 2005 Frank Buss <fb@frank-buss.de> (aka Shine)
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspsircs.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("IRDA", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

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
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

int main(void)
{
	SceCtrlData pad;
	u32 buttonsold = 0;

	SetupCallbacks();
	pspDebugScreenInit();

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

	printf ("IrDA PSP-2-PSP Example by Shine\n");
        printf ("-------------------------------\n");
	printf ("This example can be used with two PSPs\n\n");
        printf ("Press CROSS, SQUARE, CIRCLE or TRIANGLE\n");
        printf ("and it will be displayed at the other PSP\n\n");

	int fd = sceIoOpen("irda0:", PSP_O_RDWR, 0);

	while (1) {
		// read pad and send it
		sceCtrlReadBufferPositive(&pad, 1);
		if (pad.Buttons != buttonsold) {
			unsigned char padHighbyte = pad.Buttons >> 8;
			sceIoWrite(fd, &padHighbyte, 1);
			buttonsold = pad.Buttons;
		}

		// check for pad info from other PSP
		unsigned char data;
		int len = sceIoRead(fd, &data, 1);
		int otherPad = data << 8;
		if (len == 1) {
			if (otherPad & PSP_CTRL_CIRCLE) printf ("CIRCLE pressed\n");
			if (otherPad & PSP_CTRL_CROSS) printf ("CROSS pressed\n");
			if (otherPad & PSP_CTRL_SQUARE) printf ("SQUARE pressed\n");
			if (otherPad & PSP_CTRL_TRIANGLE) printf ("TRIANGLE pressed\n");
		}
		
		sceDisplayWaitVblankStart(); 
	}

	return 0;
}
