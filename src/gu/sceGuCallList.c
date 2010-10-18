/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuCallList(const void* list)
{
	unsigned int list_addr = (unsigned int)list;

	if (gu_call_mode == 1)
	{
		sendCommandi(14,(list_addr >> 16) | 0x110000);
		sendCommandi(12,list_addr & 0xffff);
		sendCommandiStall(0,0);
	}
	else
	{
		sendCommandi(16,(list_addr >> 8) & 0xf0000);
		sendCommandiStall(10,list_addr & 0xffffff);
	}
}
