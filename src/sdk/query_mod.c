/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * query_mod.c - Replacement for some missing modulemgr functions for v1.0 units.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: query_mod.c 1148 2005-10-12 19:08:27Z tyranid $
 */

#include <pspkerneltypes.h>
#include <psploadcore.h>
#include <pspmodulemgr.h>
#include <pspmodulemgr_kernel.h>
#include <pspsdk.h>
#include <string.h>

int pspSdkGetModuleIdList(SceUID *readbuf, int readbufsize, int *idcount)
{
	sceKernelGetModuleList(readbufsize / sizeof(SceUID), readbuf);
	*idcount = sceKernelModuleCount();

	return *idcount;
}

int pspSdkQueryModuleInfoV1(SceUID uid, SceKernelModuleInfo *modinfo)
{
	SceModule *mod;

	mod = sceKernelFindModuleByUID(uid);
	if(mod != NULL)
	{
		memcpy(modinfo->name, mod->modname, sizeof(mod->modname) + 1);
		modinfo->attribute = mod->attribute;
		modinfo->version[0] = mod->version[0];
		modinfo->version[1] = mod->version[1];
		modinfo->nsegment = (unsigned char )mod->nsegment;
		modinfo->entry_addr = mod->entry_addr;
		modinfo->gp_value = mod->gp_value;
		modinfo->text_addr = mod->text_addr;
		modinfo->text_size = mod->text_size;
		modinfo->data_size = mod->data_size;
		modinfo->bss_size = mod->bss_size;
		memcpy(modinfo->segmentaddr, mod->segmentaddr, sizeof(unsigned int) * 4);
		memcpy(modinfo->segmentsize, mod->segmentsize, sizeof(unsigned int) * 4);
	}
	else
	{
		return -1;
	}

	return 0;
}
