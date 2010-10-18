/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuMaterial(int mode, int color)
{
	if (mode & 0x01)
	{
		sendCommandi(85, color & 0xffffff);
		sendCommandi(88, color >> 24);
	}

	if (mode & 0x02)
		sendCommandi(86, color & 0xffffff);

	if (mode & 0x04)
		sendCommandi(87, color & 0xffffff);
}
