/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * kprintf.c - Basic Kprintf handling for applications. 
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id: kprintf.c 1095 2005-09-27 21:02:16Z jim $
 */

#include <pspkernel.h>
#include <pspdebug.h>

/* The current kprintf handler */
static PspDebugKprintfHandler curr_handler;

int sceKernelRegisterKprintfHandler(void *func, void *args);

/* Default kprintf handler */
static void _pspDebugDefaultKprintfHandler(const char *format, u32 *args)
{
	pspDebugScreenPrintf(format, args[0], args[1], args[2], args[3]);
}

/* The registered kprintf handler */
static void _pspDebugKprintfHandler(void *arg, const char *format, u32 *args)
{
	if(curr_handler != NULL)
	{
		curr_handler(format, args);
	}
	else
	{
		_pspDebugDefaultKprintfHandler(format, args);
	}
}

/* Install a kprintf handler */
int pspDebugInstallKprintfHandler(PspDebugKprintfHandler handler)
{
	curr_handler = handler;
	return sceKernelRegisterKprintfHandler(_pspDebugKprintfHandler, NULL);
}
