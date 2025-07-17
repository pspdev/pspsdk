/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLightAtt(int light, float atten0, float atten1, float atten2)
{
#ifdef GU_DEBUG
	printf("sceGuLightAtt(%d, %f, %f, %f);\n", light, atten0, atten1, atten2);
	assert(gu_init && "GU not initialized");
	assert(light >= 0 && light <= 3 && "Invalid light index");
#endif

	int offset = light * 3;

	sendCommandf(LIGHT0_CONSTANT_ATTEN + offset, atten0);
	sendCommandf(LIGHT0_LINEAR_ATTEN + offset, atten1);
	sendCommandf(LIGHT0_QUADRATIC_ATTEN + offset, atten2);
}
