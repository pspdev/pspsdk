/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspstdio.h - Prototypes for the sceStdio library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: pspstdio.h 1095 2005-09-27 21:02:16Z jim $
 */
#ifndef __PSPSTDIO_H__
#define __PSPSTDIO_H__

#include <pspkerneltypes.h>

/** @defgroup Stdio Stdio Library 
 *  This module contains the imports for the kernel's stdio routines.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Stdio Stdio Library */
/*@{*/

/**
  * Function to get the current standard in file no
  * 
  * @return The stdin fileno
  */
SceUID sceKernelStdin(void);

/**
  * Function to get the current standard out file no
  * 
  * @return The stdout fileno
  */
SceUID sceKernelStdout(void);

/**
  * Function to get the current standard err file no
  * 
  * @return The stderr fileno
  */
SceUID sceKernelStderr(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
