/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuEndObject(void)
{
	// rewrite commands from sceGuBeginObject()

	unsigned int* current = gu_list->current;
	gu_list->current = gu_object_stack[gu_object_stack_depth-1];

	sendCommandi(16, (((unsigned int)current) >> 8) & 0xf0000);
	sendCommandi(9, ((unsigned int)current) & 0xffffff);
	gu_list->current = current;

	gu_object_stack_depth--;
}
