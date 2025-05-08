/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuColor(unsigned int color)
{
	sceGuMaterial(GU_AMBIENT | GU_DIFFUSE | GU_SPECULAR, color);
}
