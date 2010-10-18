/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * fixup.c - Code to manually fixup late binding modules
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 *
 * $Id: fixup.c 1888 2006-05-01 08:47:04Z tyranid $
 */

#include <pspkernel.h>
#include <string.h>

struct SceLibStubEntry{
	char *moduleName;
	unsigned short version;
	unsigned short attr;
	unsigned char structsz; // 0x5
	unsigned char numVars;
	unsigned short numFuncs;
	u32* nidList;
	u32* stubs;
} __attribute__((packed));

struct PspModuleExport
{
	const char* name;
	u32 flags;
	u8  unk;
	u8  v_count;
	u16 f_count;
	u32 *exports;
} __attribute__((packed));

extern SceModuleInfo module_info;

static void *pspSdkFindExport(SceModule *modInfo, const char *exportName, u32 nid) {
	void *pRet = NULL;
	struct PspModuleExport *export;
	if (modInfo == NULL)
		return NULL;

	export = modInfo->ent_top;

	while(export < (struct PspModuleExport *)(modInfo->ent_top+modInfo->ent_size))	{
		if (export->name != NULL && strcmp(exportName, export->name) == 0) {
			u32 *nidlist;
			int i;
			int t_count;

			t_count = export->f_count + export->v_count;
			nidlist = export->exports;

			for(i = 0; i < t_count; i++) {
				if(nidlist[i] == nid) {
					pRet = (void *) nidlist[i+t_count];
					break;
				}
			}
			break;
		}
		export++;
	}

	return pRet;
}

void pspSdkFixupImports(int modId)
{
	struct SceLibStubEntry* stubEntry = module_info.stub_top;
	int i;
	u32 *nid, *stub;
	void* addr;
	SceModule *modInfo;

	modInfo = sceKernelFindModuleByUID(modId);
	if (modInfo == NULL) {
		Kprintf("Could not find module with id 0x%08X\n", modId);
		return;
	}

	while (stubEntry < (struct SceLibStubEntry*)module_info.stub_end) {
		if (stubEntry->attr == 9) { //check to ensure this is a delayed import library
			/*Kprintf("Fixing up imports for '%s'...\n", stubEntry->moduleName);*/
			for (i = 0; i < stubEntry->numVars+stubEntry->numFuncs; i++) {
				stub = stubEntry->stubs;
				stub += i * 2; // since each stub is 8 bytes
				nid = stubEntry->nidList;
				nid += i;

				//get addr of NID from library
				addr = pspSdkFindExport(modInfo, stubEntry->moduleName, *nid);
				if (addr != NULL) {
					//fixup stub
					//Kprintf("addr is 0x%08X\n", addr);
					*stub = ((u32)addr & 0x03FFFFFF) >> 2 | 0x0A000000; //j addr
					stub += 1;
					*stub = 0; // nop
					/* Okay if we fix up at least one function set attribute to 1 */
					stubEntry->attr = 1;
				} 
			}
		} 

		stubEntry += 1;
	}
	//clear caches
	sceKernelDcacheWritebackAll();
	sceKernelIcacheClearAll();
}
