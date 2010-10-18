/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuPixelMask(unsigned int mask)
{
	sendCommandi(232,mask & 0xffffff);
	sendCommandi(233,mask >> 24);
}
