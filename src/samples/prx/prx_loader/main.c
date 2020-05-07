/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic harness for loading prxes (for proving a point)
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspsdk.h>
#include <string.h>

PSP_MODULE_INFO("PRXLOADER", 0x1000, 1, 1);
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(0);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

/* Exit callback */
int exit_callback(int arg1, int arg2, void *arg)
{
	sceKernelExitGame();

	return 0;
}

/* Callback thread */
void CallbackThread(void *arg)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", (void*) CallbackThread, 0x11, 0xFA0, 0xa0000000, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

SceUID load_module(const char *path, int flags, int type)
{
	SceKernelLMOption option;
	SceUID mpid;

	/* If the type is 0, then load the module in the kernel partition, otherwise load it
	   in the user partition. */
	if (type == 0) {
		mpid = 1;
	} else {
		mpid = 2;
	}

	memset(&option, 0, sizeof(option));
	option.size = sizeof(option);
	option.mpidtext = mpid;
	option.mpiddata = mpid;
	option.position = 0;
	option.access = 1;

	return sceKernelLoadModule(path, flags, type > 0 ? &option : NULL);
}

/* Imported function */
void *getModuleInfo(void);

int main(void)
{
	SceUID modid;
	SceModule *mod;
	int i;
	int ret;
	int fd;

	pspDebugScreenInit();

	/* Install all our funky err thingamybobs */
	pspDebugInstallKprintfHandler(NULL);
	pspDebugInstallErrorHandler(NULL);
	pspDebugInstallStdoutHandler(pspDebugScreenPrintData);
	pspSdkInstallNoPlainModuleCheckPatch();
	SetupCallbacks();

	/* Start mymodule.prx and dump its information */
	printf("\nStart my module\n");
	modid = load_module("ms0:/mymodule.prx", 0, 0);
	printf("Module ID %08X\n", modid);
	mod = sceKernelFindModuleByUID(modid);
	printf("mod %p\n", mod);
	if(mod != NULL)
	{
		printf("Attr %04X, Version %x.%x\n", mod->attribute, mod->version[0], mod->version[1]);
		printf("Name %s\n", mod->modname);
		printf("Text %08X, Size %08X, Data Size %08X\n", mod->text_addr, mod->text_size, mod->data_size);
		printf("Entry Addr %08X\n", mod->entry_addr);
		printf("Stub %p %08X, Ent %p %08X\n", mod->stub_top, mod->stub_size, mod->ent_top, mod->ent_size);
		for(i = 0; i < mod->nsegment; i++)
		{
			printf("Segment[%d] %08X %08X\n", i, mod->segmentaddr[i], mod->segmentsize[i]);
		}

		ret = sceKernelStartModule(modid, 0, NULL, &fd, NULL);

		/* Let's test the module's exports */
		printf("Module Info %p\n", getModuleInfo());
	}

	/* Let's bug out */
	sceKernelExitDeleteThread(0);

	return 0;
}
