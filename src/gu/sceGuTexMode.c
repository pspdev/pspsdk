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
	GuContext *context = &gu_contexts[gu_curr_context];
	context->texture_mode = tpsm;

	sendCommandi(TEX_MODE, (maxmips << 16) | (mc << 8) | (swizzle));
	sendCommandi(TEX_FORMAT, tpsm);

	sceGuTexFlush();
}
