/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuPatchDivide(unsigned int ulevel, unsigned int vlevel)
{
#ifdef GU_DEBUG
	printf("sceGuPatchDivide(%08X, %08X);\n", ulevel, vlevel);
	assert(gu_init && "GU not initialized");
	assert(ulevel >= 1 && ulevel <= 64 && "Invalid U level - must be between 1 and 64");
	assert(vlevel >= 1 && vlevel <= 64 && "Invalid V level - must be between 1 and 64");
#endif

	sendCommandi(PATCH_DIVISION, (vlevel << 8) | ulevel);
}
