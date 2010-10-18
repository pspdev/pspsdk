/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClear(int flags)
{
	GuContext* context = &gu_contexts[gu_curr_context];
	unsigned int filter;
	struct Vertex
	{
		u32 color;
		u16 x,y,z;
		u16 pad;
	};

	switch (gu_draw_buffer.pixel_size)
	{
		case 0: filter = context->clear_color & 0xffffff; break;
		case 1: filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 31); break;
		case 2: filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 28); break;
		case 3: filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 24); break;
		default: filter = 0; break;
	}

	struct Vertex* vertices;
	int count;

	if (!(flags & GU_FAST_CLEAR_BIT))
	{
		vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));
		count = 2;

		vertices[0].color = 0;
		vertices[0].x = 0;
		vertices[0].y = 0;
		vertices[0].z = context->clear_depth;

		vertices[1].color = filter;
		vertices[1].x = gu_draw_buffer.width;
		vertices[1].y = gu_draw_buffer.height;
		vertices[1].z = context->clear_depth;
	}
	else
	{
		struct Vertex* curr;
		unsigned int i;
		count = ((gu_draw_buffer.width+63)/64)*2;
		vertices = (struct Vertex*)sceGuGetMemory(count * sizeof(struct Vertex));
		curr = vertices;

		for (i = 0; i < count; ++i, ++curr)
		{
			unsigned int j,k;

			j = i >> 1;
			k = (i & 1);

			curr->color = filter;
			curr->x = (j+k) * 64;
			curr->y = k * gu_draw_buffer.height;
			curr->z = context->clear_depth;
		}
	}

	sendCommandi(211,((flags & (GU_COLOR_BUFFER_BIT|GU_STENCIL_BUFFER_BIT|GU_DEPTH_BUFFER_BIT)) << 8) | 0x01);
	sceGuDrawArray(GU_SPRITES,GU_COLOR_8888|GU_VERTEX_16BIT|GU_TRANSFORM_2D,count,0,vertices);
	sendCommandi(211,0);
}
