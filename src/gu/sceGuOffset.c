/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuOffset(unsigned int x, unsigned int y)
{
	sendCommandi(OFFSET_X, x << 4);
	sendCommandi(OFFSET_Y, y << 4);
}
