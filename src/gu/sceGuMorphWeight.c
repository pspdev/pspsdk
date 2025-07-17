/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuMorphWeight(int index, float weight)
{
#ifdef GU_DEBUG
	printf("sceGuMorphWeight(%d, %f);\n", index, weight);
	assert(gu_init && "GU not initialized");
	assert(index >= 0 && index <= 7 && "Invalid morph weight index");
#endif

	sendCommandf(MORPH_WEIGHT0 + index, weight);
}
