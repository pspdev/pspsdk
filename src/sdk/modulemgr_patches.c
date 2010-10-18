/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * modulemgr_patches.c - Patches for sceModuleManager libraries.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: modulemgr_patches.c 2166 2007-02-04 10:52:49Z tyranid $
 */

#include <psptypes.h>
#include <psploadcore.h>
#include <pspkerror.h>
#include <psputils.h>
#include <pspsdk.h>
#include <string.h>

#define MM_MODNAME "sceModuleManager"

#ifdef F_InstallNoDeviceCheckPatch

#define IOFILEMGR_LIBNAME "IoFileMgrForKernel"
#define IOCTL_NID 0x63632449
#define JR_RA_INSN 0x03e00008
#define MOVE_V0_0_INSN 0x00001021

/* Nullify sceModuleMangager's LoadDeviceCheck() (and related calls). */
int pspSdkInstallNoDeviceCheckPatch(void)
{
	SceModule *mm_module;
	SceLibraryStubTable *libstubtable;
	int found, i;

	mm_module = sceKernelFindModuleByName(MM_MODNAME);
	if (mm_module == NULL) {
		return SCE_KERNEL_ERROR_UNKNOWN_MODULE;
	}

	libstubtable = (SceLibraryStubTable *) mm_module->stub_top;
	found = 0;
	/* Find the stub entry table for IoFileMgrForKernel. */
	while ((u32) libstubtable < ((u32) mm_module->stub_top + mm_module->stub_size)) {
		if (strcmp(libstubtable->libname, IOFILEMGR_LIBNAME) == 0) {
			found = 1;
			break;
		}

		libstubtable = (SceLibraryStubTable *) ((u32) libstubtable + (libstubtable->len * 4));
	}

	if (!found) {
		return SCE_KERNEL_ERROR_LIBRARY_NOTFOUND;
	}

	/* Find the NID for sceIoIoctl, and it's offset within the function stub table. */
	for (i = 0; i < libstubtable->stubcount; i++) {
		if (libstubtable->nidtable[i] == IOCTL_NID) {
			/* Found it, so patch the stub to return 0 so that all device checks pass. */
			u32 *ioctl_stub = (u32 *) ((u32) libstubtable->stubtable + (i * 8));

			ioctl_stub[0] = JR_RA_INSN;
			ioctl_stub[1] = MOVE_V0_0_INSN;
			return 0;
		}
	} 

	/* We couldn't find the stub entry. */
	return SCE_KERNEL_ERROR_ERROR;
}
#endif /* F_InstallNoDeviceCheckPatch */

#ifdef F_InstallNoPlainModuleCheckPatch

#define LOAD_EXEC_PLAIN_CHECK 0x4000B000 /* mfc0 *, $22 */
#define LOAD_EXEC_PLAIN_PATCH 0x34000001 /* li   *, 1 */


extern u32 sceKernelProbeExecutableObject;
extern u32 sceKernelCheckPspConfig;

int pspSdkInstallNoPlainModuleCheckPatch(void)
{
    u32 *addr;
    int i;

    addr = (u32*) (0x80000000 | ((sceKernelProbeExecutableObject & 0x03FFFFFF) << 2));
    //printf("sceKernelProbeExecutableObject %p\n", addr);
    for(i = 0; i < 100; i++)
    {
        if((addr[i] & 0xFFE0FFFF) == LOAD_EXEC_PLAIN_CHECK)
        {
            //printf("Found instruction %p\n", &addr[i]);
            addr[i] = (LOAD_EXEC_PLAIN_PATCH | (addr[i] & ~0xFFE0FFFF));
        }
    }

    addr = (u32*) (0x80000000 | ((sceKernelCheckPspConfig & 0x03FFFFFF) << 2));
    //printf("sceCheckPspConfig %p\n", addr);
    for(i = 0; i < 100; i++)
    {
        if((addr[i] & 0xFFE0FFFF) == LOAD_EXEC_PLAIN_CHECK)
        {
            //printf("Found instruction %p\n", &addr[i]);
            addr[i] = (LOAD_EXEC_PLAIN_PATCH | (addr[i] & ~0xFFE0FFFF));
        }
    }

    sceKernelDcacheWritebackAll();

    return 0;
}
#endif /* F_InstallNoPlainModuleCheckPatch */

#ifdef F_InstallKernelLoadModulePatch

#define LOAD_MODULE_KERN_CHECK 0x001BDC02 /* srl $k1, 16 */
#define LOAD_MODULE_KERN_PATCH 0x0000d821 /* move $k1, $0 */

extern u32 sceKernelLoadModuleWithApitype;
void sceKernelIcacheInvalidateAll();

int pspSdkInstallKernelLoadModulePatch(void)
{
    u32 *addr;
    int i;

    addr = (u32*) (0x80000000 | ((sceKernelLoadModuleWithApitype & 0x03FFFFFF) << 2));
    for(i = 0; i < 100; i++)
    {
        if(addr[i] == LOAD_MODULE_KERN_CHECK)
        {
            addr[i] = LOAD_MODULE_KERN_PATCH;
        }
    }

	sceKernelDcacheWritebackInvalidateAll();
	sceKernelIcacheInvalidateAll();

    return 0;
}
#endif
