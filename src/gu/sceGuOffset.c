/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuOffset(unsigned int x, unsigned int y)
{
#ifdef GU_DEBUG
	printf("sceGuOffset(%08X, %08X);\n", x, y);
	assert(gu_init && "GU not initialized");
	assert(x < 4096 && "X offset too large");
	assert(y < 4096 && "Y offset too large");
#endif

	sendCommandi(OFFSET_X, x << 4);
	sendCommandi(OFFSET_Y, y << 4);
}
