/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexProjMapMode(int mode)
{
	GuContext* context = &gu_contexts[gu_curr_context];

	context->texture_proj_map_mode = ((mode & 0x03) << 8);
	sendCommandi(192,((mode & 0x03) << 8) | context->texture_map_mode);
}
