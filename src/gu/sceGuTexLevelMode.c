/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <math.h>

void sceGuTexLevelMode(unsigned int mode, float bias)
{
#ifdef GU_DEBUG
	printf("sceGuTexLevelMode(%08X, %f);\n", mode, bias);
	assert(gu_init && "GU not initialized");
	assert((mode == GU_TEXTURE_AUTO || mode == GU_TEXTURE_CONST || mode == GU_TEXTURE_SLOPE) && "Invalid texture level mode");
#endif

	int offset = (int)truncf(bias * 16.0f);

	// mip map bias?
	if (offset >= 128)
		offset = 128;
	else if (offset < -128)
		offset = -128;

	sendCommandi(TEX_LEVEL, (((unsigned int)(offset)) << 16) | mode);
}
