/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic sample to demonstrate the kprintf handler.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>

PSP_MODULE_INFO("KPTEST", 0x1000, 1, 1);
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(0);

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

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

int main(void)
{
	pspDebugScreenInit();
	SetupCallbacks();

	printf("Kprintf Example:\n\n");

	pspDebugInstallKprintfHandler(NULL);

	printf("Lets test a kernel function error report\n");
	pspDebugScreenSetTextColor(0xFF);
	/* Try and load a module, this should print an error to the screen */
	sceKernelLoadModule("test:/this/is/not/a/file.prx", 0, NULL);
	pspDebugScreenSetTextColor(0xFFFFFFFF);
	printf("\nLets call Kprintf directly\n");
	pspDebugScreenSetTextColor(0xFF);
	Kprintf("Hello from Kprintf\n");
	
	/* Let's bug out */
	sceKernelExitDeleteThread(0);

	return 0;
}
