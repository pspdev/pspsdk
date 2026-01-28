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
#include <psptypes.h>
#include <pspmodulemgr.h>

/** @defgroup ModuleMgrKern Kernel Module Manager Library
	* This module contains the imports for the kernel's module management routines.
	*/

enum SceModuleMgrExecModes {
	MODULE_EXEC_CMD_LOAD,
	MODULE_EXEC_CMD_RELOCATE,
	MODULE_EXEC_CMD_START,
	MODULE_EXEC_CMD_STOP,
	MODULE_EXEC_CMD_UNLOAD,
};

/** 
 * Structure used internally for many `sceModuleManager` module functions.
 * 
 * Also seems to be passed to `sceKernelStartThread` eventually by those internal functions.
 * */
typedef struct {
	/** The Operation to start on. One of the `SceModuleMgrExecModes` modes. */
	u8 mode_start;
	/** The Operation to finish on. One of the `SceModuleMgrExecModes` modes. */
	u8 mode_finish;
	/** The module placement policy in memory. One of `PspSysMemBlockTypes`. */
	u8 position;
	u8 access;
	SceUID *result;
	SceUID *new_block_id;
	/** The module in memory. */
	SceModule *mod;
	/** The executable information of the module. */
	SceLoadCoreExecFileInfo *exec_info;
	/** The API type of the module. */
	u32 api_type;
	/** The file ID for module file. */
	SceUID fd;
	/** The module thread priority. */
	s32 thread_priority;
	/** The module thread attributes. */
	u32 thread_attr;
	/** The memory partition where the program of the module will be stored. */
	SceUID mpid_text;
	/** The memory partition where the data of the module will be stored. */
	SceUID mpid_data;
	SceUID thread_mpid_stack;
	SceSize stack_size;
	/** The module ID. */
	SceUID mod_id;
	SceUID caller_mod_id;
	SceSize mod_size;
	void *file_base;
	SceSize arg_size;
	void *argp;
	u32 unk1;
	u32 unk2;
	s32 *status;
	SceUID event_id;
	u32 unk3;
	u32 unk4;
	u32 unk5;
	SceUID extern_mem_block_id_kernel;
	SceUID extern_mem_block_partition_id;
	SceSize extern_mem_block_size;
	u32 unk6;
	void *block_gzip; 
	u32 unk7;
	char secure_install_id[SCE_SECURE_INSTALL_ID_LEN];
	SceUID extern_mem_block_id_user;
	u32 unk8;
	SceOff mem_block_offset;
} SceModuleMgrParam;

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup ModuleMgrKern Kernel Module Manager Library */
/**@{*/

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
 * @return The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
 */
SceUID sceKernelLoadModuleBuffer(void *buf, SceSize bufsize, int flags, SceKernelLMOption *option);

/**
 * Alias for `sceKernelLoadModuleForLoadExecForUser`
 *
 * @attention Needs to link to `pspmodulemgr_kernel` stub.
 */
SceUID sceKernelLoadModuleWithApitype2(int apitype, const char *path, int flags, SceKernelLMOption *option);

/**
 * Load a module from a buffer with the Boot Init BTCNF apitype (0x051).
 *
 * @param bufsize - Size (in bytes) of the buffer pointed to by buf.
 * @param buf - Pointer to a buffer containing the module to load.  The buffer must reside at an
 *              address that is a multiple to 64 bytes.
 * @param flags - Unused, always 0.
 * @param option - Pointer to an optional ::SceKernelLMOption structure.
 *
 * @returns The UID of the loaded module on success, otherwise one of ::PspKernelErrorCodes.
 *
 * @attention Needs to link to `pspmodulemgr_kernel` stub.
 */
SceUID sceKernelLoadModuleBufferBootInitBtcnf(int bufsize, void *buf, int flags, SceKernelLMOption *option);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif
