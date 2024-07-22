/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuViewport(int cx, int cy, int width, int height)
{
	sendCommandf(VIEWPORT_X_SCALE, (float)(width >> 1));
	sendCommandf(VIEWPORT_Y_SCALE, (float)((-height) >> 1));
	sendCommandf(VIEWPORT_X_CENTER, (float)cx);
	sendCommandf(VIEWPORT_Y_CENTER, (float)cy);
}
