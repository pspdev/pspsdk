/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDepthMask(int mask)
{
#ifdef GU_DEBUG
	printf("sceGuDepthMask(%d);\n", mask);
	assert(gu_init && "GU not initialized");
	assert((mask == 0 || mask == 1) && "Invalid depth mask");
#endif

	sendCommandi(Z_MASK, mask);
}
