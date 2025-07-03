/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuViewport(float cx, float cy, float width, float height)
{
	float sx, sy;
  	sx = width  *  0.5f;
	sy = height * -0.5f;
	
	sendCommandf(VIEWPORT_X_SCALE, sx);
	sendCommandf(VIEWPORT_Y_SCALE, sy);
	sendCommandf(VIEWPORT_X_CENTER, cx);
	sendCommandf(VIEWPORT_Y_CENTER, cy);
}
