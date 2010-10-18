/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psploadexec.h - Process load and exit related functions.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: psploadexec.h 835 2005-08-09 05:41:25Z tyranid $
 */

/* Note: Some of the structures, types, and definitions in this file were
   extrapolated from symbolic debugging information found in the Japanese
   version of Puzzle Bobble. */

#ifndef __LOADEXEC_H__
#define __LOADEXEC_H__

/** @defgroup LoadExec LoadExec Library */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup LoadExec */

/*@{*/

/**
 * Register callback
 *
 * @note By installing the exit callback the home button becomes active. However if sceKernelExitGame
 * is not called in the callback it is likely that the psp will just crash.
 *
 * @par Example:
 * @code
 * int exit_callback(void) { sceKernelExitGame(); }
 *
 * cbid = sceKernelCreateCallback("ExitCallback", exit_callback, NULL);
 * sceKernelRegisterExitCallback(cbid);
 * @endcode
 *
 * @param cbid Callback id
 * @return < 0 on error
 */
int sceKernelRegisterExitCallback(int cbid);

/**
 * Exit game and go back to the PSP browser.
 *
 * @note You need to be in a thread in order for this function to work
 *
 */
void sceKernelExitGame(void);

/** Structure to pass to loadexec */
struct SceKernelLoadExecParam {
	/** Size of the structure */
	SceSize     size;
	/** Size of the arg string */
	SceSize     args;
	/** Pointer to the arg string */
	void *  argp;
	/** Encryption key ? */
	const char *    key;
};

/** 
  * Execute a new game executable, limited when not running in kernel mode.
  * 
  * @param file - The file to execute.
  * @param param - Pointer to a ::SceKernelLoadExecParam structure, or NULL.
  *
  * @return < 0 on error, probably.
  *
  */
int sceKernelLoadExec(const char *file, struct SceKernelLoadExecParam *param);

#ifdef __cplusplus
}
#endif

/*@}*/

#endif
