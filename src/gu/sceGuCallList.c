/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

int sceGuCallList(const void *list)
{
#ifdef GU_DEBUG
	printf("sceGuCallList(%p);\n", list);
	assert(gu_init && "GU not initialized");
#endif

	int res;
	unsigned int list_addr = (unsigned int)list;

	if (gu_call_mode == GU_CALL_SIGNAL)
	{
		sendCommandi(SIGNAL, (0x11 << 16) | (list_addr >> 16));
		sendCommandi(END, list_addr & 0xffff);
	}
	else
	{
		sendCommandi(BASE, (list_addr >> 8) & 0xf0000);
		sendCommandi(CALL, list_addr);
	}

	res = _sceGuUpdateStallAddr();
	if (res < 0)
	{
		return res;
	}
	return 0;
}
