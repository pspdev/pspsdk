/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmodulemgr_kernel.h - Prototypes to manage modules.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: pspmodulemgr.h 792 2005-07-27 09:03:36Z warren $
 */

#ifndef __MODMGRKERNEL_H__
#define __MODMGRKERNEL_H__

#include <pspkerneltypes.h>
#include <pspmodulemgr.h>

/** @defgroup ModuleMgrKern Kernel Module Manager Library
  * This module contains the imports for the kernel's module management routines.
  */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup ModuleMgrKern Kernel Module Manager Library */
/*@{*/

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

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
