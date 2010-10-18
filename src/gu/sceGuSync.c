/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspge.h>

int sceGuSync(int mode, int what)
{
	switch (mode)
	{
		case 0: return sceGeDrawSync(what);
		case 3: return sceGeListSync(ge_list_executed[0],what);
		case 4: return sceGeListSync(ge_list_executed[1],what);
		default: case 1: case 2: return 0;
	}
}
