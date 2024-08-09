/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClutLoad(int num_blocks, const void *cbp)
{
	sendCommandi(CLUT_ADDR, ((unsigned int)cbp) & 0xffffff);
	sendCommandi(CLUT_ADDR_UPPER, (((unsigned int)cbp) >> 8) & 0xf0000);
	sendCommandi(LOAD_CLUT, num_blocks);
}
