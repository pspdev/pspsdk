/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psputility_osk.h - Definitions and Functions for OSK section of
 *                     the pspUtility library
 *
 * Copyright (c) 2006 McZonk
 * Copyright (c) 2008 InsertWittyName <tias_dp@hotmail.com>
 *
 * $Id: psputility_osk.h 2433 2008-10-15 10:00:27Z iwn $
 */
#ifndef PSPOSK_H
#define PSPOSK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <psptypes.h>

/**
 * Enumeration for input language
 */
enum SceUtilityOskInputLanguage
{
	PSP_UTILITY_OSK_LANGUAGE_DEFAULT =		0x00,
	PSP_UTILITY_OSK_LANGUAGE_JAPANESE =		0x01,
	PSP_UTILITY_OSK_LANGUAGE_ENGLISH =		0x02,
	PSP_UTILITY_OSK_LANGUAGE_FRENCH =		0x03,
	PSP_UTILITY_OSK_LANGUAGE_SPANISH =		0x04,
	PSP_UTILITY_OSK_LANGUAGE_GERMAN =		0x05,
	PSP_UTILITY_OSK_LANGUAGE_ITALIAN =		0x06,
	PSP_UTILITY_OSK_LANGUAGE_DUTCH =		0x07,
	PSP_UTILITY_OSK_LANGUAGE_PORTUGESE =	0x08,
	PSP_UTILITY_OSK_LANGUAGE_RUSSIAN =		0x09,
	PSP_UTILITY_OSK_LANGUAGE_KOREAN =		0x0a
};

/**
 * Enumeration for OSK internal state
 */
enum SceUtilityOskState
{
	PSP_UTILITY_OSK_DIALOG_NONE = 0,	/**< No OSK is currently active */
	PSP_UTILITY_OSK_DIALOG_INITING,		/**< The OSK is currently being initialized */
	PSP_UTILITY_OSK_DIALOG_INITED,		/**< The OSK is initialised */
	PSP_UTILITY_OSK_DIALOG_VISIBLE,		/**< The OSK is visible and ready for use */
	PSP_UTILITY_OSK_DIALOG_QUIT,		/**< The OSK has been cancelled and should be shut down */
	PSP_UTILITY_OSK_DIALOG_FINISHED		/**< The OSK has successfully shut down */	
};

/**
 * Enumeration for OSK field results
 */
enum SceUtilityOskResult
{
	PSP_UTILITY_OSK_RESULT_UNCHANGED =	0,
	PSP_UTILITY_OSK_RESULT_CANCELLED,
	PSP_UTILITY_OSK_RESULT_CHANGED
};

/**
 * Enumeration for input types (these are limited by initial choice of language)
 */
enum SceUtilityOskInputType
{
	PSP_UTILITY_OSK_INPUTTYPE_ALL =						0x00000000,
	PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT =				0x00000001,
	PSP_UTILITY_OSK_INPUTTYPE_LATIN_SYMBOL =			0x00000002,
	PSP_UTILITY_OSK_INPUTTYPE_LATIN_LOWERCASE =			0x00000004,
	PSP_UTILITY_OSK_INPUTTYPE_LATIN_UPPERCASE =			0x00000008,
	PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_DIGIT =			0x00000100,
	PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_SYMBOL =			0x00000200,
	PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_LOWERCASE =		0x00000400,
	PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_UPPERCASE =		0x00000800,
	// http://en.wikipedia.org/wiki/Hiragana
	PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_HIRAGANA =		0x00001000,
	// http://en.wikipedia.org/wiki/Katakana
	// Half-width Katakana
	PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_HALF_KATAKANA =	0x00002000,
	PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_KATAKANA =		0x00004000,
	// http://en.wikipedia.org/wiki/Kanji
	PSP_UTILITY_OSK_INPUTTYPE_JAPANESE_KANJI =			0x00008000,
	PSP_UTILITY_OSK_INPUTTYPE_RUSSIAN_LOWERCASE =		0x00010000,
	PSP_UTILITY_OSK_INPUTTYPE_RUSSIAN_UPPERCASE =		0x00020000,
	PSP_UTILITY_OSK_INPUTTYPE_KOREAN =					0x00040000,
	PSP_UTILITY_OSK_INPUTTYPE_URL =						0x00080000
};

/**
 * OSK Field data
 */
typedef struct _SceUtilityOskData
{
    /** Unknown. Pass 0. */
	int unk_00;
	/** Unknown. Pass 0. */
    int unk_04;
	/** One of ::SceUtilityOskInputLanguage */
    int language;
	/** Unknown. Pass 0. */
    int unk_12;
	/** One or more of ::SceUtilityOskInputType (types that are selectable by pressing SELECT) */
    int inputtype;
	/** Number of lines */
    int lines;
	/** Unknown. Pass 0. */
    int unk_24;
	/** Description text */
    unsigned short* desc;
	/** Initial text */
    unsigned short* intext;
	/** Length of output text */
    int outtextlength;
	/** Pointer to the output text */
    unsigned short* outtext;
	/** Result. One of ::SceUtilityOskResult */
    int result;
	/** The max text that can be input */
    int outtextlimit;
	
} SceUtilityOskData;

/**
 * OSK parameters
 */
typedef struct _SceUtilityOskParams
{
	pspUtilityDialogCommon base;
	/** Number of input fields */
	int datacount;
	/** Pointer to the start of the data for the input fields */
	SceUtilityOskData* data;
	/** The local OSK state, one of ::SceUtilityOskState */
	int state;
	/** Unknown. Pass 0 */
	int unk_60;
	
} SceUtilityOskParams;

/**
 * Create an on-screen keyboard
 *
 * @param params - OSK parameters.
 *
 * @return < 0 on error.
 */
int sceUtilityOskInitStart(SceUtilityOskParams* params);

/**
 * Remove a currently active keyboard. After calling this function you must
 *
 * poll sceUtilityOskGetStatus() until it returns PSP_UTILITY_DIALOG_NONE.
 *
 * @return < 0 on error.
 */
int sceUtilityOskShutdownStart(void);

/**
 * Refresh the GUI for a keyboard currently active
 *
 * @param n - Unknown, pass 1.
 *
 * @return < 0 on error.
 */
int sceUtilityOskUpdate(int n);

/**
 * Get the status of a on-screen keyboard currently active.
 *
 * @return the current status of the keyboard. See ::pspUtilityDialogState for details.
 */
int sceUtilityOskGetStatus(void);

#ifdef __cplusplus
}
#endif

#endif
