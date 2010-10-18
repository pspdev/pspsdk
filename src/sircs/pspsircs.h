/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmodulemgr.h - Prototypes to manage manage modules.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Matthew H <matthewh@webone.com.au>
 *
 * $$
 */
#ifndef __SIRCS_H__
#define __SIRCS_H__

/** @defgroup Sony Integrated Remote Control System Library
  * This module contains the imports for the kernel's remote control routines.
  */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Sony Integrated Remote Control System Library */
/*@{*/

struct sircs_data {
	u8 type; // 12, 15 or 20 bits
	u8 cmd;  // 7 bit cmd
	u16 dev; // 5, 8 or 13 bit device address
} __packed__;

/**
  */
int sceSircsSend(struct sircs_data* sd, int count); 

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
