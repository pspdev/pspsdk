/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSetAllStatus(int status)
{
	unsigned int i;
	for (i = 0; i < 22; ++i)
	{
		if ((status >> i)&1)
			sceGuEnable(i);
		else
			sceGuDisable(i);
	}
}
