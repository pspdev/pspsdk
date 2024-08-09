/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuFog(float near, float far, unsigned int color)
{
	float distance = far - near;

	if (distance)
		distance = 1.0f / distance;

	sendCommandi(FOG_COLOR, color & 0xffffff);
	sendCommandf(FOG1, far);
	sendCommandf(FOG2, distance);
}
