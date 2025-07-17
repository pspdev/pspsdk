/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexFilter(int min, int mag)
{
#ifdef GU_DEBUG
	printf("sceGuTexFilter(%d, %d);\n", min, mag);
	assert(gu_init && "GU not initialized");
	assert(min >= GU_NEAREST && min <= GU_LINEAR_MIPMAP_LINEAR && "Invalid minification filter");
	assert(mag >= GU_NEAREST && mag <= GU_LINEAR && "Invalid magnification filter");
#endif

	int arg = min | (mag << 8);
	sendCommandi(TEX_FILTER, arg);
}
