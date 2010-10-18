/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuFog(float near, float far, unsigned int color)
{
	float distance = far-near;

	if (distance)
		distance = 1.0f / distance;

	sendCommandi(207,color & 0xffffff);
	sendCommandf(205,far);
	sendCommandf(206,distance);
}
