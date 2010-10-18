/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspiofilemgr_fcntl.h - File control definitions.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: pspiofilemgr_fcntl.h 559 2005-07-09 08:47:52Z mrbrown $
 */
#ifndef PSPIOFILEMGR_FCNTL_H
#define PSPIOFILEMGR_FCNTL_H

/* Note: Not all of these sceIoOpen() flags are not compatible with the
   open() flags found in sys/unistd.h. */
#define PSP_O_RDONLY	0x0001
#define PSP_O_WRONLY	0x0002
#define PSP_O_RDWR	(PSP_O_RDONLY | PSP_O_WRONLY)
#define PSP_O_NBLOCK	0x0004
#define PSP_O_DIROPEN	0x0008	// Internal use for dopen
#define PSP_O_APPEND	0x0100
#define PSP_O_CREAT	0x0200
#define PSP_O_TRUNC	0x0400
#define	PSP_O_EXCL	0x0800
#define PSP_O_NOWAIT	0x8000

#define PSP_SEEK_SET	0
#define PSP_SEEK_CUR	1
#define PSP_SEEK_END	2

#endif /* PSPIOFILEMGR_FCNTL_H */
