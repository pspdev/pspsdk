/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspnand_driver.h - Definitions and interfaces to the NAND (flash) driver.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@0xd6.org>
 *
 */

#ifndef PSPNAND_DRIVER_H
#define PSPNAND_DRIVER_H

#include <pspkerneltypes.h>

#ifdef __cplusplus
extern "C" {
#endif

enum PspNandDriverErrorCodes 
{
	SCE_NAND_ERROR_READ_ECCFAILED = 0x80230003,
	SCE_NAND_ERROR_READEXTRA_ECCFAILED = 0x80230009,
};

int sceNandSetWriteProtect(int protectFlag);

int sceNandLock(int writeFlag);

void sceNandUnlock(void);

int sceNandReadStatus(void);

int sceNandReset(int flag);

int sceNandReadId(void *buf, SceSize size);

int sceNandReadPages(u32 ppn, void *buf, void *spare, u32 count);

int sceNandReadExtraOnly(u32 ppn, void *buf, u32 count);

int sceNandReadPagesRawAll(u32 ppn, void *buf, void *spare, u32 count);

int sceNandReadAccess(u32 ppn, void *buf, void *spare, u32 count, u32 flags);

int sceNandWritePages(u32 ppn, void *buf, void *spare, u32 count);

int sceNandWriteAccess(u32 ppn, void *buf, void *spare, u32 count, u32 flags);

int sceNandReadAccess(u32 ppn, void *buf, void *spare, u32 count, u32 flags);

int sceNandEraseBlock(u32 ppn);

int sceNandReadExtraOnly(u32 ppn, void *spare, u32 len);

int sceNandCalcEcc(void *buf);

int sceNandVerifyEcc(void *buf, u16 ecc);

int sceNandCollectEcc(void *buf, u16 ecc); 

int sceNandGetPageSize(void);

int sceNandGetPagesPerBlock(void);

int sceNandGetTotalBlocks(void);

int sceNandWriteBlock(u32 ppn, void *buf, void *spare);

int sceNandWriteBlockWithVerify(u32 ppn, void *buf, void *spare);

int sceNandReadBlockWithRetry(u32 ppn, void *buf, void *buf2);

int sceNandVerifyBlockWithRetry(u32 ppn, void *buf, void *spare);

int sceNandEraseBlockWithRetry(u32 ppn);

int sceNandIsBadBlock(u32 ppn);

int sceNandEraseAllBlock(void);

int sceNandTestBlock(u32 ppn);

#ifdef __cplusplus
}
#endif

#endif /* PSPNAND_DRIVER_H */
