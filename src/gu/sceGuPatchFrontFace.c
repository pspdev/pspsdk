/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuPatchFrontFace(unsigned int mode)
{
#ifdef GU_DEBUG
	printf("sceGuPatchFrontFace(%u);\n", mode);
	assert(gu_init && "GU not initialized");
	assert((mode == GU_CW || mode == GU_CCW) && "Invalid patch front face mode");
#endif

	sendCommandi(PATCH_FACING, mode);
}
