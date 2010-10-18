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

void* sceGuGetMemory(int size)
{
	// some kind of 4-byte alignment?
	size += 3;
	size += ((unsigned int)(size >> 31)) >> 30;
	size = (size >> 2) << 2;

	unsigned int* orig_ptr = gu_list->current;
	unsigned int* new_ptr = (unsigned int*)(((unsigned int)orig_ptr) + size + 8);

	int lo = (8 << 24) | (((unsigned int)new_ptr) & 0xffffff);
	int hi = (16 << 24) | ((((unsigned int)new_ptr) >> 8) & 0xf0000);

	orig_ptr[0] = hi;
	orig_ptr[1] = lo;

	gu_list->current = new_ptr;

	if (!gu_curr_context)
		sceGeListUpdateStallAddr(ge_list_executed[0],new_ptr);

	return orig_ptr + 2;
}
