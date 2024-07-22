/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuPixelMask(unsigned int mask)
{
	sendCommandi(MASK_COLOR, mask & 0xffffff);
	sendCommandi(MASK_ALPHA, mask >> 24);
}
