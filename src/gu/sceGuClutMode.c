/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClutMode(unsigned int cpsm, unsigned int shift, unsigned int mask, unsigned int a3)
{
	unsigned int argument = (cpsm) | (shift << 2) | (mask << 8) | (a3 << 16);
	sendCommandi(197,argument);
}
