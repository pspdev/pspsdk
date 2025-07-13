/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuPixelMask(unsigned int mask)
{
#ifdef GU_DEBUG
	printf("sceGuPixelMask(%08X);\n", mask);
	assert(gu_init && "GU not initialized");
#endif

	sendCommandi(MASK_COLOR, mask);
	sendCommandi(MASK_ALPHA, mask >> 24);
}
