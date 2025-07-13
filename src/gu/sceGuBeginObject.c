/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuBeginObject(int vertex_type, int count, const void *indices, const void *vertices)
{
#ifdef GU_DEBUG
	printf("sceGuBeginObject(%d, %d, %p, %p);\n", vertex_type, count, indices, vertices);
	assert(gu_init && "GU not initialized");
	assert(count > 0 && count <= 255 && (count % 8) == 0 && "Invalid vertex count - must be positive, <= 65535, and multiple of 8");
	assert(gu_object_stack_depth < GU_OBJECT_STACK_SIZE && "Object stack overflow");
#endif

	if (vertex_type)
		sendCommandi(VERTEX_TYPE, vertex_type);

	if (indices)
	{
		sendCommandi(BASE, (((unsigned int)indices) >> 8) & 0xf0000);
		sendCommandi(IADDR, ((unsigned int)indices));
	}

	if (vertices)
	{
		sendCommandi(BASE, (((unsigned int)vertices) >> 8) & 0x0f0000);
		sendCommandi(VADDR, ((unsigned int)vertices));
	}

	sendCommandi(BOUNDING_BOX, count);

	// store start to new object

	gu_object_stack[gu_object_stack_depth++] = gu_list->current;

	// dummy commands, overwritten in sceGuEndObject()
	sendCommandi(BASE, 0);
	sendCommandi(BJUMP, 0);
}
