/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuStencilFunc(int func, int ref, int mask)
{
	sendCommandi(STENCIL_TEST, func | ((ref & 0xff) << 8) | ((mask & 0xff) << 16));
}
