/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuColorFunc(int func, unsigned int color, unsigned int mask)
{
#ifdef GU_DEBUG
	printf("sceGuColorFunc(%d, 0x%08X, 0x%08X);\n", func, color, mask);
	assert(gu_init && "GU not initialized");
	assert(func >= GU_NEVER && func <= GU_NOTEQUAL && "Invalid color function");
#endif

	sendCommandi(COLOR_TEST, func & 0x03);
	sendCommandi(COLOR_REF, color);
	sendCommandi(COLOR_TESTMASK, mask);
}
