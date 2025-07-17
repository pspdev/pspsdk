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
#ifdef GU_DEBUG
	printf("sceGuFog(%f, %f, %08X);\n", near, far, color);
	assert(gu_init && "GU not initialized");
	assert(near >= 0.0f && "Invalid fog near value");
	assert(far > near && "Fog far must be greater than near");
	assert(far <= 65535.0f && "Fog far value too large");
#endif

	float distance = far - near;

	if (distance)
		distance = 1.0f / distance;

	sendCommandi(FOG_COLOR, color);
	sendCommandf(FOG1, far);
	sendCommandf(FOG2, distance);
}
