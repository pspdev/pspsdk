/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexOffset(float u, float v)
{
	sendCommandf(TEX_OFFSET_U, u);
	sendCommandf(TEX_OFFSET_V, v);
}
