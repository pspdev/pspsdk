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

struct PspIoDrv;

/** Structure passed to the init and exit functions of the io driver system */
typedef struct PspIoDrvArg
{
	/** Pointer to the original driver which was added */
	struct PspIoDrv *drv;
	/** Pointer to a user defined argument (if written by the driver will preseve across calls */
	void *arg;
	/** The number of file descriptor UID related to the device. */
	SceSize user_fd_count;
} PspIoDrvArg;

typedef struct SceIoCwd {
    struct SceIoCwd *next;
    char *path_name;
    PspIoDrvArg *drv;
    void *cwd_private;
    int ref_count;
} SceIoCwd;

/** Structure passed to the file functions of the io driver system */
typedef struct PspIoDrvFileArg
{
	/** The file flags. Bit or'ed `PSP_O_*` flags */
	u32 flags;
	/** The file system number, e.g. if a file is opened as host5:/myfile.txt this field will be 5 */
	u32 fs_num;
	/** A pointer to the driver entry data */
	PspIoDrvArg *drv;
	/** The device attributes */
	u32 dev_attr;
	/** Pointer to a user defined argument, this is preserved on a per file basis */
	void *arg;
	/** Current work directory data */
	SceIoCwd *cwd;
	/** The current file position offset. */
	s64 file_pos;
	/** he thread UID of owner (?). */
	SceUID thread_id;
	u32 unk;
	/** UID of the opened file */
	SceUID uid;
	/** The thread UID of the thread that opened the file. */
	SceUID open_thread_id;
	/** If the file is opened in user mode. */
	u8 is_user_mode;
	/** If the file was opened with power lock flag. */
	u8 is_user_mode;
	/** Unknown. It is a boolean of some sort, async related. */
	u8 unk2;
	/** The async task priority. */
	u8 async_priority;
	/** The thread UID of the thread for the file async operations. */
	SceUID async_thread_id;
	/** The semaphore UID for the file async operations. */
	SceUID async_sema;
	/** The event flag UID for the file async operations. */
	SceUID async_event_flag;
	/** The callback UID for the file async operations. */
	SceUID async_callback;
	/** A pointer to the parameter to pass to `async_callback`. */
	void * async_callback_argp;
	u32 unused;
	/** The current `k1` register value for async operations. */
	u32 k1;
	/** The async return value of operations. */
	s64 async_return;
	/** Arguments for the command to use. */
	s32 async_args[6];
	/** The async command to execute. */
	u32 async_cmd;
	/** The current user level of the file. */
	u32 user_level;
	/** The IO hook */
	// FIXME: Proper type... (SceIoHook)
	u32 hook[3];
	u32 unk3;
	char *new_path;
	/// The return address.
	SceSize return_addr;
} PspIoDrvFileArg;

/** Structure to maintain the file driver pointers */
typedef struct PspIoDrvFuncs
{
	int (*IoInit)(PspIoDrvArg* arg);
	int (*IoExit)(PspIoDrvArg* arg);
	int (*IoOpen)(PspIoDrvFileArg *arg, char *file, int flags, SceMode mode);
	int (*IoClose)(PspIoDrvFileArg *arg);
	int (*IoRead)(PspIoDrvFileArg *arg, char *data, int len);
	int (*IoWrite)(PspIoDrvFileArg *arg, const char *data, int len);
	SceOff (*IoLseek)(PspIoDrvFileArg *arg, SceOff ofs, int whence);
	int (*IoIoctl)(PspIoDrvFileArg *arg, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);
	int (*IoRemove)(PspIoDrvFileArg *arg, const char *name);
	int (*IoMkdir)(PspIoDrvFileArg *arg, const char *name, SceMode mode);
	int (*IoRmdir)(PspIoDrvFileArg *arg, const char *name);
	int (*IoDopen)(PspIoDrvFileArg *arg, const char *dirname);
	int (*IoDclose)(PspIoDrvFileArg *arg);
	int (*IoDread)(PspIoDrvFileArg *arg, SceIoDirent *dir);
	int (*IoGetstat)(PspIoDrvFileArg *arg, const char *file, SceIoStat *stat);
	int (*IoChstat)(PspIoDrvFileArg *arg, const char *file, SceIoStat *stat, int bits);
	int (*IoRename)(PspIoDrvFileArg *arg, const char *oldname, const char *newname);
	int (*IoChdir)(PspIoDrvFileArg *arg, const char *dir);
	int (*IoMount)(PspIoDrvFileArg *arg);
	int (*IoUmount)(PspIoDrvFileArg *arg);
	int (*IoDevctl)(PspIoDrvFileArg *arg, const char *devname, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);
	int (*IoUnk21)(PspIoDrvFileArg *arg);
} PspIoDrvFuncs;

typedef struct PspIoDrv
{
	/** The name of the device to add */
	const char *name;
	/** Device type, this 0x10 is for a filesystem driver */
	u32 dev_type;
	/** Unknown, set to `0x800` almost always (sometimes to `0x001`)*/
	u32 unk2;
	/** The device short description. */
	const char *name2;
	/** Pointer to a filled out functions table */
	PspIoDrvFuncs *funcs;
} PspIoDrv;

/** Compat: Name used on UOFW and March33 for `PspIoDrv` */
typedef PspIoDrv SceIoDeviceTable;
/** Compat: Name used on UOFW and March33 for `PspIoDrvFileArg` */
typedef PspIoDrvFileArg SceIoIob;
/** Compat: Name used on UOFW and March33 for `PspIoDrvArg` */
typedef PspIoDrvArg SceIoDeviceEntry;
/** Compat: Name used on UOFW and March33 for `PspIoDrvArg` */
typedef PspIoDrvFuncs SceIoDeviceFunction;

/**
  * Adds a new IO driver to the system.
  * @note This is only exported in the kernel version of IoFileMgr
  *
  * @param drv - Pointer to a filled out driver structure
  * @return < 0 on error.
  *
  * @par Example:
  * @code
  * PspIoDrvFuncs host_funcs = { ... };
  * PspIoDrv host_driver = { "host", 0x10, 0x800, "HOST", &host_funcs };
  * sceIoDelDrv("host");
  * sceIoAddDrv(&host_driver);
  * @endcode
  */
int sceIoAddDrv(PspIoDrv *drv);

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
