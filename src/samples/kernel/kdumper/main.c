/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - KDumper sample, demonstrates use of kernel mode.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section, note the 0x1000 flag to enable start in kernel mode */
PSP_MODULE_INFO("SDKTEST", 0x1000, 1, 1);

/* Define the thread attribute as 0 so that the main thread does not get converted to user mode */
PSP_MAIN_THREAD_ATTR(0);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	sceKernelExitGame();

	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	/* Note the use of THREAD_ATTR_USER to ensure the callback thread is in user mode */
	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

/* Dump the cop0 regs, good proof we are in kernel mode */
void dump_cop0_regs(void)
{
	u32 regs[32];
	int i;

	asm __volatile__ (
		"mfc0 $3, $0\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $1\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $2\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $3\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $4\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $5\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $6\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $7\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $8\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $9\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $10\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $11\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $12\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $13\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $14\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $15\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $16\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $17\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $18\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $19\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $20\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $21\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $22\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $23\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $24\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $25\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $26\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $27\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $28\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $29\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $30\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		"mfc0 $3, $31\n"
		"sw $3, 0(%0)\n"
		"addi %0, %0, 4\n"
		:
		: "r"(&regs[0])
	);

	printf("Cop0 regs\n");
	for(i = 0; i < 32; i+=4)
	{
		printf("$%02d: %08X, $%02d: %08X, $%02d: %08X $%02d: %08X\n", 
				i, regs[i], i+1, regs[i+1], i+2, regs[i+2], i+3, regs[i+3]);
	}
}

char g_data[0x400000] __attribute__((aligned(64)));

/* Well what would you expect ? :) */
void dump_memregion(const char* file, void *addr, int len)
{
	int fd;

	fd = sceIoOpen(file, PSP_O_CREAT | PSP_O_TRUNC | PSP_O_WRONLY, 0777);
	if(fd >= 0)
	{
		printf("Writing %s\n", file);
		memcpy(g_data, addr, len);
		sceIoWrite(fd, g_data, len);
		sceIoClose(fd);
	}
}

int main(void)
{
	pspDebugScreenInit();
	SetupCallbacks();

	printf("Kernel mem dumper. TyRaNiD 2k5.\n");
	printf("Props to nem, mrbrown, adresd et al\n\n");
	dump_cop0_regs();
	printf("Dumping Boot Mem 0xBFC00000 -> 0xBFD00000\n");
	dump_memregion("ms0:/boot.bin", (void*) 0xBFC00000, 0x100000);
	printf("Dumping Kernel Mem 0x88000000 -> 0x883FFFFF\n");
	dump_memregion("ms0:/kmem.bin", (void*) 0x88000000, 0x400000);
	printf("Done\n");

	/* Exit the thread, this will allow the exit callback to work */
	sceKernelExitDeleteThread(0);

	return 0;
}
