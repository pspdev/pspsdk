/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexMapMode(int mode, unsigned int a1, unsigned int a2)
{
	GuContext* context = &gu_contexts[gu_curr_context];

	context->texture_map_mode = mode & 0x03;

	sendCommandi(192,context->texture_proj_map_mode | (mode & 0x03));
	sendCommandi(193,(a2 << 8)|(a1 & 0x03));
}
