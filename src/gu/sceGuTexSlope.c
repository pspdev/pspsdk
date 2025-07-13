/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexSlope(float slope)
{
#ifdef GU_DEBUG
	printf("sceGuTexSlope(%f);\n", slope);
	assert(gu_init && "GU not initialized");
#endif

	sendCommandf(TEX_LOD_SLOPE, slope);
}
