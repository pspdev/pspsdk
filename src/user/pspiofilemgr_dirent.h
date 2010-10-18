/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspiofilemgr_dirent.h - File attributes and directory entries.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: pspiofilemgr_dirent.h 1172 2005-10-20 09:08:04Z jim $
 */

/* Note: Some of the structures, types, and definitions in this file were
   extrapolated from symbolic debugging information found in the Japanese
   version of Puzzle Bobble. */

#ifndef PSPIOFILEMGR_DIRENT_H
#define PSPIOFILEMGR_DIRENT_H

#include <pspiofilemgr_stat.h>

/** Describes a single directory entry */
typedef struct SceIoDirent {
	/** File status. */
	SceIoStat 	d_stat;
	/** File name. */
	char 		d_name[256];
	/** Device-specific data. */
	void * 		d_private;
	int 		dummy;
} SceIoDirent;

#endif /* PSPIOFILEMGR_DIRENT_H */
