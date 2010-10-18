/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psputility_gamesharing.h - Game Sharing utility library
 *
 * Copyright (c) 2008 InsertWittyName <tias_dp@hotmail.com>
 *
 */
#ifndef __PSPUTILITY_GAMESHARING_H__
#define __PSPUTILITY_GAMESHARING_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	PSP_UTILITY_GAMESHARING_MODE_SINGLE		= 1,	/* Single send */
	PSP_UTILITY_GAMESHARING_MODE_MULTIPLE	= 2		/* Up to 4 simultaneous sends */
	
} pspUtilityGameSharingMode;

typedef enum
{
	PSP_UTILITY_GAMESHARING_DATA_TYPE_FILE		= 1, /* EBOOT is a file */
	PSP_UTILITY_GAMESHARING_DATA_TYPE_MEMORY	= 2, /* EBOOT is in memory */
	
} pspUtilityGameSharingDataType;

/**
 * Structure to hold the parameters for Game Sharing
**/
typedef struct _pspUtilityGameSharingParams
{
    pspUtilityDialogCommon base;
    int unknown1;							/* Set to 0 */
	int unknown2;							/* Set to 0 */
	char name[8];
	int unknown3;							/* Set to 0 */
	int unknown4;							/* Set to 0 */
	int unknown5;							/* Set to 0 */
	int result;								/* Return value */
	char *filepath;							/* File path if PSP_UTILITY_GAMESHARING_DATA_TYPE_FILE specified */
	pspUtilityGameSharingMode mode;			/* Send mode. One of ::pspUtilityGameSharingMode */
	pspUtilityGameSharingDataType datatype; /* Data type. One of ::pspUtilityGameSharingDataType */
	void *data;								/* Pointer to the EBOOT data in memory */
	unsigned int datasize;					/* Size of the EBOOT data in memory */

} pspUtilityGameSharingParams;

/**
 * Init the game sharing
 *
 * @param params - game sharing parameters
 * @return 0 on success, < 0 on error.
 */
int sceUtilityGameSharingInitStart(pspUtilityGameSharingParams *params);

/**
 * Shutdown game sharing. 
 */
void sceUtilityGameSharingShutdownStart(void);

/**
 * Get the current status of game sharing.
 *
 * @return 2 if the GUI is visible (you need to call sceUtilityGameSharingGetStatus).
 * 3 if the user cancelled the dialog, and you need to call sceUtilityGameSharingShutdownStart.
 * 4 if the dialog has been successfully shut down.
 */
int sceUtilityGameSharingGetStatus(void);

/**
 * Refresh the GUI for game sharing
 *
 * @param n - unknown, pass 1
 */
void sceUtilityGameSharingUpdate(int n);

#ifdef __cplusplus
}
#endif

#endif
