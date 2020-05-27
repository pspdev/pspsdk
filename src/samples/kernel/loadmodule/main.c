/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - sceKernelLoadModule() sample.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

/* WARNING: This sample currently crashes, due to a bug in the PSP's kernel.  We're working on a fix. */

#include <pspuser.h>
#include <pspdebug.h>
#include <pspsdk.h>
#include <string.h>

/* Define the module info section, note the 0x1000 flag to enable start in kernel mode */
PSP_MODULE_INFO("SDKTEST", 0x1000, 1, 1);

PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

/* List of modules to load - type is 0 if the module belongs to the kernel, 1 if it's a user module. */
struct module_list {
	int			type;
	const char *path;
} module_list[] = {
	{ 0, "flash0:/kd/ifhandle.prx" },
	{ 1, "flash0:/kd/pspnet.prx" }
};
const int module_count = sizeof(module_list) / sizeof(module_list[0]);

SceUID load_module(const char *path, int flags, int type);


void MyExceptionHandler(PspDebugRegBlock *regs)
{
	printf("\n\n");
	pspDebugDumpException(regs);
}

/* This function is called by the startup code before main() is called.  Since
   it runs in kernel mode we can access kernel-only features. */
__attribute__((constructor))
void KernelSetup(void)
{
	pspDebugScreenInit();
	pspDebugInstallKprintfHandler(NULL);
	pspDebugInstallErrorHandler(MyExceptionHandler);

	/* Very important - patch the module manager so that we can load modules from user mode. */
	pspSdkInstallNoDeviceCheckPatch();
}

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

	/* Note the use of THREAD_ATTR_USER to ensure the callback thread is in user mode */
	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, PSP_THREAD_ATTR_USER, NULL);
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

	return sceKernelLoadModule(path, flags, &option);
}

int main(void)
{
	int i;

	SetupCallbacks();

	printf("Loadmodule sample program.\n\n");

	/* Try loading and starting the network modules. */
	for (i = 0; i < module_count; i++) {
		SceUID modid;
		int res, status;

		modid = load_module(module_list[i].path, 0, module_list[i].type);
		if (modid < 0) {
			printf("sceKernelLoadModule('%s') failed with %x\n", module_list[i].path, modid);
			break;
		}

		res = sceKernelStartModule(modid, 0, NULL, &status, NULL);
		if (res < 0) {
			printf("sceKernelStartModule('%s') failed with %x\n", module_list[i].path, res);
			break;
		}

		printf("Load and start '%s' - Success\n", module_list[i].path);
	}

	printf("\nAll done!\n");

	sceKernelSleepThread();
	return 0;
}
