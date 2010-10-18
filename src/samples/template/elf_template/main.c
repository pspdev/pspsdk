/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic ELF template
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: main.c 1888 2006-05-01 08:47:04Z tyranid $
 * $HeadURL$
 */
#include <pspkernel.h>
#include <pspdebug.h>

#define printf pspDebugScreenPrintf

/* Define the module info section */
PSP_MODULE_INFO("template", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main(int argc, char *argv[])
{
	pspDebugScreenInit();

	pspDebugScreenPrintf("Hello World\n");

	return 0;
}
