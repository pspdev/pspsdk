/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspimpose_driver.h - Prototypes for the sceImpose_driver library.
 *
 * Copyright (c) 2007 Iaroslav Gaponenko <adrahil@gmail.com>
 *
 */

#ifndef __IMPOSE_DRIVER_H__
#define __IMPOSE_DRIVER_H__

#include <pspimpose.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int SceImposeParam;

/**
 * These values have been found in the 3.52 kernel.
 * Therefore, they might not be supported by previous ones.
 */
#define PSP_IMPOSE_MAIN_VOLUME                  0x1
#define PSP_IMPOSE_BACKLIGHT_BRIGHTNESS         0x2
#define PSP_IMPOSE_EQUALIZER_MODE               0x4
#define PSP_IMPOSE_MUTE                         0x8
#define PSP_IMPOSE_AVLS                         0x10
#define PSP_IMPOSE_TIME_FORMAT                  0x20
#define PSP_IMPOSE_DATE_FORMAT                  0x40
#define PSP_IMPOSE_LANGUAGE                     0x80
#define PSP_IMPOSE_BACKLIGHT_OFF_INTERVAL       0x200
#define PSP_IMPOSE_SOUND_REDUCTION              0x400

/**
 * Fetch the value of an Impose parameter.
 *
 * @return value of the parameter on success, < 0 on error
 */
int sceImposeGetParam(SceImposeParam param);

/**
 * Change the value of an Impose parameter.
 *
 * @param param - The parameter to change.
 * @param value - The value to set the parameter to.
 * @return < 0 on error
 *
 */
int sceImposeSetParam(SceImposeParam param, int value);

/**
 * Check the video out. (for psp slim?)
 *
 * @param value - video out mode/status(?)
 * @return < 0 on error
 *
 */
int sceImposeCheckVideoOut(int *value);

#ifdef __cplusplus
}
#endif

#endif
