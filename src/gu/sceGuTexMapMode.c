/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexMapMode(int mode, unsigned int lu, unsigned int lv)
{
	GuContext *context = &gu_contexts[gu_curr_context];

	context->texture_map_mode = mode & 0x03;

	sendCommandi(TEX_MAP_MODE, context->texture_proj_map_mode | (mode & 0x03));
	sendCommandi(TEX_SHADE_MAPPING, (lu << 8) | (lv & 0x03));
}
