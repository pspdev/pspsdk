/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Dump the Initial Program Loader (IPL).
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * Sample program to write the contents of the Initial Program Loader (IPL)
 * from flash to a file.  The IPL is written to ms0:/ipl.bin.
 *
 * A table describing the location of the IPL is located at block offset 4
 * (physical page 128) in flash.  The table contains a list of 16-bit values
 * that point to the block offsets of the IPL itself.  The table is terminated
 * with an entry of zero.
 * 
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <pspuser.h>
#include <pspdebug.h>
#include <pspnand_driver.h>

/* Define the module info section */
PSP_MODULE_INFO("dumpipl", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(0);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

int g_iPageSize, g_iPagesPerBlock, g_iBlockSize;
int g_bFlashLocked = 0;

void LockFlash();
void UnlockFlash();
void die(const char *msg);
int ReadIPLBlockTable(void *pBlockBuf);

/* Exit callback */
int exit_callback(void)
{
	UnlockFlash();
	sceKernelExitGame();
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", (SceKernelCallbackFunction) exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();
	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, PSP_THREAD_ATTR_USER, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

void LockFlash()
{
	if (!g_bFlashLocked)
		sceNandLock(0);

	g_bFlashLocked = 1;
}

void UnlockFlash()
{
	if (g_bFlashLocked)
		sceNandUnlock();

	g_bFlashLocked = 0;
}

void die(const char *msg)
{
	UnlockFlash();

	printf("Fatal error: %s\n", msg);

	while (1)
		sceKernelSleepThread();
}

int ReadIPLBlockTable(void *pBlockBuf)
{
	u16 *pBlockTable;
	u32 uiBlockNum = 4;
	u32 uiSearchCount = 8;
	int iBlockCount;

	/* You must always get exclusive access to the flash device before reading
	   from it or writing to it. */
	LockFlash();
	memset(pBlockBuf, 0, g_iBlockSize);

	while (uiSearchCount > 0)
	{
		u32 uiPPN = uiBlockNum * g_iPagesPerBlock;

		if (!sceNandIsBadBlock(uiPPN))
		{
			if (sceNandReadBlockWithRetry(uiPPN, pBlockBuf, NULL) < 0)
			{
				die("can't read IPL block table!");
			}

			printf("Found IPL block table at block %ld\n", uiBlockNum);
			break;
		}

		uiBlockNum++;
		uiSearchCount--;
	}

	/* Count the number of blocks used by the IPL. */
	pBlockTable = (u16 *) pBlockBuf;
	iBlockCount = 0;

	while (*pBlockTable != 0)
	{
		iBlockCount++;
		pBlockTable++;
	}

	if (iBlockCount)
		printf("IPL spans a total of %d blocks.\n", iBlockCount);

	UnlockFlash();
	return iBlockCount;
}

int main(int argc, char *argv[])
{
	void *pBlockBuf;
	u16 *pBlockTable;
	int iBlockCount, iBlock;
	int fd;

	pspDebugScreenInit();
	SetupCallbacks();

	g_iPageSize = sceNandGetPageSize();
	g_iPagesPerBlock = sceNandGetPagesPerBlock();
	g_iBlockSize = g_iPageSize * g_iPagesPerBlock;

	/* Read buffer for blocks. */
	pBlockBuf = malloc(g_iBlockSize);
	assert(pBlockBuf);

	iBlockCount = ReadIPLBlockTable(pBlockBuf);
	if (!iBlockCount)
		die("IPL block count is 0!");

	pBlockTable = (u16 *) malloc(iBlockCount * sizeof(u16));
	memcpy(pBlockTable, pBlockBuf, iBlockCount * sizeof(u16));

	fd = sceIoOpen("ms0:/ipl.bin", PSP_O_WRONLY | PSP_O_CREAT, 0777);
	if (fd < 0)
		die("can't open ms0:/ipl.bin for writing!");

	/* Write out each block of the IPL. */
	for (iBlock = 0; iBlock < iBlockCount; iBlock++)
	{
		u32 uiPPN = pBlockTable[iBlock] * g_iPagesPerBlock;

		LockFlash();

		if (sceNandReadBlockWithRetry(uiPPN, pBlockBuf, NULL) < 0)
		{
			sceIoClose(fd);
			die("can't read block from IPL!\n");
		}

		UnlockFlash();

		if (sceIoWrite(fd, pBlockBuf, g_iBlockSize) < 0)
		{
			sceIoClose(fd);
			die("can't write data to file!\n");
		}
	}

	sceIoClose(fd);
	free(pBlockTable);
	free(pBlockBuf);

	printf("\nFinished writing IPL to ms0:/ipl.bin.  Use [HOME] to exit.\n");
	sceKernelSleepThread();
	return 0;
}
