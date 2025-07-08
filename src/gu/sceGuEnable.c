/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuEnable(int state)
{
	switch (state)
	{
	case GU_ALPHA_TEST:
		sendCommandi(ALPHA_TEST_ENABLE, 1);
		break;
	case GU_DEPTH_TEST:
		sendCommandi(Z_TEST_ENABLE, 1);
		break;
	case GU_SCISSOR_TEST:
	{
		GuContext *context = &gu_contexts[gu_curr_context];
		int orig = (context->scissor_start[1] << 10) | context->scissor_start[0];
		int end = (context->scissor_end[1] << 10) | context->scissor_end[0];
		
		context->scissor_enable = 1;
		sendCommandi(SCISSOR1, orig);
		sendCommandi(SCISSOR2, end);
		sendCommandi(REGION1, 0);
		sendCommandi(REGION2, end);
	}
	break;
	case GU_STENCIL_TEST:
		sendCommandi(STENCIL_TEST_ENABLE, 1);
		break;
	case GU_BLEND:
		sendCommandi(ALPHA_BLEND_ENABLE, 1);
		break;
	case GU_CULL_FACE:
		sendCommandi(CULL_FACE_ENABLE, 1);
		break;
	case GU_DITHER:
		sendCommandi(DITHER_ENABLE, 1);
		break;
	case GU_FOG:
		sendCommandi(FOG_ENABLE, 1);
		break;
	case GU_CLIP_PLANES:
		sendCommandi(DEPTH_CLIP_ENABLE, 1);
		break;
	case GU_TEXTURE_2D:
		sendCommandi(TEXTURE_ENABLE, 1);
		break;
	case GU_LIGHTING:
		sendCommandi(LIGHTING_ENABLE, 1);
		break;
	case GU_LIGHT0:
		sendCommandi(LIGHT_ENABLE0, 1);
		break;
	case GU_LIGHT1:
		sendCommandi(LIGHT_ENABLE1, 1);
		break;
	case GU_LIGHT2:
		sendCommandi(LIGHT_ENABLE2, 1);
		break;
	case GU_LIGHT3:
		sendCommandi(LIGHT_ENABLE3, 1);
		break;
	case GU_LINE_SMOOTH:
		sendCommandi(ANTI_ALIAS_ENABLE, 1);
		break;
	case GU_PATCH_CULL_FACE:
		sendCommandi(PATCH_CULL_ENABLE, 1);
		break;
	case GU_COLOR_TEST:
		sendCommandi(COLOR_TEST_ENABLE, 1);
		break;
	case GU_COLOR_LOGIC_OP:
		sendCommandi(LOGIC_OP_ENABLE, 1);
		break;
	case GU_FACE_NORMAL_REVERSE:
		sendCommandi(NORMAL_REVERSE, 1);
		break;
	case GU_PATCH_FACE:
		sendCommandi(PATCH_FACING, 1);
		break;
	case GU_FRAGMENT_2X:
	{
		GuContext *context = &gu_contexts[gu_curr_context];
		context->fragment_2x = 0x10000;
		sendCommandi(TEX_FUNC, 0x10000 | context->texture_function);
	}
	break;
	}

	if (state < GU_MAX_STATUS)
		gu_states |= (1 << state);
}
