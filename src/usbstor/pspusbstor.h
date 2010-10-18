/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspusbstor.h - Prototypes for the sceUsbStor and sceUsbStorBoot libraries
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: pspusbstor.h 1095 2005-09-27 21:02:16Z jim $
 */
#ifndef __PSPUSBSTOR_H__
#define __PSPUSBSTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PSP_USBSTOR_DRIVERNAME "USBStor_Driver"

/**
  * Register an eventFlag to send notifications to.
  * 
  * @param eventFlag - eventFlag created with sceKernelCreateEventFlag
  *
  * @return 0 on success
  */
int sceUsbstorBootRegisterNotify(u32 eventFlag);

/**
  * Unregister a previously registered eventFlag.
  * 
  * @param eventFlag - eventFlag created with sceKernelCreateEventFlag
  *
  * @return 0 on success
  */
int sceUsbstorBootUnregisterNotify(u32 eventFlag);

/**
  * Tell the USBstorBoot driver the size of MS
  *
  * @note I'm not sure if this is the actual size of the media or not
  * as it seems to have no bearing on what size windows detects.
  * PSPPET passes 0x800000
  * 
  * @param size - capacity of memory stick
  *
  * @return 0 on success
  */
int sceUsbstorBootSetCapacity(u32 size);

// the following are disabled until more testing is done
#if 0
int sceUsbstorBootGetDataSize(void); // what for ?
int sceUsbstorBootSetLoadAddr(u32 addr); // ?
int sceUsbstorBootSetStatus(u32 status); // 1=?
int sceUsbstorGetStatus(?)
#endif

#ifdef __cplusplus
}
#endif

#endif
