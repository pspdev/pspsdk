/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psputility_savedata.h - Definitions and Functions for savedata part of
 *                     pspUtility library
 *
 * Copyright (c) 2005    Shine
 *                       weltall <weltall@consoleworld.org>
 *                       Marcus R. Brown <mrbrown@ocgnet.org>
 *						 InsertWittyName <tias_dp@hotmail.com>
 *
 */

#ifndef __PSPUTILITY_SAVEDATA_H__
#define __PSPUTILITY_SAVEDATA_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Save data utility modes */
typedef enum
{
	PSP_UTILITY_SAVEDATA_AUTOLOAD = 0,
	PSP_UTILITY_SAVEDATA_AUTOSAVE,
	PSP_UTILITY_SAVEDATA_LOAD,
	PSP_UTILITY_SAVEDATA_SAVE,
	PSP_UTILITY_SAVEDATA_LISTLOAD,
	PSP_UTILITY_SAVEDATA_LISTSAVE,
	PSP_UTILITY_SAVEDATA_LISTDELETE,
	PSP_UTILITY_SAVEDATADELETE,

} PspUtilitySavedataMode;

/** Initial focus position for list selection types */
typedef enum
{
	PSP_UTILITY_SAVEDATA_FOCUS_UNKNOWN = 0,
	PSP_UTILITY_SAVEDATA_FOCUS_FIRSTLIST,	/* First in list */
	PSP_UTILITY_SAVEDATA_FOCUS_LASTLIST,	/* Last in list */
	PSP_UTILITY_SAVEDATA_FOCUS_LATEST,	/* Most recent date */
	PSP_UTILITY_SAVEDATA_FOCUS_OLDEST,	/* Oldest date */
	PSP_UTILITY_SAVEDATA_FOCUS_UNKNOWN2,
	PSP_UTILITY_SAVEDATA_FOCUS_UNKNOWN3,
	PSP_UTILITY_SAVEDATA_FOCUS_FIRSTEMPTY, /* First empty slot */
	PSP_UTILITY_SAVEDATA_FOCUS_LASTEMPTY,	/*Last empty slot */
	
} PspUtilitySavedataFocus;


/** title, savedataTitle, detail: parts of the unencrypted SFO
    data, it contains what the VSH and standard load screen shows */
typedef struct PspUtilitySavedataSFOParam
{
	char title[0x80];
	char savedataTitle[0x80];
	char detail[0x400];
	unsigned char parentalLevel;
	unsigned char unknown[3];
	
} PspUtilitySavedataSFOParam;

typedef struct PspUtilitySavedataFileData {
	void *buf;
	SceSize bufSize;
	SceSize size;	/* ??? - why are there two sizes? */
	int unknown;
	
} PspUtilitySavedataFileData;

typedef struct PspUtilitySavedataListSaveNewData
{
	PspUtilitySavedataFileData icon0;
	char *title;
	
} PspUtilitySavedataListSaveNewData;

/** Structure to hold the parameters for the ::sceUtilitySavedataInitStart function. */
typedef struct SceUtilitySavedataParam
{
	pspUtilityDialogCommon base;

	PspUtilitySavedataMode mode;
	
	int unknown1;
	
	int overwrite;

	/** gameName: name used from the game for saves, equal for all saves */
	char gameName[13];
	char reserved[3];
	/** saveName: name of the particular save, normally a number */
	char saveName[20];

	/** saveNameList: used by multiple modes */
	char (*saveNameList)[20];

	/** fileName: name of the data file of the game for example DATA.BIN */
	char fileName[13];
	char reserved1[3];

	/** pointer to a buffer that will contain data file unencrypted data */
	void *dataBuf;
	/** size of allocated space to dataBuf */
	SceSize dataBufSize;
	SceSize dataSize;

	PspUtilitySavedataSFOParam sfoParam;

	PspUtilitySavedataFileData icon0FileData;
	PspUtilitySavedataFileData icon1FileData;
	PspUtilitySavedataFileData pic1FileData;
	PspUtilitySavedataFileData snd0FileData;

	/** Pointer to an PspUtilitySavedataListSaveNewData structure */
	PspUtilitySavedataListSaveNewData *newData;

	/** Initial focus for lists */
	PspUtilitySavedataFocus focus;

	/** unknown2: ? */
	int unknown2[4];

#if _PSP_FW_VERSION >= 200

	/** key: encrypt/decrypt key for save with firmware >= 2.00 */
	char key[16];

	/** unknown3: ? */
	char unknown3[20];

#endif

} SceUtilitySavedataParam;


/**
 * Saves or Load savedata to/from the passed structure
 * After having called this continue calling sceUtilitySavedataGetStatus to
 * check if the operation is completed
 *
 * @param params - savedata parameters
 * @return 0 on success
 */
int sceUtilitySavedataInitStart(SceUtilitySavedataParam * params);

/**
 * Check the current status of the saving/loading/shutdown process
 * Continue calling this to check current status of the process
 * before calling this call also sceUtilitySavedataUpdate
 * @return 2 if the process is still being processed.
 * 3 on save/load success, then you can call sceUtilitySavedataShutdownStart.
 * 4 on complete shutdown.
 */
int sceUtilitySavedataGetStatus(void);


/**
 * Shutdown the savedata utility. after calling this continue calling
 * ::sceUtilitySavedataGetStatus to check when it has shutdown
 *
 * @return 0 on success
 *
 */
int sceUtilitySavedataShutdownStart(void);

/**
 * Refresh status of the savedata function
 *
 * @param unknown - unknown, pass 1
 */
void sceUtilitySavedataUpdate(int unknown);

#ifdef __cplusplus
}
#endif

#endif
