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
#include <pspusbbus.h>

#define PSP_USBACC_DRIVERNAME	"USBAccBaseDriver"

/* Error codes returned by the sceUsbAcc functions */
#define PSP_USBACC_ERROR_NOT_AUTHENTICATED	(0x80243701)

/** Accessory type bits used with ::sceUsbAccRegisterType / ::sceUsbAccUnregisterType */
enum PspUsbAccType {
	/** Microphone */
	PSP_USBACC_TYPE_MIC	= 0x01,
	/** Camera */
	PSP_USBACC_TYPE_CAMERA	= 0x02,
	/** GPS receiver */
	PSP_USBACC_TYPE_GPS	= 0x04,
	/** DMB / 1Seg TV tuner */
	PSP_USBACC_TYPE_DMB	= 0x08,
};

/** Accessory specific information block returned by ::sceUsbAccGetInfo */
typedef struct SceUsbAccInfo {
	/** The layout depends on the connected accessory */
	u8	data[8];
} SceUsbAccInfo;

/**
 * Command packet sent from the PSP to an accessory by ::sceUsbAccIntrInReq.
 * The caller places one of these in the UsbdDeviceReq data buffer.
 */
typedef struct SceUsbAccPacket {
	/** Accessory type (::PspUsbAccType) */
	u16	type;
	/** Command / opcode (accessory specific) */
	u8	cmd;
	/** Payload length in bytes, must be <= 60 */
	u8	len;
	/** Payload */
	u8	data[60];
} SceUsbAccPacket;

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

/**
 * Registers the accessory type(s) the caller handles (::PspUsbAccType bits).
 * An accessory is accepted only if it advertises every registered type
 * (none registered = any accessory accepted).
 *
 * Available on firmware 2.70 and higher only.
 *
 * @param type - mask of accessory type bits to register
 *
 * @return 0 on success, PSP_USB_ERROR_ALREADY_DONE if any requested
 *         bit is already registered
*/
int sceUsbAccRegisterType(u16 type);

/**
 * Unregisters accessory type(s) previously registered with
 * ::sceUsbAccRegisterType.
 *
 * Available on firmware 2.70 and higher only.
 *
 * @param type - mask of accessory type bits to unregister
 *
 * @return 0 on success, PSP_USB_ERROR_DRIVER_NOT_FOUND if none of the requested
 *         bits was registered
*/
int sceUsbAccUnregisterType(u16 type);

/**
 * Queues a packet to be sent from the PSP to the accessory on the
 * interrupt endpoint (EP 0x81). req->data must point to a ::SceUsbAccPacket.
 *
 * Available on firmware 2.70 and higher only.
 *
 * @param req - UsbdDeviceReq whose data points to a filled ::SceUsbAccPacket
 *
 * @return 0 on success, PSP_USB_ERROR_BUS_DRIVER_NOT_STARTED if no accessory
 *         is attached, PSP_USB_ERROR_INVALID_ARGUMENT if the payload is too long
*/
int sceUsbAccIntrInReq(struct UsbdDeviceReq *req);

#ifdef __cplusplus
}
#endif

#endif
