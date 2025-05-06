/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuPatchDivide(unsigned int ulevel, unsigned int vlevel)
{
	sendCommandi(PATCH_DIVISION, (vlevel << 8) | ulevel);
}
