/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psputility_avmodules.h - Load audio/video modules from user mode on 2.xx+
 *
 * Copyright (c) 2007 David Perry <tias_dp@hotmail.com>
 *
 */
#ifndef __PSPUTILITY_AVMODULES_H__
#define __PSPUTILITY_AVMODULES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <psptypes.h>

#define PSP_AV_MODULE_AVCODEC		0
#define PSP_AV_MODULE_SASCORE		1
#define PSP_AV_MODULE_ATRAC3PLUS	2 // Requires PSP_AV_MODULE_AVCODEC loading first
#define PSP_AV_MODULE_MPEGBASE		3 // Requires PSP_AV_MODULE_AVCODEC loading first
#define PSP_AV_MODULE_MP3			4
#define PSP_AV_MODULE_VAUDIO		5
#define PSP_AV_MODULE_AAC			6
#define PSP_AV_MODULE_G729			7

/**
 * Load an audio/video module (PRX) from user mode.
 *
 * Available on firmware 2.00 and higher only.
 *
 * @param module - module number to load (PSP_AV_MODULE_xxx)
 * @return 0 on success, < 0 on error
 */
int sceUtilityLoadAvModule(int module);

/**
 * Unload an audio/video module (PRX) from user mode.
 * Available on firmware 2.00 and higher only.
 *
 * @param module - module number to be unloaded
 * @return 0 on success, < 0 on error
 */
int sceUtilityUnloadAvModule(int module);

#ifdef __cplusplus
}
#endif

#endif
