/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuBlendFunc(int op, int src, int dest, unsigned int srcfix, unsigned int destfix)
{
	sendCommandi(BLEND_MODE, src | (dest << 4) | (op << 8));
	sendCommandi(BLEND_FIXED_A, srcfix & 0xffffff);
	sendCommandi(BLEND_FIXED_B, destfix & 0xffffff);
}
