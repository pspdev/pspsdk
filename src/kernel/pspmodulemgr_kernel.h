/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmodulemgr_kernel.h - Prototypes to manage modules.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

#ifndef __MODMGRKERNEL_H__
#define __MODMGRKERNEL_H__

#include <pspkerneltypes.h>
#include <pspmodulemgr.h>
#include <pspinit.h>

/** @defgroup ModuleMgrKern Kernel Module Manager Library
  * This module contains the imports for the kernel's module management routines.
  */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup ModuleMgrKern Kernel Module Manager Library */
/*@{*/

enum PSPLoadModuleApitype
{
	PSP_LOADMODULE_APITYPE_KERNEL = 0, /* ModuleMgrForKernel */
	PSP_LOADMODULE_APITYPE_USER = 0x10, /* ModuleMgrForUser */
	PSP_LOADMODULE_APITYPE_DNAS = 0x13,  
	PSP_LOADMODULE_APITYPE_VSH = 0x20, 
	PSP_LOADMODULE_APITYPE_DISC = 0x120,
	PSP_LOADMODULE_APITYPE_DISC_UPDATER = 0x121,
	PSP_LOADMODULE_APITYPE_DISC_DEBUG = 0x122,
	PSP_LOADMODULE_APITYPE_DISC_IMAGE = 0x123,
	PSP_LOADMODULE_APITYPE_USBWLAN = 0x130,
	PSP_LOADMODULE_APITYPE_USBWLAN_DEBUG = 0x131,
	PSP_LOADMODULE_APITYPE_MS1 = 0x140, 
	PSP_LOADMODULE_APITYPE_MS2 = 0x141, 
	PSP_LOADMODULE_APITYPE_MS3 = 0x142, 
	PSP_LOADMODULE_APITYPE_MS4 = 0x143,
	PSP_LOADMODULE_APITYPE_MS5 = 0x144,
	PSP_LOADMODULE_APITYPE_VSH_EXIT_VSH_KERNEL = 0x200,
	PSP_LOADMODULE_APITYPE_VSH_EXIT_GAME = 0x210, 
	PSP_LOADMODULE_APITYPE_VSH_EXIT_VSH_VSH = 0x220, 
	PSP_LOADMODULE_APITYPE_REBOOT_KERNEL = 0x300,
};

/**
  * Gets the current module list.
  * 
  * @param readbufsize - The size of the read buffer.
  * @param readbuf     - Pointer to a buffer to store the IDs
  *
  * @return < 0 on error.
  */
int sceKernelGetModuleList(int readbufsize, SceUID *readbuf);

/**
  * Get the number of loaded modules.
  *
  * @return The number of loaded modules.
  */
int sceKernelModuleCount(void);

/**
 * Load a module from a buffer
 *
 * @param buf - Pointer to a buffer containing the module to load.  The buffer must reside at an
 *              address that is a multiple to 64 bytes.
 * @param bufsize - Size (in bytes) of the buffer pointed to by buf.
 * @param flags - Unused, always 0.
 * @param option - Pointer to an optional ::SceKernelLMOption structure.
 *
 * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
 */
SceUID sceKernelLoadModuleBuffer(void *buf, SceSize bufsize, int flags, SceKernelLMOption *option);

/**
 * Load a module from a buffer in reboot
 *
 * @param bufsize - Size (in bytes) of the buffer pointed to by buf.
 * @param buf - Pointer to a buffer containing the module to load.  The buffer must reside at an
 *              address that is a multiple to 64 bytes.
 * @param flags - Unused, always 0.
 * @param option - Pointer to an optional ::SceKernelLMOption structure.
 *
 * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
 */
SceUID ModuleMgrForKernel_EF7A7F02(SceSize bufsize, void *buf, int flags, SceKernelLMOption *option);

/**
 * Load a module buffer for VSHUsbWlan (0x130)
 *
 * @param buf - Pointer to a buffer containing the module to load.  The buffer must reside at an
 *              address that is a multiple to 64 bytes.
 * @param flags - Unused, always 0.
 * @param option - Pointer to an optional ::SceKernelLMOption structure.
 *
 * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
 */
SceUID sceKernelLoadModuleBufferForLoadExecBufferVSHUsbWlan(void *buf, int flags, SceKernelLMOption *option);

/**
 * Load a module buffer for VSHUsbWlanDebug (0x131)
 *
 * @param buf - Pointer to a buffer containing the module to load.  The buffer must reside at an
 *              address that is a multiple to 64 bytes.
 * @param flags - Unused, always 0.
 * @param option - Pointer to an optional ::SceKernelLMOption structure.
 *
 * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
 */
SceUID sceKernelLoadModuleBufferForLoadExecBufferVSHUsbWlanDebug(void *buf, int flags, SceKernelLMOption *option);

/**
 * Load a module from a buffer for exit vsh kernel (0x200)
 *
 * @param buf - Pointer to a buffer containing the module to load.  The buffer must reside at an
 *              address that is a multiple to 64 bytes.
 * @param flags - Unused, always 0.
 * @param option - Pointer to an optional ::SceKernelLMOption structure.
 *
 * @param unk - Umknown
 * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
 */
