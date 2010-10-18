/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psputility_usbmodules.h - Load usb modules from user mode on 2.70 and higher
 *
 * Copyright (c) 2007 David Perry <tias_dp@hotmail.com>
 *
 */
#ifndef __PSPUTILITY_USBMODULES_H__
#define __PSPUTILITY_USBMODULES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <psptypes.h>

#define PSP_USB_MODULE_PSPCM	1
#define PSP_USB_MODULE_ACC	2
#define PSP_USB_MODULE_MIC	3 // Requires PSP_USB_MODULE_ACC loading first
#define PSP_USB_MODULE_CAM	4 // Requires PSP_USB_MODULE_ACC loading first
#define PSP_USB_MODULE_GPS	5 // Requires PSP_USB_MODULE_ACC loading first

/**
 * Load a usb module (PRX) from user mode.
 * Available on firmware 2.70 and higher only.
 *
 * @param module - module number to load (PSP_USB_MODULE_xxx)
 * @return 0 on success, < 0 on error
*/
int sceUtilityLoadUsbModule(int module);

/**
 * Unload a usb module (PRX) from user mode.
 * Available on firmware 2.70 and higher only.
 *
 * @param module - module number to be unloaded
 * @return 0 on success, < 0 on error
*/
int sceUtilityUnloadUsbModule(int module);

#ifdef __cplusplus
}
#endif

#endif
