/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuFrontFace(int order)
{
#ifdef GU_DEBUG
	printf("sceGuFrontFace(%d);\n", order);
	assert(gu_init && "GU not initialized");
	assert((order == GU_CW || order == GU_CCW) && "Invalid front face order");
#endif

	sendCommandi(CULL, order ? 0 : 1);
}