SceUID sceKernelLoadModuleBufferForExitVSHKernel(void *buf, int flags, SceKernelLMOption *option, int unk);

/**
 * Load a module from a buffer for exit game (0x210)
 *
 * @param buf - Pointer to a buffer containing the module to load.  The buffer must reside at an
 *              address that is a multiple to 64 bytes.
 * @param flags - Unused, always 0.
 * @param option - Pointer to an optional ::SceKernelLMOption structure.
 *
 * @param unk - Umknown
 * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
 */
SceUID sceKernelLoadModuleBufferForExitGame(void *buf, int flags, SceKernelLMOption *option, int unk);


/**
 * Load a module from a buffer for exit vsh vsh (0x220)
 *
 * @param buf - Pointer to a buffer containing the module to load.  The buffer must reside at an
 *              address that is a multiple to 64 bytes.
 * @param flags - Unused, always 0.
 * @param option - Pointer to an optional ::SceKernelLMOption structure.
 *
 * @param unk - Umknown
 * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
 */
SceUID sceKernelLoadModuleBufferForExitVSHVSH(void *buf, int flags, SceKernelLMOption *option, int unk);

/**
 * Load a module from a buffer for  reboot kernel (0x300)
 *
 * @param buf - Pointer to a buffer containing the module to load.  The buffer must reside at an
 *              address that is a multiple to 64 bytes.
 * @param flags - Unused, always 0.
 * @param option - Pointer to an optional ::SceKernelLMOption structure.
 *
 * @param unk - Umknown
 * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
 */
SceUID sceKernelLoadModuleBufferForRebootKernel(void *buf, int flags, SceKernelLMOption *option, int unk);

/**
  * Load a module with the VSH apitype.
  * 
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID sceKernelLoadModuleVSH(const char *path, int flags, SceKernelLMOption *option);

/**
  * Load the executable of a disc (EBOOT.BIN) (0x120)
  * 
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID sceKernelLoadModuleForLoadExecVSHDisc(const char *path, int flags, SceKernelLMOption *option);

/**
  * Load the updater executable of a disc (UPDATE/EBOOT.BIN) (0x121)
  * 
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID sceKernelLoadModuleForLoadExecVSHDiscUpdater(const char *path, int flags, SceKernelLMOption *option);

/**
  * Load the executable of a disc for debug in a toolkit (EBOOT.BIN) (0x122)
  * 
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID sceKernelLoadModuleForLoadExecVSHDiscDebug(const char *path, int flags, SceKernelLMOption *option);

/**
  * Load the executable of a disc image (0x123)
  * 
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID ModuleMgrForKernel_1B91F6EC(const char *path, int flags, SceKernelLMOption *option);

/**
  * Load a PBP (used for updater pbp's) (0x140)
  * 
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID sceKernelLoadModuleForLoadExecVSHMs1(const char *path, int flags, SceKernelLMOption *option);

/**
  * Load a PBP (used for non updater pbp's) (0x141)
  * 
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID sceKernelLoadModuleForLoadExecVSHMs2(const char *path, int flags, SceKernelLMOption *option);

/**
  * Load a PBP (used in Ms3) (0x142)
  * 
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID sceKernelLoadModuleForLoadExecVSHMs3(const char *path, int flags, SceKernelLMOption *option);

/**
  * Load a PBP (used in Ms4 function to load psx games) (0x143)
  * 
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID sceKernelLoadModuleForLoadExecVSHMs4(const char *path, int flags, SceKernelLMOption *option);

/**
  * Load a PBP (used in Ms5) (0x144)
  * 
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID sceKernelLoadModuleForLoadExecVSHMs5(const char *path, int flags, SceKernelLMOption *option);

/**
  * Load a module in reboot
  * 
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID ModuleMgrForKernel_25E1F458(const char *path, int flags, SceKernelLMOption *option);

/**
  * Load a module with a specific apitype for loadexecforuser 
  * 
  * @param apìtype - The apitype
  * @param path - The path to the module to load.
  * @param flags - Unused, always 0 .
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
  */
SceUID sceKernelLoadModuleForLoadExecForUser(int apitype, const char *path, int flags, SceKernelLMOption *option);

/**
 * Stop and unload the current module with the specified exit status code
 *
 * @param exitcode - The exitcode for the module
 * @param argsize - Size (in bytes) of the arguments that will be passed to module_stop().
 * @param argp - Poitner to arguments that will be passed to module_stop().
 * @param status - Return value from module_stop().
 * @param option - Pointer to an optional ::SceKernelSMOption structure.
 *
 * @returns ??? on success, otherwise one of ::PspKernelErrorCodes.
 */
int	ModuleMgrForKernel_2BE4807D(int exitcode, SceSize argsize, void *argp, int *status, SceKernelSMOption *option);

#define sceKernelStopUnloadSelfModuleWithStatusKernel ModuleMgrForKernel_2BE4807D

#define sceKernelLoadModuleForLoadExecVSHDiscImage	ModuleMgrForKernel_1B91F6EC

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
