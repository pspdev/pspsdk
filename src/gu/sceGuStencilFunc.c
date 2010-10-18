/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuStencilFunc(int func, int ref, int mask)
{
	sendCommandi(220,func | ((ref & 0xff) << 8) | ((mask & 0xff) << 16));
}
