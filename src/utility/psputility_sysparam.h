/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psputility_sysparam.h - Definitions and Functions for System Paramters 
 *                          section of the pspUtility library
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: psputility_sysparam.h 2433 2008-10-15 10:00:27Z iwn $
 */
#ifndef __PSPUTILITY_SYSPARAM_H__
#define __PSPUTILITY_SYSPARAM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <psptypes.h>

/**
 * IDs for use inSystemParam functions
 * PSP_SYSTEMPARAM_ID_INT are for use with SystemParamInt funcs
 * PSP_SYSTEMPARAM_ID_STRING are for use with SystemParamString funcs
 */
#define PSP_SYSTEMPARAM_ID_STRING_NICKNAME	1
#define PSP_SYSTEMPARAM_ID_INT_ADHOC_CHANNEL	2
#define PSP_SYSTEMPARAM_ID_INT_WLAN_POWERSAVE	3
#define PSP_SYSTEMPARAM_ID_INT_DATE_FORMAT	4
#define PSP_SYSTEMPARAM_ID_INT_TIME_FORMAT	5
//Timezone offset from UTC in minutes, (EST = -300 = -5 * 60)
#define PSP_SYSTEMPARAM_ID_INT_TIMEZONE		6
#define PSP_SYSTEMPARAM_ID_INT_DAYLIGHTSAVINGS	7
#define PSP_SYSTEMPARAM_ID_INT_LANGUAGE		8
/**
 * #9 seems to be Region or maybe X/O button swap.
 * It doesn't exist on JAP v1.0
 * is 1 on NA v1.5s
 * is 0 on JAP v1.5s
 * is read-only
 */
#define PSP_SYSTEMPARAM_ID_INT_UNKNOWN		9

/**
 * Return values for the SystemParam functions
 */
#define PSP_SYSTEMPARAM_RETVAL_OK	0
#define PSP_SYSTEMPARAM_RETVAL_FAIL	0x80110103

/**
 * Valid values for PSP_SYSTEMPARAM_ID_INT_ADHOC_CHANNEL
 */
#define PSP_SYSTEMPARAM_ADHOC_CHANNEL_AUTOMATIC 0
#define PSP_SYSTEMPARAM_ADHOC_CHANNEL_1		1
#define PSP_SYSTEMPARAM_ADHOC_CHANNEL_6		6
#define PSP_SYSTEMPARAM_ADHOC_CHANNEL_11	11

/**
 * Valid values for PSP_SYSTEMPARAM_ID_INT_WLAN_POWERSAVE
 */
#define PSP_SYSTEMPARAM_WLAN_POWERSAVE_OFF	0
#define PSP_SYSTEMPARAM_WLAN_POWERSAVE_ON	1

/**
 * Valid values for PSP_SYSTEMPARAM_ID_INT_DATE_FORMAT
 */
#define PSP_SYSTEMPARAM_DATE_FORMAT_YYYYMMDD	0
#define PSP_SYSTEMPARAM_DATE_FORMAT_MMDDYYYY	1
#define PSP_SYSTEMPARAM_DATE_FORMAT_DDMMYYYY	2

/**
 * Valid values for PSP_SYSTEMPARAM_ID_INT_TIME_FORMAT
 */
#define PSP_SYSTEMPARAM_TIME_FORMAT_24HR	0
#define PSP_SYSTEMPARAM_TIME_FORMAT_12HR	1

/**
 * Valid values for PSP_SYSTEMPARAM_ID_INT_DAYLIGHTSAVINGS
 */
#define PSP_SYSTEMPARAM_DAYLIGHTSAVINGS_STD	0
#define PSP_SYSTEMPARAM_DAYLIGHTSAVINGS_SAVING	1

/**
 * Valid values for PSP_SYSTEMPARAM_ID_INT_LANGUAGE
 */
#define PSP_SYSTEMPARAM_LANGUAGE_JAPANESE		0
#define PSP_SYSTEMPARAM_LANGUAGE_ENGLISH		1
#define PSP_SYSTEMPARAM_LANGUAGE_FRENCH			2
#define PSP_SYSTEMPARAM_LANGUAGE_SPANISH		3
#define PSP_SYSTEMPARAM_LANGUAGE_GERMAN			4
#define PSP_SYSTEMPARAM_LANGUAGE_ITALIAN		5
#define PSP_SYSTEMPARAM_LANGUAGE_DUTCH			6
#define PSP_SYSTEMPARAM_LANGUAGE_PORTUGUESE		7
#define PSP_SYSTEMPARAM_LANGUAGE_RUSSIAN		8
#define PSP_SYSTEMPARAM_LANGUAGE_KOREAN			9
#define PSP_SYSTEMPARAM_LANGUAGE_CHINESE_TRADITIONAL	10
#define PSP_SYSTEMPARAM_LANGUAGE_CHINESE_SIMPLIFIED	11

/**
 * Set Integer System Parameter
 *
 * @param id - which parameter to set
 * @param value - integer value to set
 * @return 0 on success, PSP_SYSTEMPARAM_RETVAL_FAIL on failure
 */
int sceUtilitySetSystemParamInt(int id, int value);

/**
 * Set String System Parameter
 *
 * @param id - which parameter to set
 * @param str - char * value to set
 * @return 0 on success, PSP_SYSTEMPARAM_RETVAL_FAIL on failure
 */
int sceUtilitySetSystemParamString(int id, const char *str);

/**
 * Get Integer System Parameter
 *
 * @param id - which parameter to get
 * @param value - pointer to integer value to place result in
 * @return 0 on success, PSP_SYSTEMPARAM_RETVAL_FAIL on failure
 */
int sceUtilityGetSystemParamInt( int id, int *value );

/**
 * Get String System Parameter
 *
 * @param id - which parameter to get
 * @param str - char * buffer to place result in
 * @param len - length of str buffer
 * @return 0 on success, PSP_SYSTEMPARAM_RETVAL_FAIL on failure
 */
int sceUtilityGetSystemParamString(int id, char *str, int len);

#ifdef __cplusplus
}
#endif

#endif
