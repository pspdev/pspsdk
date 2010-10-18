/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspreg.h - Prototypes for the sceReg library.
 *
 * Copyright (c) 2005 James F
 *
 * $Id: pspreg.h 2433 2008-10-15 10:00:27Z iwn $
 */

#ifndef __REG_H__
#define __REG_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Reg Registry Kernel Library */
/*@{*/

/** System registry path */
#define SYSTEM_REGISTRY "/system"

/** Size of a keyname, used in ::sceRegGetKeys */
#define REG_KEYNAME_SIZE 27

/** Key types */
enum RegKeyTypes
{
	/** Key is a directory */
	REG_TYPE_DIR = 1,
	/** Key is an integer (4 bytes) */
	REG_TYPE_INT = 2,
	/** Key is a string */
	REG_TYPE_STR = 3,
	/** Key is a binary string */
	REG_TYPE_BIN = 4,
};

/** Typedef for a registry handle */
typedef unsigned int REGHANDLE;

/** Struct used to open a registry */
struct RegParam
{
	unsigned int regtype;     /* 0x0, set to 1 only for system */
	/** Seemingly never used, set to ::SYSTEM_REGISTRY */
	char name[256];        /* 0x4-0x104 */
	/** Length of the name */
	unsigned int namelen;     /* 0x104 */
	/** Unknown, set to 1 */
	unsigned int unk2;     /* 0x108 */
	/** Unknown, set to 1 */
	unsigned int unk3;     /* 0x10C */
};

/**
 * Open the registry
 *
 * @param reg - A filled in ::RegParam structure
 * @param mode - Open mode (set to 1)
 * @param h - Pointer to a REGHANDLE to receive the registry handle
 *
 * @return 0 on success, < 0 on error
 */
int sceRegOpenRegistry(struct RegParam *reg, int mode, REGHANDLE *h);

/**
 * Flush the registry to disk
 *
 * @param h - The open registry handle
 *
 * @return 0 on success, < 0 on error
 */
int sceRegFlushRegistry(REGHANDLE h);

/**
 * Close the registry 
 *
 * @param h - The open registry handle
 *
 * @return 0 on success, < 0 on error
 */
int sceRegCloseRegistry(REGHANDLE h);

/**
 * Open a registry directory
 *
 * @param h - The open registry handle
 * @param name - The path to the dir to open (e.g. /CONFIG/SYSTEM)
 * @param mode - Open mode (can be 1 or 2, probably read or read/write
 * @param hd - Pointer to a REGHANDLE to receive the registry dir handle
 *
 * @return 0 on success, < 0 on error
 */
int sceRegOpenCategory(REGHANDLE h, const char *name, int mode, REGHANDLE *hd);

/**
 * Remove a registry dir
 *
 * @param h - The open registry dir handle
 * @param name - The name of the key
 *
 * @return 0 on success, < 0 on error
 */
int sceRegRemoveCategory(REGHANDLE h, const char *name);

/**
 * Close the registry directory
 *
 * @param hd - The open registry dir handle
 *
 * @return 0 on success, < 0 on error
 */
int sceRegCloseCategory(REGHANDLE hd);

/**
 * Flush the registry directory to disk
 *
 * @param hd - The open registry dir handle
 *
 * @return 0 on success, < 0 on error
 */
int sceRegFlushCategory(REGHANDLE hd);

/**
 * Get a key's information
 *
 * @param hd - The open registry dir handle
 * @param name - Name of the key
 * @param hk - Pointer to a REGHANDLE to get registry key handle
 * @param type - Type of the key, on of ::RegKeyTypes
 * @param size - The size of the key's value in bytes
 *
 * @return 0 on success, < 0 on error
 */
int sceRegGetKeyInfo(REGHANDLE hd, const char *name, REGHANDLE *hk, unsigned int *type, SceSize *size);

/**
 * Get a key's information by name
 *
 * @param hd - The open registry dir handle
 * @param name - Name of the key
 * @param type - Type of the key, on of ::RegKeyTypes
 * @param size - The size of the key's value in bytes
 *
 * @return 0 on success, < 0 on error
 */
int sceRegGetKeyInfoByName(REGHANDLE hd, const char *name, unsigned int *type, SceSize *size);

/**
 * Get a key's value
 *
 * @param hd - The open registry dir handle
 * @param hk - The open registry key handler (from ::sceRegGetKeyInfo)
 * @param buf - Buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegGetKeyValue(REGHANDLE hd, REGHANDLE hk, void *buf, SceSize size);

/**
 * Get a key's value by name
 *
 * @param hd - The open registry dir handle
 * @param name - The key name
 * @param buf - Buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegGetKeyValueByName(REGHANDLE hd, const char *name, void *buf, SceSize size);

/**
 * Set a key's value
 *
 * @param hd - The open registry dir handle
 * @param name - The key name
 * @param buf - Buffer to hold the value
 * @param size - The size of the buffer
 *
 * @return 0 on success, < 0 on error
 */
int sceRegSetKeyValue(REGHANDLE hd, const char *name, const void *buf, SceSize size);

/**
 * Get number of subkeys in the current dir
 *
 * @param hd - The open registry dir handle
 * @param num - Pointer to an integer to receive the number
 *
 * @return 0 on success, < 0 on error
 */
int sceRegGetKeysNum(REGHANDLE hd, int *num);

/** 
 * Get the key names in the current directory
 *
 * @param hd - The open registry dir handle
 * @param buf - Buffer to hold the NUL terminated strings, should be num*REG_KEYNAME_SIZE
 * @param num - Number of elements in buf
 *
 * @return 0 on success, < 0 on error
 */
int sceRegGetKeys(REGHANDLE hd, char *buf, int num);

/**
 * Create a key
 * 
 * @param hd - The open registry dir handle
 * @param name - Name of the key to create
 * @param type - Type of key (note cannot be a directory type)
 * @param size - Size of the allocated value space
 *
 * @return 0 on success, < 0 on error
 */
int sceRegCreateKey(REGHANDLE hd, const char *name, int type, SceSize size);

/**
 * Remove a registry (HONESTLY, DO NOT USE)
 *
 * @param reg - Filled out registry parameter
 *
 * @return 0 on success, < 0 on error
 */
int sceRegRemoveRegistry(struct RegParam *reg);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
