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

void sendCommandi(int cmd, int argument)
{
	*(gu_list->current++) = (cmd << 24) | (argument & 0xffffff);
}

void sendCommandf(int cmd, float argument)
{
	union
	{
		float f;
		unsigned int i;
	} t;
	t.f = argument;

	sendCommandi(cmd,t.i >> 8);
}

void sendCommandiStall(int cmd, int argument)
{
	sendCommandi(cmd,argument);

	if (!gu_object_stack_depth && !gu_curr_context)
		sceGeListUpdateStallAddr(ge_list_executed[0],gu_list->current);
}
