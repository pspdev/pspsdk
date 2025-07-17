/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexWrap(int u, int v)
{
#ifdef GU_DEBUG
	printf("sceGuTexWrap(%d, %d);\n", u, v);
	assert(gu_init && "GU not initialized");
	assert((u == GU_CLAMP || u == GU_REPEAT) && "Invalid U wrap mode");
	assert((v == GU_CLAMP || v == GU_REPEAT) && "Invalid V wrap mode");
#endif

	int arg = u | (v << 8);
	sendCommandi(TEX_WRAP, arg);
}
