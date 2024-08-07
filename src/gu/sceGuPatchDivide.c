/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuPatchDivide(unsigned int a0, unsigned int a1)
{
	sendCommandi(PATCH_DIVISION, (a1 << 8) | a0);
}
