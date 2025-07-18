/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClear(int flags)
{
#ifdef GU_DEBUG
	printf("sceGuClear(%d);\n", flags);
	assert(gu_init && "GU not initialized");
	assert(flags >= 0 && "Invalid clear flags");
	assert((flags & ~(GU_COLOR_BUFFER_BIT | GU_STENCIL_BUFFER_BIT | GU_DEPTH_BUFFER_BIT | GU_FAST_CLEAR_BIT)) == 0 && "Invalid clear flags");
#endif

	GuContext *context = &gu_contexts[gu_curr_context];
	unsigned int filter;
	struct Vertex
	{
		u32 color;
		u16 x, y, z;
		u16 pad;
	};

	switch (gu_draw_buffer.pixel_size)
	{
	case GU_PSM_5650:
		filter = context->clear_color & 0xffffff;
		break;
	case GU_PSM_5551:
		filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 31);
		break;
	case GU_PSM_4444:
		filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 28);
		break;
	case GU_PSM_8888:
		filter = (context->clear_color & 0xffffff) | (context->clear_stencil << 24);
		break;
	default:
		filter = 0;
		break;
	}

	struct Vertex *vertices;
	int count;

	if (!(flags & GU_FAST_CLEAR_BIT))
	{
		vertices = (struct Vertex *)sceGuGetMemory(2 * sizeof(struct Vertex));
		count = 2;

		vertices[0].color = filter;
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
		struct Vertex *curr;
		unsigned int i, blockWidth;
		// Use blockWidth of 32 for 8888, 64 for other formats
		blockWidth = gu_draw_buffer.pixel_size == GU_PSM_8888 ? 32 : 64;
		count = ((gu_draw_buffer.width + blockWidth - 1) / blockWidth) * 2;
		vertices = (struct Vertex *)sceGuGetMemory(count * sizeof(struct Vertex));
		curr = vertices;

		for (i = 0; i < count; ++i, ++curr)
		{
			unsigned int j, k;

			j = i >> 1;
			k = (i & 1);

			curr->color = filter;
			curr->x = (j + k) * blockWidth;
			curr->y = k * gu_draw_buffer.height;
			curr->z = context->clear_depth;
		}
	}

	sendCommandi(CLEAR_MODE, ((flags & (GU_COLOR_BUFFER_BIT | GU_STENCIL_BUFFER_BIT | GU_DEPTH_BUFFER_BIT)) << 8) | 0x01);
	sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_VERTEX_16BIT | GU_TRANSFORM_2D, count, 0, vertices);
	sendCommandi(CLEAR_MODE, 0);
}
