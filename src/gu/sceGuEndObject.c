/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#define ERROR_NOT_FOUND 0x80000025

int sceGuEndObject(void)
{
	int res;

	gu_object_stack_depth--;
	if (gu_object_stack_depth < 0) {
		return -ERROR_NOT_FOUND;
	}

	unsigned int *current = gu_list->current;
	gu_list->current = gu_object_stack[gu_object_stack_depth];

	sendCommandi(BASE, (((unsigned int)current) >> 8) & 0xf0000);
	sendCommandi(BJUMP, (unsigned int)current);
	gu_list->current = current;

	if (gu_curr_context == GU_DIRECT) {
		res = _sceGuUpdateStallAddr();
		if (res < 0) {
			return res;
		}
	}

	return gu_object_stack_depth;
}
