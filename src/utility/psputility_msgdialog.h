/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psputility_msdialog.h - Definitions and Functions for Dialogs
 *                         section of the pspUtility library
 *
 * Copyright (c) 2005 Marcus Comstedt <marcus@mc.pp.se>
 *			 (c) 2008 InsertWittyName <tias_dp@hotmail.com>
 *
 * $Id: psputility_msgdialog.h 2433 2008-10-15 10:00:27Z iwn $
 */
#ifndef __PSPUTILITY_DIALOGS_H__
#define __PSPUTILITY_DIALOGS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	PSP_UTILITY_MSGDIALOG_MODE_ERROR = 0, /* Error message */
	PSP_UTILITY_MSGDIALOG_MODE_TEXT /* String message */
	
} pspUtilityMsgDialogMode;

typedef enum
{
	PSP_UTILITY_MSGDIALOG_OPTION_ERROR = 0, /* Error message (why two flags?) */
	PSP_UTILITY_MSGDIALOG_OPTION_TEXT = 0x00000001, /* Text message (why two flags?) */
	PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS = 0x00000010,	/* Yes/No buttons instead of 'Cancel' */
	PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO  = 0x00000100	/* Default position 'No', if not set will default to 'Yes' */
	
} pspUtilityMsgDialogOption;

typedef enum
{
	PSP_UTILITY_MSGDIALOG_RESULT_UNKNOWN1 = 0,
	PSP_UTILITY_MSGDIALOG_RESULT_YES,
	PSP_UTILITY_MSGDIALOG_RESULT_NO,
	PSP_UTILITY_MSGDIALOG_RESULT_BACK
	
} pspUtilityMsgDialogPressed;

/**
 * Structure to hold the parameters for a message dialog
**/
typedef struct _pspUtilityMsgDialogParams
{
    pspUtilityDialogCommon base;
    int unknown;
	pspUtilityMsgDialogMode mode;
	unsigned int errorValue;
    /** The message to display (may contain embedded linefeeds) */
    char message[512];
	int options; /* OR ::pspUtilityMsgDialogOption together for multiple options */
	pspUtilityMsgDialogPressed buttonPressed;

} pspUtilityMsgDialogParams;

/**
 * Create a message dialog
 *
 * @param params - dialog parameters
 * @return 0 on success
 */
int sceUtilityMsgDialogInitStart(pspUtilityMsgDialogParams *params);

/**
 * Remove a message dialog currently active.  After calling this
 * function you need to keep calling GetStatus and Update until
 * you get a status of 4.
 */
void sceUtilityMsgDialogShutdownStart(void);

/**
 * Get the current status of a message dialog currently active.
 *
 * @return 2 if the GUI is visible (you need to call sceUtilityMsgDialogGetStatus).
 * 3 if the user cancelled the dialog, and you need to call sceUtilityMsgDialogShutdownStart.
 * 4 if the dialog has been successfully shut down.
 */
int sceUtilityMsgDialogGetStatus(void);

/**
 * Refresh the GUI for a message dialog currently active
 *
 * @param n - unknown, pass 1
 */
void sceUtilityMsgDialogUpdate(int n);

/**
 * Abort a message dialog currently active
 */
int sceUtilityMsgDialogAbort(void);

#ifdef __cplusplus
}
#endif

#endif
