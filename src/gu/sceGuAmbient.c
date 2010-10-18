/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuAmbient(unsigned int color)
{
	sendCommandi(92,(color & 0xffffff));
	sendCommandi(93,(color >> 24));
}
