/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmoduleexport.h - Definitions for the .rodata.sceResident section.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: pspmoduleexport.h 1095 2005-09-27 21:02:16Z jim $
 */

#ifndef PSP_MODEXPORT_H_
#define PSP_MODEXPORT_H_

/** Structure to hold a single export entry */
struct _PspLibraryEntry {
	const char *	name;
	unsigned short	version;
	unsigned short	attribute;
	unsigned char	entLen;
	unsigned char	varCount;
	unsigned short	funcCount;
	void *			entrytable;
}; 

#endif
