/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <math.h>

void sceGuTexLevelMode(unsigned int mode, float bias)
{
	int offset = (int)truncf(bias * 16.0f);

	// mip map bias?
	if (offset >= 128)
		offset = 128;
	else if (offset < -128)
		offset = -128;

	sendCommandi(200,(((unsigned int)(offset)) << 16) | mode);
}
