/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuShadeModel(int mode)
{
	switch (mode)
	{
		case 1: sendCommandi(80,1); break;
		default: sendCommandi(80,0); break;
	}
}
