/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspaudio.h - Prototypes for the sceHprm library.
 *
 * Copyright (c) 2005 Adresd
 *
 * $Id: psphprm.h 1480 2005-11-25 16:10:18Z mrbrown $
 */
#ifndef __HPRM_H__
#define __HPRM_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Hprm Hprm Remote */

/** @addtogroup Hprm */

/*@{*/

/** Enumeration of the remote keys */
enum PspHprmKeys
{
	PSP_HPRM_PLAYPAUSE  = 0x1,
	PSP_HPRM_FORWARD    = 0x4,
	PSP_HPRM_BACK       = 0x8,
	PSP_HPRM_VOL_UP		= 0x10,
	PSP_HPRM_VOL_DOWN   = 0x20,
	PSP_HPRM_HOLD       = 0x80
};

/** 
  * Peek at the current being pressed on the remote.
  * 
  * @param key - Pointer to the u32 to receive the key bitmap, should be one or
  * more of ::PspHprmKeys
  *
  * @return < 0 on error
  */
int sceHprmPeekCurrentKey(u32 *key);

/**
  * Peek at the current latch data.
  *
  * @param latch - Pointer a to a 4 dword array to contain the latch data.
  *
  * @return < 0 on error.
  */
int sceHprmPeekLatch(u32 *latch);

/**
  * Read the current latch data.
  *
  * @param latch - Pointer a to a 4 dword array to contain the latch data.
  *
  * @return < 0 on error.
  */
int sceHprmReadLatch(u32 *latch);

/**
  * Determines whether the headphones are plugged in.
  *
  * @return 1 if the headphones are plugged in, else 0.
  */
int sceHprmIsHeadphoneExist(void);

/** 
  * Determines whether the remote is plugged in.
  *
  * @return 1 if the remote is plugged in, else 0.
  */
int sceHprmIsRemoteExist(void);

/** 
  * Determines whether the microphone is plugged in.
  *
  * @return 1 if the microphone is plugged in, else 0.
  */
int sceHprmIsMicrophoneExist(void);



/*@}*/

#ifdef __cplusplus
}
#endif

#endif
