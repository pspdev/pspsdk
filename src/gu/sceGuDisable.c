/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDisable(int state)
{
	switch(state)
	{
		case GU_ALPHA_TEST:	sendCommandi(34,0); break;
		case GU_DEPTH_TEST:	sendCommandi(35,0); break;
		case GU_SCISSOR_TEST:
		{
			GuContext* context = &gu_contexts[gu_curr_context];
			context->scissor_enable = 0;
			sendCommandi(212,0);
			sendCommandi(213,((gu_draw_buffer.height-1) << 10)|(gu_draw_buffer.width-1));
		}
		break;
		case GU_STENCIL_TEST:	sendCommandi(36,0); break;
		case GU_BLEND:		sendCommandi(33,0); break;
		case GU_CULL_FACE:	sendCommandi(29,0); break;
		case GU_DITHER:		sendCommandi(32,0); break;
		case GU_FOG:		sendCommandi(31,0); break;
		case GU_CLIP_PLANES:	sendCommandi(28,0); break;
		case GU_TEXTURE_2D:	sendCommandi(30,0); break;
		case GU_LIGHTING:	sendCommandi(23,0); break;
		case GU_LIGHT0:		sendCommandi(24,0); break;
		case GU_LIGHT1:		sendCommandi(25,0); break;
		case GU_LIGHT2:		sendCommandi(26,0); break;
		case GU_LIGHT3:		sendCommandi(27,0); break;
		case GU_LINE_SMOOTH:	sendCommandi(37,0); break;
		case GU_PATCH_CULL_FACE:sendCommandi(38,0); break;
		case GU_COLOR_TEST:	sendCommandi(39,0); break;
		case GU_COLOR_LOGIC_OP:	sendCommandi(40,0); break;
		case GU_FACE_NORMAL_REVERSE:sendCommandi(81,0); break;
		case GU_PATCH_FACE:	sendCommandi(56,0); break;
		case GU_FRAGMENT_2X:
		{
			GuContext* context = &gu_contexts[gu_curr_context];
			context->fragment_2x = 0;
			sendCommandi(201,context->texture_function);
		}
		break;
	}

	if (state < 22)
		gu_states &= ~(1 << state);
}
