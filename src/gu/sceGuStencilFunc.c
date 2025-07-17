/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuStencilFunc(int func, int ref, int mask)
{
#ifdef GU_DEBUG
	printf("sceGuStencilFunc(%d, %d, %d);\n", func, ref, mask);
	assert(gu_init && "GU not initialized");
	assert(func >= GU_NEVER && func <= GU_GEQUAL && "Invalid stencil function");
	assert(ref >= 0 && ref <= 255 && "Invalid stencil reference");
	assert(mask >= 0 && mask <= 255 && "Invalid stencil mask");
#endif

	int arg = func | ((ref & 0xff) << 8) | ((mask & 0xff) << 16);
	sendCommandi(STENCIL_TEST, arg);
}
