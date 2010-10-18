/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psputility_modules.h - Load modules from user mode
 *
 * Copyright (c) 2008 David Perry <tias_dp@hotmail.com>
 *
 */
#ifndef __PSPUTILITY_MODULES_H__
#define __PSPUTILITY_MODULES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <psptypes.h>

/* Net Modules */
#define PSP_MODULE_NET_COMMON		0x0100
#define PSP_MODULE_NET_ADHOC		0x0101
#define PSP_MODULE_NET_INET			0x0102
#define PSP_MODULE_NET_PARSEURI		0x0103
#define PSP_MODULE_NET_PARSEHTTP	0x0104
#define PSP_MODULE_NET_HTTP			0x0105
#define PSP_MODULE_NET_SSL			0x0106

/* USB Modules */
#define PSP_MODULE_USB_PSPCM		0x0200
#define PSP_MODULE_USB_MIC			0x0201
#define PSP_MODULE_USB_CAM			0x0202
#define PSP_MODULE_USB_GPS			0x0203

/* Audio/video Modules */
#define PSP_MODULE_AV_AVCODEC		0x0300
#define PSP_MODULE_AV_SASCORE		0x0301
#define PSP_MODULE_AV_ATRAC3PLUS	0x0302
#define PSP_MODULE_AV_MPEGBASE		0x0303
#define PSP_MODULE_AV_MP3			0x0304
#define PSP_MODULE_AV_VAUDIO		0x0305
#define PSP_MODULE_AV_AAC			0x0306
#define PSP_MODULE_AV_G729			0x0307

/* NP */
#define PSP_MODULE_NP_COMMON		0x0400
#define PSP_MODULE_NP_SERVICE		0x0401
#define PSP_MODULE_NP_MATCHING2		0x0402

#define PSP_MODULE_NP_DRM			0x0500

/* IrDA */
#define PSP_MODULE_IRDA				0x0600


/**
 * Load a module (PRX) from user mode.
 *
 * @param module - module to load (PSP_MODULE_xxx)
 *
 * @return 0 on success, < 0 on error
 */
int sceUtilityLoadModule(int module);

/**
 * Unload a module (PRX) from user mode.
 *
 * @param module - module to unload (PSP_MODULE_xxx)
 *
 * @return 0 on success, < 0 on error
 */
int sceUtilityUnloadModule(int module);

#ifdef __cplusplus
}
#endif

#endif
