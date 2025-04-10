/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

int sceGuFinishId(unsigned int id)
{
	switch (gu_curr_context)
	{
	case GU_DIRECT:
	case GU_SEND:
	{
		sendCommandi(FINISH, id & 0xffff);
		sendCommandiStall(END, 0);
	}
	break;

	case GU_CALL:
	{
		if (gu_call_mode == 1)
		{
			sendCommandi(SIGNAL, 0x120000);
			sendCommandi(END, 0);
			sendCommandiStall(NOP, 0);
		}
		else
		{
			sendCommandi(RET, 0);
		}
	}
	break;
	}

	unsigned int size = ((unsigned int)gu_list->current) - ((unsigned int)gu_list->start);

	// go to parent list
	gu_curr_context = gu_list->parent_context;
	gu_list = &gu_contexts[gu_curr_context].list;
	return size;
}

int sceGuFinish(void)
{
	return sceGuFinishId(0);
}
