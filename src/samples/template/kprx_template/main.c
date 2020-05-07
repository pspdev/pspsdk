/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic Kernel PRX template
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#include <pspkernel.h>
#include <stdio.h>

PSP_MODULE_INFO("template", PSP_MODULE_KERNEL, 1, 1);

int main_thread(SceSize args, void *argp)
{
	printf("Hello World\n");

	return 0;
}

/* Entry point */
int module_start(SceSize args, void *argp)
{
	int thid;

	thid = sceKernelCreateThread("template", main_thread, 7, 0x800, 0, NULL);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, args, argp);
	}
	return 0;
}

/* Module stop entry */
int module_stop(SceSize args, void *argp)
{
	return 0;
}
