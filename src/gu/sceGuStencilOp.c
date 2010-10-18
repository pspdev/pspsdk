/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuStencilOp(int fail, int zfail, int zpass)
{
	sendCommandi(221,fail | (zfail << 8) | (zpass << 16));
}
