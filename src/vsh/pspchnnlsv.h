/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  pspchnnlsv.h - Include for the pspChnnlsv library.
 *
 * Copyright (c) 2005 Jim Paris <jim@jtan.com>
 * Copyright (c) 2005 psp123
 *
 */
#ifndef __PSPCHNNLSV_H__
#define __PSPCHNNLSV_H__

/* The descriptions are mostly speculation. */

/** @defgroup Chnnlsv Chnnlsv Library
 * Library imports for the vsh chnnlsv library.
 */

#include <psptypes.h>

/** @addtogroup Chnnlsv Chnnlsv Library */
/**@{*/

typedef struct _pspChnnlsvContext1 {
	/** Cipher mode */
	int mode;
	/** Context data */
	u8 data[16];
	/** Context key */
	u8 key[16];
	/** Data size */
	u32 size;
} SceSdContext1;

typedef struct _pspChnnlsvContext2 {
	/** Cipher mode */
	u32 mode;
	u32 unk4;
	u8 data[16];
} SceSdContext2;

// Backwards compat
typedef SceSdContext1 pspChnnlsvContext1;
typedef SceSdContext2 pspChnnlsvContext2;
#define sceChnnlsv_E7833020 sceSdSetIndex
#define sceChnnlsv_F21A1FCA sceSdRemoveValue
#define sceChnnlsv_C4C494F8 sceSdGetLastIndex
#define sceChnnlsv_ABFDFC8B sceSdCreateList
#define sceChnnlsv_850A7FA1 sceSdSetMember
#define sceChnnlsv_21BE78B4 sceSdCleanList

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Initialize context
 *
 * @param ctx - Context
 * @param mode - Cipher mode
 * @return < 0 on error
 */
int sceSdSetIndex(SceSdContext1 *ctx, int mode);

/**
 * Process data
 *
 * @param ctx - Context
 * @param data - Data (aligned to 0x10)
 * @param len - Length (aligned to 0x10)
 * @return < 0 on error
 */
int sceSdRemoveValue(SceSdContext1 *ctx, unsigned char *data, int len);

/**
 * Finalize hash
 *
 * @param ctx - Context
 * @param hash - Hash output (aligned to 0x10, 0x10 bytes long)
 * @param cryptkey - Crypt key or NULL.
 * @return < 0 on error
 */
int sceSdGetLastIndex(SceSdContext1 *ctx, unsigned char *hash, unsigned char *cryptkey);

/**
 * Prepare a key, and set up integrity check
 *
 * @param ctx - Context
 * @param mode1 - Cipher mode
 * @param mode2 - Encrypt mode (1 = encrypting, 2 = decrypting)
 * @param hashkey - Key out
 * @param cipherkey - Key in
 * @return < 0 on error
 */
int sceSdCreateList(SceSdContext2 *ctx, int mode1, int mode2, unsigned char *hashkey, unsigned char *cipherkey);

/**
 * Process data for integrity check
 *
 * @param ctx - Context
 * @param data - Data (aligned to 0x10)
 * @param len - Length (aligned to 0x10)
 * @return < 0 on error
 */
int sceSdSetMember(SceSdContext2 *ctx, unsigned char *data, int len);

/**
 * Check integrity
 *
 * @param ctx - Context
 * @return < 0 on error
 */
int sceSdCleanList(SceSdContext2 *ctx);

/**@}*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PSPCHNNLSV_H__ */
