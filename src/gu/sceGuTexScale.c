/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexScale(float u, float v)
{
#ifdef GU_DEBUG
	printf("sceGuTexScale(%f, %f);\n", u, v);
	assert(gu_init && "GU not initialized");
#endif

	sendCommandf(TEX_SCALE_U, u);
	sendCommandf(TEX_SCALE_V, v);
}
