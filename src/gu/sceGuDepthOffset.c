/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDepthOffset(unsigned int offset)
{
	GuContext* context = &gu_contexts[gu_curr_context];
	context->depth_offset = offset;

	sceGuDepthRange(context->near_plane,context->far_plane);
}
