/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspge.h>

int sceGuSendList(int mode, const void *list, PspGeContext *context)
{
#ifdef GU_DEBUG
	printf("sceGuSendList(%d, %p, %p);\n", mode, list, context);
	assert(gu_init && "GU not initialized");
	assert((mode == GU_HEAD || mode == GU_TAIL) && "Invalid list mode");
#endif

	PspGeListArgs args;
	int list_id;
	int callback;

	args.size = sizeof(PspGeListArgs);
	args.context = context;
	args.numStacks = 0;
	args.stacks = NULL;

	callback = gu_settings.ge_callback_id;
	gu_settings.signal_offset = 0;
	list_id = -1;

	switch (mode)
	{
	case GU_HEAD:
		list_id = sceGeListEnQueueHead(list, NULL, callback, &args);
		break;
	case GU_TAIL:
		list_id = sceGeListEnQueue(list, NULL, callback, &args);
		break;
	}

	if (list_id < 0)
	{
		return list_id;
	}

	ge_list_executed[1] = list_id;
	return 0;
}
