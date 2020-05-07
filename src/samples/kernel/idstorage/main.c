/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - idstorage sample, demonstrates the use of sceIdStorageLookup.
 *
 * Copyright (c) 2006 Harley G. <harleyg@0x89.org>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspidstorage.h>

/* Start in kernel mode */
PSP_MODULE_INFO("idstorage sample", 0x1000, 1, 0);
PSP_MAIN_THREAD_ATTR(0);
PSP_MAIN_THREAD_STACK_SIZE_KB(32);

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
	sceKernelExitGame();
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
	int cbid;
	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
	int thid = 0;
	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);
	if(thid >= 0) sceKernelStartThread(thid, 0, 0);
	return thid;
}

int main(void) {
	unsigned char buffer[0x1e]; /* Buffer */
	
	pspDebugScreenInit();
	SetupCallbacks();
	
	pspDebugScreenPrintf("Idstorage sample by harleyg\nThanks to Dark_AleX and Mathieulh\n\n");
	/* Read idstorage key 0x050 (serial) */
	sceIdStorageLookup(0x050, 0x0, buffer, 0x1e); /* key, offset, buffer, length */
	
	/* Print the serial */
	pspDebugScreenPrintf("Serial: %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
			      buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5],
			      buffer[6], buffer[7], buffer[8], buffer[9], buffer[10], buffer[11],
			      buffer[12], buffer[13], buffer[14], buffer[15], buffer[16], buffer[17],
			      buffer[18], buffer[19], buffer[20], buffer[21], buffer[22], buffer[23],
			      buffer[24], buffer[25], buffer[26], buffer[27], buffer[28], buffer[29]);
	
	sceKernelSleepThread();
	return 0;
}
