/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClutMode(unsigned int cpsm, unsigned int shift, unsigned int mask, unsigned int csa)
{
#ifdef GU_DEBUG
	printf("sceGuClutMode(%08X, %08X, %08X, %08X);\n", cpsm, shift, mask, csa);
	assert(gu_init && "GU not initialized");
	assert(cpsm >= GU_PSM_5650 && cpsm <= GU_PSM_8888 && "Invalid CLUT pixel format");
#endif

	unsigned int argument = (cpsm) | (shift << 2) | (mask << 8) | (csa << 16);
	sendCommandi(CLUT_FORMAT, argument);
}
