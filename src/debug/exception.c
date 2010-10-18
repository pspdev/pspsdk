/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  pspexception.c - Basic exception handler for applications.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id: exception.c 1777 2006-02-01 22:23:22Z tyranid $
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>

static PspDebugErrorHandler curr_handler = NULL;

void _pspDebugExceptionHandler(void);
PspDebugRegBlock _pspDebugExceptRegs;

int sceKernelRegisterDefaultExceptionHandler(void *func);

/* Install an error handler */
int pspDebugInstallErrorHandler(PspDebugErrorHandler handler)
{
	u32 addr;

	curr_handler = handler;

	addr = (u32) _pspDebugExceptionHandler;
	addr |= 0x80000000;

	return sceKernelRegisterDefaultExceptionHandler((void *) addr);
}

/* Mnemonic register names */
static const unsigned char regName[32][5] =
{
    "zr", "at", "v0", "v1", "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", 
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"
};

/* Taken from the ps2, might not be 100% correct */
static const char *codeTxt[32] =
{
	"Interrupt", "TLB modification", "TLB load/inst fetch", "TLB store",
	"Address load/inst fetch", "Address store", "Bus error (instr)",
	"Bus error (data)", "Syscall", "Breakpoint", "Reserved instruction",
	"Coprocessor unusable", "Arithmetic overflow", "Unknown 13", "Unknown 14",
	"FPU Exception", "Unknown 16", "Unknown 17", "Unknown 18",
	"Unknown 20", "Unknown 21", "Unknown 22", "Unknown 23",
	"Unknown 24", "Unknown 25", "Unknown 26", "Unknown 27",
	"Unknown 28", "Unknown 29", "Unknown 30", "Unknown 31"
};

/* Dump an exception to screen */
void pspDebugDumpException(PspDebugRegBlock *regs)
{
	int i;

	pspDebugScreenPrintf("Exception - %s\n", codeTxt[(regs->cause >> 2) & 31]);
	pspDebugScreenPrintf("EPC       - %08X\n", regs->epc);
	pspDebugScreenPrintf("Cause     - %08X\n", regs->cause);
	pspDebugScreenPrintf("Status    - %08X\n", regs->status);
	pspDebugScreenPrintf("BadVAddr  - %08X\n", regs->badvaddr);
	for(i = 0; i < 32; i+=4)
	{
		pspDebugScreenPrintf("%s:%08X %s:%08X %s:%08X %s:%08X\n", regName[i], regs->r[i],
				regName[i+1], regs->r[i+1], regName[i+2], regs->r[i+2], regName[i+3], regs->r[i+3]);
	}

	sceDisplayWaitVblankStart();
}

/* Our default handler in case nothing else is installed */
static void _pspDebugDefaultHandler(PspDebugRegBlock *regs)
{
	pspDebugScreenInit();
	pspDebugDumpException(regs);
}

/**
  * The entry point for our exception "trap"
  */
void _pspDebugTrapEntry(void)
{
	/* No special stack is used here, if the thread's stack is trashed we might be in trouble */
	if(curr_handler != NULL)
	{
		curr_handler(&_pspDebugExceptRegs);
	}
	else
	{
		_pspDebugDefaultHandler(&_pspDebugExceptRegs);
	}

	/* Kill this thread as we cannot necessarily continue */
	/* Technically you might be able to "restart" after something like a break */
	sceKernelExitDeleteThread(0);
}
