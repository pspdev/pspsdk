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
 * $Id: pspiofilemgr_stat.h 1095 2005-09-27 21:02:16Z jim $
 */

/* Note: Some of the structures, types, and definitions in this file were
   extrapolated from symbolic debugging information found in the Japanese
   version of Puzzle Bobble. */

#ifndef PSPIOFILEMGR_STAT_H
#define PSPIOFILEMGR_STAT_H

#include <psptypes.h>
#include <pspkerneltypes.h>

/** Access modes for st_mode in SceIoStat (confirm?). */
enum IOAccessModes
{
	/** Format bits mask */
	FIO_S_IFMT		= 0xF000,
	/** Symbolic link */
	FIO_S_IFLNK		= 0x4000,
	/** Directory */
	FIO_S_IFDIR		= 0x1000,
	/** Regular file */
	FIO_S_IFREG		= 0x2000,

	/** Set UID */
	FIO_S_ISUID		= 0x0800,
	/** Set GID */
	FIO_S_ISGID		= 0x0400,
	/** Sticky */
	FIO_S_ISVTX		= 0x0200,

	/** User access rights mask */
	FIO_S_IRWXU		= 0x01C0,	
	/** Read user permission */
	FIO_S_IRUSR		= 0x0100,
	/** Write user permission */
	FIO_S_IWUSR		= 0x0080,
	/** Execute user permission */
	FIO_S_IXUSR		= 0x0040,	

	/** Group access rights mask */
	FIO_S_IRWXG		= 0x0038,	
	/** Group read permission */
	FIO_S_IRGRP		= 0x0020,
	/** Group write permission */
	FIO_S_IWGRP		= 0x0010,
	/** Group execute permission */
	FIO_S_IXGRP		= 0x0008,

	/** Others access rights mask */
	FIO_S_IRWXO		= 0x0007,	
	/** Others read permission */
	FIO_S_IROTH		= 0x0004,	
	/** Others write permission */
	FIO_S_IWOTH		= 0x0002,	
	/** Others execute permission */
	FIO_S_IXOTH		= 0x0001,	
};

// File mode checking macros
#define FIO_S_ISLNK(m)	(((m) & FIO_S_IFMT) == FIO_S_IFLNK)
#define FIO_S_ISREG(m)	(((m) & FIO_S_IFMT) == FIO_S_IFREG)
#define FIO_S_ISDIR(m)	(((m) & FIO_S_IFMT) == FIO_S_IFDIR)

/** File modes, used for the st_attr parameter in SceIoStat (confirm?). */
enum IOFileModes
{
	/** Format mask */
	FIO_SO_IFMT			= 0x0038,		// Format mask
	/** Symlink */
	FIO_SO_IFLNK		= 0x0008,		// Symbolic link
	/** Directory */
	FIO_SO_IFDIR		= 0x0010,		// Directory
	/** Regular file */
	FIO_SO_IFREG		= 0x0020,		// Regular file

	/** Hidden read permission */
	FIO_SO_IROTH		= 0x0004,		// read
	/** Hidden write permission */
	FIO_SO_IWOTH		= 0x0002,		// write
	/** Hidden execute permission */
	FIO_SO_IXOTH		= 0x0001,		// execute
};

// File mode checking macros
#define FIO_SO_ISLNK(m)	(((m) & FIO_SO_IFMT) == FIO_SO_IFLNK)
#define FIO_SO_ISREG(m)	(((m) & FIO_SO_IFMT) == FIO_SO_IFREG)
#define FIO_SO_ISDIR(m)	(((m) & FIO_SO_IFMT) == FIO_SO_IFDIR)

/** Structure to hold the status information about a file */
typedef struct SceIoStat {
	SceMode 		st_mode;
	unsigned int 	st_attr;
	/** Size of the file in bytes. */
	SceOff 			st_size;
	/** Creation time. */
	ScePspDateTime 	st_ctime;
	/** Access time. */
	ScePspDateTime 	st_atime;
	/** Modification time. */
	ScePspDateTime 	st_mtime;
	/** Device-specific data. */
	unsigned int 	st_private[6];
} SceIoStat;

#endif /* PSPIOFILEMGR_STAT_H */
