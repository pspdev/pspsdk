/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawBufferList(int psm, void* fbp, int fbw)
{
	sendCommandi(210,psm);
	sendCommandi(156,((unsigned int)fbp) & 0xffffff);
	sendCommandi(157,((((unsigned int)fbp) & 0xff000000) >> 8) | fbw);
}
