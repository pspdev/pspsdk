/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Simple PRX example.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id: main.c 1531 2005-12-07 18:27:12Z tyranid $
 */
#include <pspkernel.h>
#include <stdio.h>

PSP_MODULE_INFO("TESTPRX", 0x1000, 1, 1);

#define WELCOME_MESSAGE "Hello from the PRX\n"

int main(int argc, char **argv)
{
	int i;
	
	printf(WELCOME_MESSAGE);

	for(i = 0; i < argc; i++)
	{
		printf("Arg %d: %s\n", i, argv[i]);
	}

	sceKernelSleepThread();

	return 0;
}

/* Exported function returns the address of module_info */
void* getModuleInfo(void)
{
	return (void *) &module_info;
}
