/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Display information about active program threads.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("threadstatus", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

void dump_threadstatus(void);

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

	printf("\nCallback Thread Status:\n");
	dump_threadstatus();
	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}

/* Dump the current thread's status */
void dump_threadstatus(void)
{
	int thid;
	SceKernelThreadInfo status;
	int ret;

	thid = sceKernelGetThreadId();
	memset(&status, 0, sizeof(SceKernelThreadInfo));
	printf("Thread ID: %08X\n", thid);
	status.size = sizeof(SceKernelThreadInfo);
	ret = sceKernelReferThreadStatus(thid, &status); 
	printf("Get Thread Status: %08X\n", ret);
	if(ret == 0)
	{
		printf("Name: %s\n", status.name);
		printf("Thread Addr: %p\n", status.entry);
		printf("Stack Addr: %p\n", status.stack);
		printf("Stack Size: %08X\n", status.stackSize);
		printf("gp: %p\n", status.gpReg);
		printf("Initial Pri: %x\n", status.initPriority);
		printf("Current Pri: %x\n", status.currentPriority);
	}
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

int main(int argc, char *argv[])
{
	pspDebugScreenInit();
	if (argc > 0) {
		printf("Bootpath: %s\n", argv[0]);
	}
	SetupCallbacks();
	printf("\nMain Thread Status:\n");
	dump_threadstatus();
	sceKernelSleepThread();

	return 0;
}
