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

void sceGuStart(int cid, void* list)
{
	GuContext* context = &gu_contexts[cid];
	unsigned int* local_list = (unsigned int*)(((unsigned int)list) | 0x40000000);

	// setup display list

	context->list.start = local_list;
	context->list.current = local_list;
	context->list.parent_context = gu_curr_context;
	gu_list = &context->list;

	// store current context

	gu_curr_context = cid;

	if (!cid)
	{
		ge_list_executed[0] = sceGeListEnQueue(local_list,local_list,gu_settings.ge_callback_id,0);
		gu_settings.signal_offset = 0;
	}

	if (!gu_init)
	{
		static int dither_matrix[16] =
		{
			-4, 0,-3, 1,
			 2,-2, 3,-1,
			-3, 1,-4, 0,
			 3,-1, 2,-2
		};

		sceGuSetDither((ScePspIMatrix4*)dither_matrix);
		sceGuPatchDivide(16,16);
		sceGuColorMaterial(GU_AMBIENT|GU_DIFFUSE|GU_SPECULAR);

		sceGuSpecular(1.0f);
		sceGuTexScale(1.0f,1.0f);
		
		gu_init = 1;
	}

	if (!gu_curr_context)
	{
		if (gu_draw_buffer.frame_width)
		{
			sendCommandi(156, ((unsigned int)gu_draw_buffer.frame_buffer) & 0xffffff);
			sendCommandi(157, ((((unsigned int)gu_draw_buffer.frame_buffer) & 0xff000000) >> 8) | gu_draw_buffer.frame_width);
		}
	}
}
