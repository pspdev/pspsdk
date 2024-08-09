/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuColorFunc(int func, unsigned int color, unsigned int mask)
{
	sendCommandi(COLOR_TEST, func & 0x03);
	sendCommandi(COLOR_REF, color & 0xffffff);
	sendCommandi(COLOR_TESTMASK, mask);
}
