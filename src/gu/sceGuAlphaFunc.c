/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuAlphaFunc(int a0, int a1, int a2)
{
	int arg = a0 | ((a1 & 0xff) << 8) | ((a2 & 0xff) << 16);
	sendCommandi(219,arg);
}
