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
