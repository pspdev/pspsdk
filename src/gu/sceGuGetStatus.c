/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

int sceGuGetStatus(int state)
{
	if (state < GU_MAX_STATUS)
		return (gu_states >> state) & 1;
	return 0;
}
