/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuCallList(const void *list)
{
	unsigned int list_addr = (unsigned int)list;

	if (gu_call_mode == 1)
	{
		sendCommandi(SIGNAL, (list_addr >> 16) | 0x110000);
		sendCommandi(END, list_addr & 0xffff);
		sendCommandiStall(NOP, 0);
	}
	else
	{
		sendCommandi(BASE, (list_addr >> 8) & 0xf0000);
		sendCommandiStall(CALL, list_addr & 0xffffff);
	}
}
