/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * gdb-kernellib.c - GDB support functions for kernel mode.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id: gdb-kernellib.c 1492 2005-11-26 23:19:30Z mrbrown $
 */
#include <pspkernel.h>
#include <pspdebug.h>

/* GDB Debug putchar */
void putDebugChar(char ch)
{
	pspDebugSioPutchar(ch);
}

/* GDB Debug getchar */
char getDebugChar(void)
{
	int ch = 0;

	while(1)
	{
		ch = pspDebugSioGetchar();
		if(ch != -1)
		{
			break;
		}
	}

	return ch;
}

void sceKernelDcacheWBinvAll(void);
void sceKernelIcacheClearAll(void);

void _gdbSupportLibFlushCaches(void)
{
	pspKernelSetKernelPC();
	sceKernelDcacheWBinvAll();
	sceKernelIcacheClearAll();
}

int _gdbSupportLibReadByte(unsigned char *address, unsigned char *dest)
{
	u32 addr;

	addr = (u32) address;
	if((addr >= 0x08400000) && (addr < 0x0a000000))
	{
		*dest = *address;
		return 1;
	}
	else if((addr >= 0x88000000) && (addr < 0x8a000000))
	{
		*dest = *address;
		return 1;
	}

	return 0;
}

int _gdbSupportLibWriteByte(char val, unsigned char *dest)
{
	u32 addr;

	addr = (u32) dest;
	if((addr >= 0x08400000) && (addr < 0x0a000000))
	{
		*dest = val;
		return 1;
	}
	else if((addr >= 0x88000000) && (addr < 0x8a000000))
	{
		*dest = val;
		return 1;
	}

	return 0;
}

int _gdbSupportLibInit(void)
{
	/* Do nothing */

	return 0;
}
