/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuAlphaFunc(int func, int value, int mask)
{
#ifdef GU_DEBUG
	printf("sceGuAlphaFunc(%d, %d, %d);\n", func, value, mask);
	assert(gu_init && "GU not initialized");
	assert(func >= GU_NEVER && func <= GU_GEQUAL && "Invalid alpha function");
#endif

	int arg = func | ((value & 0xff) << 8) | ((mask & 0xff) << 16);
	sendCommandi(ALPHA_TEST, arg);
}
