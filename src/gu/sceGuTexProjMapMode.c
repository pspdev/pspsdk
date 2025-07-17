/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexProjMapMode(int mode)
{
#ifdef GU_DEBUG
	printf("sceGuTexProjMapMode(%d);\n", mode);
	assert(gu_init && "GU not initialized");
	assert((mode == GU_POSITION || mode == GU_UV || mode == GU_NORMALIZED_NORMAL || mode == GU_NORMAL) && "Invalid texture projection map mode");
#endif

	GuContext *context = &gu_contexts[gu_curr_context];

	context->texture_proj_map_mode = ((mode & 0x03) << 8);
	sendCommandi(TEX_MAP_MODE, ((mode & 0x03) << 8) | context->texture_map_mode);
}
