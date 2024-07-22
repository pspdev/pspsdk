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
	if (mode & 0x01)
	{
		sendCommandi(AMBIENT_COLOR, color & 0xffffff);
		sendCommandi(AMBIENT_ALPHA, color >> 24);
	}

	if (mode & 0x02)
		sendCommandi(MATERIAL_DIFFUSE, color & 0xffffff);

	if (mode & 0x04)
		sendCommandi(MATERIAL_SPECULAR, color & 0xffffff);
}
