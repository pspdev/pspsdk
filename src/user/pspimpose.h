/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspimpose.h - Prototypes for the sceImpose library.
 *
 * Copyright (c) 2007 Iaroslav Gaponenko <adrahil@gmail.com>
 *
 */

#ifndef __IMPOSE_H__
#define __IMPOSE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PSP_IMPOSE_UMD_POPUP_ENABLED 1
#define PSP_IMPOSE_UMD_POPUP_DISABLED 0

/**
 * Get the value of the backlight timer.
 *
 * @return backlight timer in seconds or < 0 on error
 *
 */
int sceImposeGetBacklightOffTime(void);

/**
 * Set the value of the backlight timer.
 *
 * @param value - The backlight timer. (30 to a lot of seconds)
 * @return < 0 on error
 *
 */
int sceImposeSetBacklightOffTime(int value);

/**
 * Get the language and button assignment parameters
 *
 * @return < 0 on error
 *
 */
int sceImposeGetLanguageMode(int *lang, int *button);

/**
 * Set the language and button assignment parameters
 *
 * /!\ parameter values not known.
 *
 * @param lang - Language
 * @param button - Button assignment
 * @return < 0 on error
 *
 */
int sceImposeSetLanguageMode(int lang, int button);

/**
 * Get the value of the UMD popup.
 *
 * @return umd popup state or < 0 on error
 *
 */
int sceImposeGetUMDPopup(void);

/**
 * Set the value of the UMD popup.
 *
 * @param value - The popup mode.
 * @return < 0 on error
 *
 */
int sceImposeSetUMDPopup(int value);

/**
 * Get the value of the Home popup.
 *
 * @return home popup state or < 0 on error
 *
 */
int sceImposeGetHomePopup(void);

/**
 * Set the value of the Home popup.
 *
 * @param value - The popup mode.
 * @return < 0 on error
 *
 */
int sceImposeSetHomePopup(int value);

#ifdef __cplusplus
}
#endif

#endif
