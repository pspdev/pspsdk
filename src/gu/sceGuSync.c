/*
 * PSP Software Development Kit - https://github.com/pspdev
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
	case GU_SYNC_FINISH:
		return sceGeDrawSync(what);
	case GU_SYNC_LIST:
		return sceGeListSync(ge_list_executed[0], what);
	case GU_SYNC_SEND:
		return sceGeListSync(ge_list_executed[1], what);
	default:
	case GU_SYNC_SIGNAL:
	case GU_SYNC_DONE:
		return 0;
	}
}
