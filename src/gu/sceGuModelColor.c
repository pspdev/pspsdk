/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuModelColor(unsigned int emissive, unsigned int ambient, unsigned int diffuse, unsigned int specular)
{
	sendCommandi(84, emissive & 0xffffff);
	sendCommandi(86, diffuse & 0xffffff);
	sendCommandi(85, ambient & 0xffffff);
	sendCommandi(87, specular & 0xffffff);
}
