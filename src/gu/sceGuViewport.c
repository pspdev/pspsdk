/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuViewport(int cx, int cy, int width, int height)
{
	sendCommandf(66,(float)(width>>1));
	sendCommandf(67,(float)((-height)>>1));
	sendCommandf(69,(float)cx);
	sendCommandf(70,(float)cy);
}
