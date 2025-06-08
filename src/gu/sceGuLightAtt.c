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
	int offset = light * 3;

	sendCommandf(LIGHT0_CONSTANT_ATTEN + offset, atten0);
	sendCommandf(LIGHT0_LINEAR_ATTEN + offset, atten1);
	sendCommandf(LIGHT0_QUADRATIC_ATTEN + offset, atten2);
}
