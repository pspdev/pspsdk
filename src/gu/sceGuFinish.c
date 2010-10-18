/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

int sceGuFinish(void)
{
	switch (gu_curr_context)
	{
		case GU_DIRECT:
		case GU_SEND:
		{
			sendCommandi(15,0);
			sendCommandiStall(12,0);
		}
		break;

		case GU_CALL:
		{
			if (gu_call_mode == 1)
			{
				sendCommandi(14,0x120000);
				sendCommandi(12,0);
				sendCommandiStall(0,0);
			}
			else
			{
				sendCommandi(11,0);
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

int sceGuFinishId(unsigned int id)
{
	switch (gu_curr_context)
	{
		case GU_DIRECT:
		case GU_SEND:
		{
			sendCommandi(15,id & 0xffff);
			sendCommandiStall(12,0);
		}
		break;

		case GU_CALL:
		{
			if (gu_call_mode == 1)
			{
				sendCommandi(14,0x120000);
				sendCommandi(12,0);
				sendCommandiStall(0,0);
			}
			else
			{
				sendCommandi(11,0);
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
