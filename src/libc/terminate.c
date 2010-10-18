/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * terminate.c - Process exit functions.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: terminate.c 802 2005-07-30 19:38:02Z stefan $
 */
#include <stdio.h>
#include <psptypes.h>
#include <pspkernel.h>

extern void _exit(int code);

__attribute__((weak))
void abort()
{
	printf("Program aborted.\n");

	while (1)
		_exit(1);
}

__attribute__((weak))
void _Exit(int retval)
{
	while (1)
		_exit(retval);
}
