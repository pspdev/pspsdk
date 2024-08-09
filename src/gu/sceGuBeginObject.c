/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuBeginObject(int vertex_type, int a1, const void *indices, const void *vertices)
{
	if (vertex_type)
		sendCommandi(VERTEX_TYPE, vertex_type);

	if (indices)
	{
		sendCommandi(BASE, (((unsigned int)indices) >> 8) & 0xf0000);
		sendCommandi(IADDR, ((unsigned int)indices) & 0xffffff);
	}

	if (vertices)
	{
		sendCommandi(BASE, (((unsigned int)vertices) >> 8) & 0x0f0000);
		sendCommandi(VADDR, ((unsigned int)vertices) & 0xffffff);
	}

	sendCommandi(BOUNDING_BOX, a1);

	// store start to new object

	gu_object_stack[gu_object_stack_depth++] = gu_list->current;

	// dummy commands, overwritten in sceGuEndObject()
	sendCommandi(BASE, 0);
	sendCommandi(BJUMP, 0);
}
