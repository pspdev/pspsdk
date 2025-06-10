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
	float sx, sy, tx, ty;
  	sx = (float)(width)  *  0.5f;
	sy = (float)(height) * -0.5f;
	tx = (float)cx;
	ty = (float)cy;
	
	sendCommandf(VIEWPORT_X_SCALE, sx);
	sendCommandf(VIEWPORT_Y_SCALE, sy);
	sendCommandf(VIEWPORT_X_CENTER, tx);
	sendCommandf(VIEWPORT_Y_CENTER, ty);
}
