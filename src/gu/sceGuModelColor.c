/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuModelColor(unsigned int emissive, unsigned int ambient, unsigned int diffuse, unsigned int specular)
{
	sendCommandi(MATERIAL_EMISSIVE, emissive & 0xffffff);
	sendCommandi(MATERIAL_DIFFUSE, diffuse & 0xffffff);
	sendCommandi(AMBIENT_COLOR, ambient & 0xffffff);
	sendCommandi(MATERIAL_SPECULAR, specular & 0xffffff);
}
