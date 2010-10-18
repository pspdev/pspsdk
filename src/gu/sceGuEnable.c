/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuEnable(int state)
{
	switch(state)
	{
		case GU_ALPHA_TEST: sendCommandi(34,1); break;
		case GU_DEPTH_TEST: sendCommandi(35,1); break;
		case GU_SCISSOR_TEST:
		{
			GuContext* context = &gu_contexts[gu_curr_context];
			context->scissor_enable = 1;
			sendCommandi(212,(context->scissor_start[1]<<10)|context->scissor_start[0]);
			sendCommandi(213,(context->scissor_end[1]<<10)|context->scissor_end[0]);
		}
		break;
		case GU_STENCIL_TEST:	sendCommandi(36,1); break;
		case GU_BLEND:		sendCommandi(33,1); break;
		case GU_CULL_FACE:	sendCommandi(29,1); break;
		case GU_DITHER:		sendCommandi(32,1); break;
		case GU_FOG:		sendCommandi(31,1); break;
		case GU_CLIP_PLANES:	sendCommandi(28,1); break;
		case GU_TEXTURE_2D:	sendCommandi(30,1); break;
		case GU_LIGHTING:	sendCommandi(23,1); break;
		case GU_LIGHT0:		sendCommandi(24,1); break;
		case GU_LIGHT1:		sendCommandi(25,1); break;
		case GU_LIGHT2:		sendCommandi(26,1); break;
		case GU_LIGHT3:		sendCommandi(27,1); break;
		case GU_LINE_SMOOTH:	sendCommandi(37,1); break;
		case GU_PATCH_CULL_FACE:sendCommandi(38,1); break;
		case GU_COLOR_TEST:	sendCommandi(39,1); break;
		case GU_COLOR_LOGIC_OP:	sendCommandi(40,1); break;
		case GU_FACE_NORMAL_REVERSE: sendCommandi(81,1); break;
		case GU_PATCH_FACE:	sendCommandi(56,1); break;
		case GU_FRAGMENT_2X:
		{
			GuContext* context = &gu_contexts[gu_curr_context];
			context->fragment_2x = 0x10000;
			sendCommandi(201,0x10000|context->texture_function);
		}
		break;
	}

	if (state < 22)
		gu_states |= (1 << state);
}
