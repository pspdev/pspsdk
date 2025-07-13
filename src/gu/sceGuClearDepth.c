/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClearDepth(unsigned int depth)
{
#ifdef GU_DEBUG
	printf("sceGuClearDepth(%u);\n", depth);
	assert(gu_init && "GU not initialized");
	assert(depth <= 65535 && "Invalid depth value");
#endif

	GuContext* context = &gu_contexts[gu_curr_context];
	context->clear_depth = depth;
}
