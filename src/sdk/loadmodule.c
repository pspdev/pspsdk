/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * loadmodule.c - Routines to simplify module loading and unloading.
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 *
 * $Id: loadmodule.c 1737 2006-01-22 12:54:08Z tyranid $
 */

#include <string.h>
#include <stdio.h>
#include <pspuser.h>

#define MAX_ARGS 2048

SceUID pspSdkLoadStartModuleWithArgs(const char *filename, int mpid, int argc, char * const argv[])
{
	SceKernelLMOption option;
	SceUID modid = 0;
	int retVal = 0, mresult;
	char args[MAX_ARGS];
	int  argpos = 0;
	int  i;

	memset(args, 0, MAX_ARGS);
	strcpy(args, filename);
	argpos += strlen(args) + 1;
	for(i = 0; (i < argc) && (argpos < MAX_ARGS); i++)
	{
		int len;

		snprintf(&args[argpos], MAX_ARGS-argpos, "%s", argv[i]);
		len = strlen(&args[argpos]);
		argpos += len + 1;
	}

	memset(&option, 0, sizeof(option));
	option.size = sizeof(option);
	option.mpidtext = mpid;
	option.mpiddata = mpid;
	option.position = 0;
	option.access = 1;

	retVal = sceKernelLoadModule(filename, 0, &option);
	if(retVal < 0){
		return retVal;
	}

	modid = retVal;

	retVal = sceKernelStartModule(modid, argpos, args, &mresult, NULL);
	if(retVal < 0){
		return retVal;
	}

	return modid;
}

SceUID pspSdkLoadStartModule(const char *filename, int mpid)
{
	return pspSdkLoadStartModuleWithArgs(filename, mpid, 0, NULL);
}
