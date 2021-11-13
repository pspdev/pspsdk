/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic sample to demonstrate some fileio functionality.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Jim Paris <jim@jtan.com>
 *
 */
#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <psptypes.h>
#include <pspiofilemgr.h>

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/param.h>

PSP_MODULE_INFO("CwdTest", 0, 1, 1);

#define printf pspDebugScreenPrintf

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

void try(const char *dest)
{
	char buf[MAXPATHLEN];

	printf("%16s --> ", dest);
	if(chdir(dest) < 0) {
		printf("(chdir error)\n");
	} else {
		printf("%s\n", getcwd(buf, MAXPATHLEN) ?: "(getcwd error)");
	}
}

int main(void)
{
	char buf[MAXPATHLEN];
	pspDebugScreenInit();
	SetupCallbacks();

	printf("Working Directory Examples\n");
	printf("Initial dir: %s\n\n", getcwd(buf, MAXPATHLEN) ?: "(error)");

	printf("%16s --> %s\n", "chdir() attempt", "resulting getcwd()");
	printf("%16s --> %s\n", "---------------", "------------------");
	try("");		   /* empty string                */
	try("hello");		   /* nonexistent path            */
	try("..");		   /* parent dir                  */
	try("../SAVEDATA");	   /* parent dir and subdir       */
	try("../..");		   /* multiple parents            */
	try(".");		   /* current dir                 */
	try("./././//PSP");        /* current dirs, extra slashes */
	try("/PSP/./GAME");	   /* absolute with no drive      */
	try("/");                  /* root with no drive          */
	try("ms0:/PSP/GAME");      /* absolute with drive         */
	try("flash0:/");           /* different drive             */
	try("ms0:/PSP/../PSP/");   /* mixed                       */

	printf("\nAll done!\n");

	return 0;
}
