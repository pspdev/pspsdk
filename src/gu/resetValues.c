/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void resetValues()
{
	unsigned int i;

	gu_init = 0;

	gu_states = 0;
	gu_current_frame = 0;
	gu_object_stack_depth = 0;

	gu_display_on = 0;
	gu_call_mode = 0;

	gu_draw_buffer.pixel_size = 1;
	gu_draw_buffer.frame_width = 0;
	gu_draw_buffer.frame_buffer = 0;
	gu_draw_buffer.disp_buffer = 0;
	gu_draw_buffer.depth_buffer = 0;
	gu_draw_buffer.depth_width = 0;
	gu_draw_buffer.width = 480;
	gu_draw_buffer.height = 272;

	for (i = 0; i < 3; ++i)
	{
		GuContext* context = &gu_contexts[i];

		context->scissor_enable = 0;
		context->scissor_start[0] = 0;
		context->scissor_start[1] = 0;
		context->scissor_end[0] = 0;
		context->scissor_end[1] = 0;

		context->near_plane = 0;
		context->far_plane = 1;

		context->depth_offset = 0;
		context->fragment_2x = 0;
		context->texture_function = 0;
		context->texture_proj_map_mode = 0;
		context->texture_map_mode = 0;
		context->sprite_mode[0] = 0;
		context->sprite_mode[1] = 0;
		context->sprite_mode[2] = 0;
		context->sprite_mode[3] = 0;
		context->clear_color = 0;
		context->clear_stencil = 0;
		context->clear_depth = 0xffff;
		context->texture_mode = 0;
	}

	gu_settings.sig = 0;
	gu_settings.fin = 0;
}
