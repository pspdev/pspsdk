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
#ifdef GU_DEBUG
	assert(gu_init && "GU not initialized");
#endif

	sceGuMaterial(GU_AMBIENT | GU_DIFFUSE | GU_SPECULAR, color);
}
