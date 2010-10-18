/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexFunc(int tfx, int tcc)
{
	GuContext* context = &gu_contexts[gu_curr_context];
	context->texture_function = (tcc << 8) | tfx;

	sendCommandi(201,((tcc << 8)|tfx)|context->fragment_2x);
}
