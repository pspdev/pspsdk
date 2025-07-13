/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuColorMaterial(int components)
{
#ifdef GU_DEBUG
	printf("sceGuColorMaterial(%d);\n", components);
	assert(gu_init && "GU not initialized");
	assert((components >= 0) && ((components & ~(GU_AMBIENT | GU_DIFFUSE | GU_SPECULAR)) == 0) && "Invalid material components");
#endif

	sendCommandi(MATERIAL_COLOR, components);
}
