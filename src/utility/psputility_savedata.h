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
#include <pspkerneltypes.h>

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
	PSP_UTILITY_SAVEDATA_LISTALLDELETE,
	SCE_UTILITY_SAVEDATA_SIZES,
	SCE_UTILITY_SAVEDATA_AUTODELETE,
	SCE_UTILITY_SAVEDATA_DELETE,
	SCE_UTILITY_SAVEDATA_LIST,
	SCE_UTILITY_SAVEDATA_FILES,
	SCE_UTILITY_SAVEDATA_MAKEDATASECURE,
	SCE_UTILITY_SAVEDATA_MAKEDATA,
	SCE_UTILITY_SAVEDATA_READDATASECURE,
	SCE_UTILITY_SAVEDATA_READDATA,
	SCE_UTILITY_SAVEDATA_WRITEDATASECURE,
	SCE_UTILITY_SAVEDATA_WRITEDATA,
	SCE_UTILITY_SAVEDATA_ERASESECURE,
	SCE_UTILITY_SAVEDATA_ERASE,
	SCE_UTILITY_SAVEDATA_DELETEDATA,
	SCE_UTILITY_SAVEDATA_GETSIZE,
} PspUtilitySavedataMode;

/** Initial focus position for list selection types */
typedef enum
{
	PSP_UTILITY_SAVEDATA_FOCUS_UNKNOWN = 0,
	PSP_UTILITY_SAVEDATA_FOCUS_FIRSTLIST,	/* First in list */
	PSP_UTILITY_SAVEDATA_FOCUS_LASTLIST,	/* Last in list */
	PSP_UTILITY_SAVEDATA_FOCUS_LATEST,	/* Most recent date */
	PSP_UTILITY_SAVEDATA_FOCUS_OLDEST,	/* Oldest date */
	PSP_UTILITY_SAVEDATA_FOCUS_FIRSTDATA,	/* first non-empty (first if none) */
	PSP_UTILITY_SAVEDATA_FOCUS_LASTDATA,	/* last non-empty (first if none) */
	PSP_UTILITY_SAVEDATA_FOCUS_FIRSTEMPTY,	/* First empty slot */
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

typedef struct PspUtilitySavedataSizeEntry {
	uint64_t size;
	char name[16];

} PspUtilitySavedataSizeEntry;

typedef struct PspUtilitySavedataSizeInfo {
	int numSecureEntries;
	int numNormalEntries;
	PspUtilitySavedataSizeEntry *secureEntries;
	PspUtilitySavedataSizeEntry *normalEntries;
	int sectorSize;
	int freeSectors;
	int freeKB;
	char freeString[8];
	int neededKB;
	char neededString[8];
	int overwriteKB;
	char overwriteString[8];

} PspUtilitySavedataSizeInfo;

typedef struct SceUtilitySavedataIdListEntry
{
	int st_mode;
	ScePspDateTime sce_st_ctime;
	ScePspDateTime sce_st_atime;
	ScePspDateTime sce_st_mtime;
	char name[20];

} SceUtilitySavedataIdListEntry;

typedef struct SceUtilitySavedataIdListInfo
{
	int maxCount;
	int resultCount;
	SceUtilitySavedataIdListEntry *entries;

} SceUtilitySavedataIdListInfo;

typedef struct SceUtilitySavedataFileListEntry
{
	int st_mode;
	uint32_t st_unk0;
	uint64_t st_size;
	ScePspDateTime sce_st_ctime;
	ScePspDateTime sce_st_atime;
	ScePspDateTime sce_st_mtime;
	char name[16];

} SceUtilitySavedataFileListEntry;

typedef struct SceUtilitySavedataFileListInfo
{
	uint32_t maxSecureEntries;
	uint32_t maxNormalEntries;
	uint32_t maxSystemEntries;
	uint32_t resultNumSecureEntries;
	uint32_t resultNumNormalEntries;
	uint32_t resultNumSystemEntries;
	SceUtilitySavedataFileListEntry *secureEntries;
	SceUtilitySavedataFileListEntry *normalEntries;
	SceUtilitySavedataFileListEntry *systemEntries;

} SceUtilitySavedataFileListInfo;

typedef struct SceUtilitySavedataMsFreeInfo
{
	int clusterSize;
	int freeClusters;
	int freeSpaceKB;
	char freeSpaceStr[8];

} SceUtilitySavedataMsFreeInfo;

typedef struct SceUtilitySavedataUsedDataInfo
{
	int usedClusters;
	int usedSpaceKB;
	char usedSpaceStr[8];
	int usedSpace32KB;
	char usedSpace32Str[8];

} SceUtilitySavedataUsedDataInfo;

typedef struct SceUtilitySavedataMsDataInfo
{
	char gameName[13];
	char pad[3];
	char saveName[20];
	SceUtilitySavedataUsedDataInfo info;

} SceUtilitySavedataMsDataInfo;

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
	
	int bind;
	
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

	int abortStatus;

	/* Function SCE_UTILITY_SAVEDATA_TYPE_SIZES */
	SceUtilitySavedataMsFreeInfo *msFree;
	SceUtilitySavedataMsDataInfo *msData;
	SceUtilitySavedataUsedDataInfo *utilityData;

#if defined(_PSP_FW_VERSION) && _PSP_FW_VERSION >= 200

	/** key: encrypt/decrypt key for save with firmware >= 2.00 */
	char key[16];

	uint32_t secureVersion;
	int multiStatus;

	/* Function 11 LIST */
	SceUtilitySavedataIdListInfo *idList;

	/* Function 12 FILES */
	SceUtilitySavedataFileListInfo *fileList;

	/* Function 22 GETSIZES */
	PspUtilitySavedataSizeInfo *sizeInfo;

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
