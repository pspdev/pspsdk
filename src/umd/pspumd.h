/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspumd.h - Prototypes for the sceUmd library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: pspumd.h 2448 2008-12-11 21:45:37Z jim $
 */
#ifndef __UMD_H__
#define __UMD_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup UMD UMD Kernel Library */
/*@{*/

/** UMD Info struct */
typedef struct pspUmdInfo
{
	/** Set to sizeof(pspUmdInfo) */
	unsigned int size;
	/** One or more of ::pspUmdTypes */
	unsigned int type;
	
} pspUmdInfo;

/** Enumeration for UMD types */
enum pspUmdTypes
{
	PSP_UMD_TYPE_GAME =		0x10,
	PSP_UMD_TYPE_VIDEO =	0x20,
	PSP_UMD_TYPE_AUDIO =	0x40
};

/** Enumeration for UMD drive state */
enum pspUmdState
{
	PSP_UMD_NOT_PRESENT =	0x01,
	PSP_UMD_PRESENT =		0x02,
	PSP_UMD_CHANGED =		0x04,
	PSP_UMD_INITING =		0x08,
	PSP_UMD_INITED =		0x10,
	PSP_UMD_READY =			0x20
};

/** Enumeration for UMD stats (legacy) */
enum UmdDriveStat
{
	/** Wait for disc to be inserted */
	UMD_WAITFORDISC = PSP_UMD_PRESENT,
	/** Wait for the UMD to be initialised so it can be accessed from the mapped drive */
	UMD_WAITFORINIT	= PSP_UMD_READY
};

/** UMD Callback function */
typedef int (*UmdCallback)(int unknown, int event);

/** 
  * Check whether there is a disc in the UMD drive
  *
  * @return 0 if no disc present, anything else indicates a disc is inserted.
  */
int sceUmdCheckMedium(void);

/** 
  * Get the disc info
  *
  * @param info - A pointer to a ::pspUmdInfo struct
  *
  * @return < 0 on error
  */
int sceUmdGetDiscInfo(pspUmdInfo *info);

/** 
  * Activates the UMD drive
  * 
  * @param unit - The unit to initialise (probably). Should be set to 1.
  *
  * @param drive - A prefix string for the fs device to mount the UMD on (e.g. "disc0:")
  *
  * @return < 0 on error
  *
  * @par Example:
  * @code
  * // Wait for disc and mount to filesystem
  * int i;
  * i = sceUmdCheckMedium();
  * if(i == 0)
  * {
  *    sceUmdWaitDriveStat(PSP_UMD_PRESENT);
  * }
  * sceUmdActivate(1, "disc0:"); // Mount UMD to disc0: file system
  * sceUmdWaitDriveStat(PSP_UMD_READY);
  * // Now you can access the UMD using standard sceIo functions
  * @endcode
  */
int sceUmdActivate(int unit, const char *drive);

/** 
  * Deativates the UMD drive
  * 
  * @param unit - The unit to initialise (probably). Should be set to 1.
  *
  * @param drive - A prefix string for the fs device to mount the UMD on (e.g. "disc0:")
  *
  * @return < 0 on error
  */
int sceUmdDeactivate(int unit, const char *drive);

/** 
  * Wait for the UMD drive to reach a certain state
  *
  * @param stat - One or more of ::pspUmdState
  *
  * @return < 0 on error
  */
int sceUmdWaitDriveStat(int stat);

/** 
  * Wait for the UMD drive to reach a certain state
  *
  * @param stat - One or more of ::pspUmdState
  *
  * @param timeout - Timeout value in microseconds
  *
  * @return < 0 on error
  */
int sceUmdWaitDriveStatWithTimer(int stat, unsigned int timeout);

/** 
  * Wait for the UMD drive to reach a certain state (plus callback)
  *
  * @param stat - One or more of ::pspUmdState
  *
  * @param timeout - Timeout value in microseconds
  *
  * @return < 0 on error
  */
int sceUmdWaitDriveStatCB(int stat, unsigned int timeout);

/** 
  * Cancel a sceUmdWait* call
  *
  * @return < 0 on error
  */
int sceUmdCancelWaitDriveStat(void);

/** 
  * Get (poll) the current state of the UMD drive
  *
  * @return < 0 on error, one or more of ::pspUmdState on success
  */
int sceUmdGetDriveStat(void);

/** 
  * Get the error code associated with a failed event
  *
  * @return < 0 on error, the error code on success
  */
int sceUmdGetErrorStat(void);

/** 
  * Register a callback for the UMD drive
  * @note Callback is of type UmdCallback
  *
  * @param cbid - A callback ID created from sceKernelCreateCallback
  * @return < 0 on error
  * @par Example:
  * @code
  * int umd_callback(int unknown, int event)
  * {
  *      //do something
  * }     
  * int cbid = sceKernelCreateCallback("UMD Callback", umd_callback, NULL);
  * sceUmdRegisterUMDCallBack(cbid);
  * @endcode
  */
int sceUmdRegisterUMDCallBack(int cbid);

/** 
  * Un-register a callback for the UMD drive
  *
  * @param cbid - A callback ID created from sceKernelCreateCallback
  *
  * @return < 0 on error
  */
int sceUmdUnRegisterUMDCallBack(int cbid);

/** 
  * Permit UMD disc being replaced
  *
  * @return < 0 on error
  */
int sceUmdReplacePermit(void);

/** 
  * Prohibit UMD disc being replaced
  *
  * @return < 0 on error
  */
int sceUmdReplaceProhibit(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
