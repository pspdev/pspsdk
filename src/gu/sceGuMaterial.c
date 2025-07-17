/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuMaterial(int mode, int color)
{
#ifdef GU_DEBUG
	printf("sceGuMaterial(%d, %08X);\n", mode, color);
	assert(gu_init && "GU not initialized");
	assert(mode >= 0 && "Invalid material mode");
	assert((mode & ~(GU_AMBIENT | GU_DIFFUSE | GU_SPECULAR)) == 0 && "Invalid material mode flags");
#endif

	if (mode & GU_AMBIENT) {
		sendCommandi(AMBIENT_COLOR, color);
		sendCommandi(AMBIENT_ALPHA, color >> 24);
	}

	if (mode & GU_DIFFUSE)
		sendCommandi(MATERIAL_DIFFUSE, color);

	if (mode & GU_SPECULAR)
		sendCommandi(MATERIAL_SPECULAR, color);
}
