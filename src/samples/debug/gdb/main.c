/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic sample to demonstrate installing an exception handler.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <stdio.h>

PSP_MODULE_INFO("EXTEST", 0x1000, 1, 1);
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

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
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

/* Initialise SIO and GDB */
__attribute__((constructor))
void loaderInit()
{
	pspDebugScreenInit();
	pspDebugScreenPrintf("Initialising serial port\n");
	pspKernelSetKernelPC();
	pspDebugSioSetBaud(38400);
	pspDebugSioInit();
	pspDebugGdbStubInit();
}

int main(void)
{
	SceCtrlData pad;

	pspDebugScreenPrintf("App Started\n");
	SetupCallbacks();

	/* Generate a breakpoint to trap into GDB */
	pspDebugBreakpoint();

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

	printf("Exception Sample\n\n");
	printf("You have two choices, press O for a bus error or X for a breakpoint\n\n");

	while(1)
	{
		sceCtrlReadBufferPositive(&pad, 1);
		if(pad.Buttons & PSP_CTRL_CIRCLE)
		{
			/* Cause a bus error */
			_sw(0, 0);
		}

		if(pad.Buttons & PSP_CTRL_CROSS)
		{
			/* Cause a break exception */
			asm(
				"break\r\n"
			  );
		}

		sceDisplayWaitVblankStart();
	}


	/* We will never end up here, hopefully */
	printf("End\n");

	sceKernelSleepThread();

	return 0;
}
