/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexMode(int tpsm, int maxmips, int mc, int swizzle)
{
#ifdef GU_DEBUG
	printf("sceGuTexMode(%d, %d, %d, %d);\n", tpsm, maxmips, mc, swizzle);
	assert(gu_init && "GU not initialized");
	assert((tpsm == GU_PSM_5650 || tpsm == GU_PSM_5551 || tpsm == GU_PSM_4444 || 
		tpsm == GU_PSM_8888 || tpsm == GU_PSM_T4 || tpsm == GU_PSM_T8) && "Invalid texture pixel format");
	assert(maxmips >= 0 && maxmips <= 7 && "Invalid max mipmaps");
	assert(mc >= 0 && mc <= 1 && "Invalid multiclut value");
	assert(swizzle >= 0 && swizzle <= 1 && "Invalid texture swizzle");
#endif

	GuContext *context = &gu_contexts[gu_curr_context];
	context->texture_mode = tpsm;

	sendCommandi(TEX_MODE, (maxmips << 16) | (mc << 8) | (swizzle));
	sendCommandi(TEX_FORMAT, tpsm);

	sceGuTexFlush();
}
