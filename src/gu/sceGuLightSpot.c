/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLightSpot(int light, const ScePspFVector3 *direction, float exponent, float cutoff)
{
#ifdef GU_DEBUG
	printf("sceGuLightSpot(%d, %p, %f, %f);\n", light, direction, exponent, cutoff);
	assert(gu_init && "GU not initialized");
	assert(light >= 0 && light <= 3 && "Invalid light index");
#endif

	int offset = light * 3;
	sendCommandf(LIGHT0_EXPONENT_ATTEN + light, exponent);
	sendCommandf(LIGHT0_CUTOFF_ATTEN + light, cutoff);

	sendCommandf(LIGHT0_DIRECTION_X + offset, direction->x);
	sendCommandf(LIGHT0_DIRECTION_Y + offset, direction->y);
	sendCommandf(LIGHT0_DIRECTION_Z + offset, direction->z);
}
