/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspusbacc.h - Prototypes for the sceUsbAcc library
 *
 * Copyright (c) 2007 dot_blank
 *
 */
#ifndef __PSPUSBACC_H__
#define __PSPUSBACC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <psptypes.h>
#include <pspusb.h>

#define PSP_USBACC_DRIVERNAME	"USBAccBaseDriver"

/* Error codes returned by the sceUsbAcc functions */
#define PSP_USBACC_ERROR_NOT_AUTHENTICATED	(0x80243701)

/** Accessory specific information block returned by ::sceUsbAccGetInfo */
typedef struct SceUsbAccInfo {
	/** The layout depends on the connected accessory */
	u8	data[8];
} SceUsbAccInfo;

/**
 * Gets the authentication state of the connected USB accessory.
 * Returns PSP_USBACC_ERROR_NOT_AUTHENTICATED while the accessory has
 * not been authenticated yet or the authentication failed, and
 * PSP_USB_ERROR_BUS_DRIVER_NOT_STARTED when no accessory is attached.
 *
 * Available on firmware 2.70 and higher only.
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbAccGetAuthStat(void);

/**
 * Gets the information block sent by the connected USB accessory.
 * Returns PSP_USBACC_ERROR_NOT_AUTHENTICATED while the accessory has
 * not been authenticated yet or the authentication failed,
 * PSP_USB_ERROR_BUS_DRIVER_NOT_STARTED when no accessory is attached, and
 * PSP_USB_ERROR_INVALID_ARGUMENT if info is NULL or not a user pointer.
 *
 * Available on firmware 2.70 and higher only.
 *
 * @param info - pointer to a structure that receives the information
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbAccGetInfo(SceUsbAccInfo *info);

#ifdef __cplusplus
}
#endif

#endif
