/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspamctrl.h - Prototypes for the sceAmctrl_driver library.
 *
 * Copyright (c) 2024 GrayJack <gr41.j4ck@gmail.com>
 *
 * TODO: Contribute this header to PSPSDK
 */

#ifndef AM_CTRL_H
#define AM_CTRL_H

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


typedef struct SceMacKey {
	int type;
	u8 key[16];
	u8 pad[16];
	int pad_size;
} SceMacKey;

typedef struct SceCipherKey {
	u32 type;
	u32 seed;
	u8 key[16];
} SceCipherKey;

enum SceMacKeyType {
	MAC_KEY_TYPE_UNK0 = 0,
	MAC_KEY_TYPE_UNK1 = 1,
	/** Use fuse ID */
	MAC_KEY_TYPE_FUSE_ID = 2,
	/** Use fixed key. MAC will need to encrypt again. */
	MAC_KEY_TYPE_FIXED = 3,
	MAC_KEY_TYPE_UNK6 = 6,
};

enum SceCipherKeyType {
	/** Use fixed key */
	CIPHER_KEY_TYPE_FIXED = 1,
	/** Use fuse ID */
	CIPHER_KEY_TYPE_FUSE_ID = 2,
};

enum SceCipherKeyMode {
	CIPHER_KEY_MODE_ENCRYPT = 1,
	CIPHER_KEY_MODE_DECRYPT = 2,
};

#ifdef __KERNEL__

int sceDrmBBMacInit(SceMacKey *mac_key, int type);
int sceDrmBBMacUpdate(SceMacKey *mac_key, u8 *buf, int size);
int sceAmctrl_driver_9227EA79(SceMacKey *mac_key, u8 *buf, int size);
int sceDrmBBMacFinal(SceMacKey *mac_key, u8 *buf, u8 *version_key);
int sceDrmBBMacFinal2(SceMacKey *mac_key, u8 *buf, u8 *version_key);

int sceDrmBBCipherInit(SceCipherKey *cipher_key, int type, int mode, u8 *header_key, u8 *version_key, int seed);
int sceDrmBBCipherUpdate(SceCipherKey *cipher_key, u8 *buf, int size);
int sceAmctrl_driver_E04ADD4C(SceCipherKey *cipher_key, u8 *buf, int size);
int sceDrmBBCipherFinal(SceCipherKey *cipher_key);

#endif // __KERNEL__

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // AM_CTRL_H