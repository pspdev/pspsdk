/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspge.h>

void sceGuSendList(int mode, const void* list, PspGeContext* context)
{
	gu_settings.signal_offset = 0;

	// TODO: figure out this structure
	PspGeListArgs args;
	args.size = 8; // Size of structure?
	args.context = context;

	int list_id = 0;
	int callback = gu_settings.ge_callback_id;

	switch (mode)
	{
		case GU_HEAD: list_id = sceGeListEnQueueHead(list,0,callback,&args); break;
		case GU_TAIL: list_id = sceGeListEnQueue(list,0,callback,&args); break;
	}

	ge_list_executed[1] = list_id;
}
