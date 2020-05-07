/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuAmbientColor(unsigned int color)
{
	sendCommandi(85,color & 0xffffff);
	sendCommandi(88,color >> 24);
}
