/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspiofilemgr_kernel.h - Interface to the kernel mode library for IoFileMgr.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

#ifndef PSPIOFILEMGR_KERNEL_H
#define PSPIOFILEMGR_KERNEL_H

#include <psptypes.h>
#include <pspkerneltypes.h>
#include <pspiofilemgr.h>

/** @defgroup IoFileMgr_Kernel Driver interface to IoFileMgr
 *  This module contains the imports for the kernel's IO routines.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup IoFileMgr_Kernel Driver interface to IoFileMgr */
/**@{*/

struct SceIoDeviceTable;

/** Structure passed to the init and exit functions of the io driver system */
typedef struct SceIoDeviceEntry
{
	/** Pointer to the original driver which was added */
	struct SceIoDeviceTable *d_dp;
	/** Pointer to a user defined argument (if written by the driver will preseve across calls */
	void                    *d_private;
	int                      d_userfd_count;
} SceIoDeviceEntry;

typedef struct SceIoCwd
{
    struct SceIoCwd         *next;
    char                    *pathname;
    struct SceIoDeviceEntry *de;
    void                    *cwd_private;
    int                      refcount;
} SceIoCwd;

/** Structure passed to the file functions of the io driver system */
typedef struct SceIoIob
{
	/** Unknown */
        int               i_flgs;
	/** The file system number, e.g. if a file is opened as host5:/myfile.txt this field will be 5 */
	int               i_unit;
	/** Pointer to the driver structure */
	SceIoDeviceEntry *i_de;
	/** Unknown, again */
	int               d_type;
	/** Pointer to a user defined argument, this is preserved on a per file basis */
	void             *i_private;
	SceIoCwd         *i_cwd;
	SceOff            i_fpos;
	SceUID            i_thread;
	int               dummy;
} SceIoIob;

/** Structure to maintain the file driver pointers */
typedef struct SceIoDeviceFunction
{
	int      (* df_init)(struct SceIoDeviceEntry *de);
	int      (* df_exit)(struct SceIoDeviceEntry *);
	int      (* df_open)(struct SceIoIob *, char *, int, SceMode);
	int      (* df_close)(struct SceIoIob *);
	SceSSize (* df_read)(struct SceIoIob *, void *, SceSize);
	SceSSize (* df_write)(struct SceIoIob *, void *, SceSize);
	SceOff   (* df_lseek)(struct SceIoIob *, SceOff, int);
	int      (* df_ioctl)(struct SceIoIob *, int, void *, SceSize, void *, SceSize);
	int      (* df_remove)(struct SceIoIob *, char *);
	int      (* df_mkdir)(struct SceIoIob *, char *, SceMode);
	int      (* df_rmdir)(struct SceIoIob *, char *);
	int      (* df_dopen)(struct SceIoIob *, char *);
	int      (* df_dclose)(struct SceIoIob *);
	int      (* df_dread)(struct SceIoIob *, struct SceIoDirent *);
	int      (* df_getstat)(struct SceIoIob *, char *, struct SceIoStat *);
	int      (* df_chstat)(struct SceIoIob *, char *, struct SceIoStat *, u_int32_t);
	int      (* df_rename)(struct SceIoIob *, char *, char *);
	int      (* df_chdir)(struct SceIoIob *, char *);
	int      (* df_mount)(struct SceIoIob *, char *, char *, int, void *, int);
	int      (* df_umount)(struct SceIoIob *, char *);
	int      (* df_devctl)(struct SceIoIob *, char *, int, void *, SceSize, void *, SceSize);
	int      (* df_cancel)(struct SceIoIob *);
} SceIoDeviceFunction;

typedef struct SceIoDeviceTable
{
	/** The name of the device to add */
	const char          *dt_string;
	/** Device type, this 0x10 is for a filesystem driver */
	int                  dt_type;
	/** Unknown, set to 0x800 */
	int                  dt_size;
	/** This seems to be the same as name but capitalised :/ */
	const char          *dt_desc;
	/** Pointer to a filled out functions table */
	SceIoDeviceFunction *dt_func;
} SceIoDeviceTable;

/** 
  * Adds a new IO driver to the system.
  * @note This is only exported in the kernel version of IoFileMgr
  * 
  * @param drv - Pointer to a filled out driver structure
  * @return < 0 on error.
  *
  * @par Example:
  * @code
  * SceIoDeviceFunction host_funcs = { ... };
  * SceIoDeviceTable host_driver = { "host", 0x10, 0x800, "HOST", &host_funcs };
  * sceIoDelDrv("host");
  * sceIoAddDrv(&host_driver);
  * @endcode
  */
int sceIoAddDrv(SceIoDeviceTable *drv);

/**
  * Deletes a IO driver from the system.
  * @note This is only exported in the kernel version of IoFileMgr
  *
  * @param drv_name - Name of the driver to delete.
  * @return < 0 on error
  */
int sceIoDelDrv(const char *drv_name);

/**
  * Reopens an existing file descriptor.
  *
  * @param file - The new file to open.
  * @param flags - The open flags.
  * @param mode - The open mode.
  * @param fd - The old filedescriptor to reopen
  *
  * @return < 0 on error, otherwise the reopened fd.
  */
int sceIoReopen(const char *file, int flags, SceMode mode, SceUID fd);

/**
 * Get the current working directory for a thread.
 *
 * @param uid - The UID of the thread
 * @param dir - A character buffer in which to store the cwd
 * @param len - The length of the buffer
 *
 * @return Number of characters written to buf, if no cwd then 0 is 
 * returned.
 */
int sceIoGetThreadCwd(SceUID uid, char *dir, int len);

/**
 * Set the current working directory for a thread
 *
 * @param uid - The UID of the thread
 * @param dir - The directory to set
 *
 * @return 0 on success, < 0 on error
 */
int sceIoChangeThreadCwd(SceUID uid, char *dir);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSPIOFILEMGR_KERNEL_H */
