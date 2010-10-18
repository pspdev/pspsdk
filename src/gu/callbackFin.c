/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void callbackFin(int id, void* arg)
{
	GuSettings* settings = (GuSettings*)arg;
	if (settings->fin)
		settings->fin(id & 0xffff);
}
