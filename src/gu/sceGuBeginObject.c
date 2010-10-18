/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuBeginObject(int vertex_type, int a1, const void* indices, const void* vertices)
{
	if (vertex_type)
		sendCommandi(18,vertex_type);

	if (indices)
	{
		sendCommandi(16,(((unsigned int)indices) >> 8) & 0xf0000);
		sendCommandi(2,((unsigned int)indices) & 0xffffff);
	}

	if (vertices)
	{
		sendCommandi(16,(((unsigned int)vertices) >> 8) & 0x0f0000);
		sendCommandi(1,((unsigned int)vertices) & 0xffffff);
	}

	sendCommandi(7,a1);

	// store start to new object

	gu_object_stack[gu_object_stack_depth++] = gu_list->current;

	// dummy commands, overwritten in sceGuEndObject()
	sendCommandi(16,0);
	sendCommandi(9,0);
}
