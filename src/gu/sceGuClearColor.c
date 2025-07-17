/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClearColor(unsigned int color)
{
#ifdef GU_DEBUG
	printf("sceGuClearColor(0x%08X);\n", color);
	assert(gu_init && "GU not initialized");
#endif

	GuContext* context = &gu_contexts[gu_curr_context];
	context->clear_color = color;
}
