/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

int sceGuGetStatus(int state)
{
	if (state < 22)
		return (gu_states >> state) & 1;
	return 0;
}
