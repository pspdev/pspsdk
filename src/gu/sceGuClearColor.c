/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClearColor(unsigned int color)
{
	GuContext* context = &gu_contexts[gu_curr_context];
	context->clear_color = color;
}
