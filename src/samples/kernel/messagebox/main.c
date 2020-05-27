/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Demonstrate use of kernel messageboxes.
 *
 * Copyright (c) 2005 Marcus Comstedt <marcus@mc.pp.se>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspthreadman.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("messagebox", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf


/* The messagebox */
static SceUID myMessagebox;

/* Structure for the messages */
typedef struct _MyMessage {
	SceKernelMsgPacket header; /* For internal use by the kernel */
	char text[8];             /* Anything we would like to have */
} MyMessage;

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

static int SubThread(SceSize args, void *argp)
{
	int error, numWaitThreads;
	SceKernelMbxInfo info;

	/* For simplicily, we statically allocate some messages */
	static MyMessage one   = { {0}, "One" };
	static MyMessage two   = { {0}, "Two" };
	static MyMessage three = { {0}, "Three" };

	sceKernelDelayThread(100000);
	printf("SUB: started\n");

	sceKernelDelayThread(1000000);

	/* Send a message */
	printf("SUB: Posting 1\n");
	sceKernelSendMbx(myMessagebox, &one.header);

	/* Send another message after some delay,
	   to demonstrate the timeout feature */
	sceKernelDelayThread(1000000);
	printf("SUB: Posting 2\n");
	sceKernelSendMbx(myMessagebox, &two.header);

	/* Again, send another message after some delay,
	   this time to demonstrate the polling feature */
	sceKernelDelayThread(1000000);
	printf("SUB: Posting 3\n");
	sceKernelSendMbx(myMessagebox, &three.header);

	/* Wait for the main task to start blocking again,
	   and then check the messagebox status */
	sceKernelDelayThread(1000000);
	printf("SUB: Checking messagebox status\n");
	info.size = sizeof(info);
	error = sceKernelReferMbxStatus(myMessagebox, &info);
	if(error < 0)
		printf("SUB: ERROR %08x\n", error);
	else
		printf("SUB: status ok, name=\"%s\", attr=%d, numWaitThreads=%d, "
		       "numMessages=%d, firstMessage=%p\n", info.name, info.attr,
		       info.numWaitThreads, info.numMessages, info.firstMessage);

	/* Finally, cancel the main tasks receive operation */
	printf("SUB: Cancelling receive\n");
	error = sceKernelCancelReceiveMbx(myMessagebox, &numWaitThreads);
	sceKernelDelayThread(100000);
	if(error < 0)
		printf("SUB: ERROR %08x\n", error);
	else
		printf("SUB: cancellation ok, %d threads were waiting\n", numWaitThreads);

	printf("SUB: Exiting\n");
	return 0;
}

int main(int argc, char *argv[])
{
	SceUID thid;
	int error;
	void *data;

	pspDebugScreenInit();
	if (argc > 0) {
		printf("Bootpath: %s\n", argv[0]);
	}
	SetupCallbacks();

	/* Create a messagebox */
	myMessagebox = sceKernelCreateMbx("pspSDK-testMBX", 0, 0);
	printf("MAIN: created messagebox %08x\n", myMessagebox);

	/* Create a task that will post in the messagebox */
	thid = sceKernelCreateThread("subthread", SubThread, 17, 8192, THREAD_ATTR_USER, 0);
	sceKernelStartThread(thid, 0, NULL);
	printf("MAIN: started task %08x\n", thid);

	/* Wait for a message */
	printf("MAIN: waiting for message\n");
	error = sceKernelReceiveMbx(myMessagebox, &data, NULL);
	if(error < 0)
		printf("MAIN: ERROR %08x\n", error);
	else
		printf("MAIN: got message: \"%s\"\n", ((MyMessage *)data)->text);

	/* Wait for a message with timeout */
	printf("MAIN: waiting with timeout (will fail the first couple of times)\n");
	for(;;) {
		SceUInt timeout = 300000; /* microseconds */
		error = sceKernelReceiveMbx(myMessagebox, &data, &timeout);
		if(error < 0)
			printf("MAIN: ERROR %08x\n", error);
		else {
			printf("MAIN: got message: \"%s\" (timeout remaining %d us)\n",
			       ((MyMessage *)data)->text, timeout);
			break;
		}
	}

	/* Poll for messages */
	printf("MAIN: polling for message (non-blocking)\n");
	for(;;) {
		error = sceKernelPollMbx(myMessagebox, &data);
		if(error < 0) {
			printf("MAIN: ERROR %08x\n", error);
			/* Sleep for a little while to give the message
			   a chance to arrive */
			sceKernelDelayThread(300000);			
		} else {
			printf("MAIN: got message: \"%s\"\n", ((MyMessage *)data)->text);
			break;
		}		
	}

	/* This call to sceKernelReceiveMbx() will be interrupted
	   by the sub task without a message being sent */
	printf("MAIN: waiting for a message that will not arrive\n");
	error = sceKernelReceiveMbx(myMessagebox, &data, NULL);
	if(error < 0)
		printf("MAIN: ERROR %08x\n", error);
	else
		printf("MAIN: got message: \"%s\"\n", ((MyMessage *)data)->text);	

	/* Prepare to shutdown */
	printf("MAIN: waiting for sub task to exit\n");
	sceKernelWaitThreadEnd(thid, NULL);
	printf("MAIN: sub task exited, deleting messagebox\n");
	error = sceKernelDeleteMbx(myMessagebox);
	if(error < 0)
		printf("MAIN: ERROR %08x\n", error);
	else
		printf("MAIN: all done\n");

	sceKernelSleepThread();

	return 0;
}
