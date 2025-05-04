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
	if (mode & GU_AMBIENT) {
		sendCommandi(AMBIENT_COLOR, color);
		sendCommandi(AMBIENT_ALPHA, color >> 24);
	}

	if (mode & GU_DIFFUSE)
		sendCommandi(MATERIAL_DIFFUSE, color);

	if (mode & GU_SPECULAR)
		sendCommandi(MATERIAL_SPECULAR, color);
}
