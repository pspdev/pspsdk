/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspge.h>

int sceGuSync(int mode, int what)
{
#ifdef GU_DEBUG
	printf("sceGuSync(%d, %d);\n", mode, what);
	assert(gu_init && "GU not initialized");
	assert((mode == GU_SYNC_FINISH || mode == GU_SYNC_LIST || mode == GU_SYNC_SEND || mode == GU_SYNC_SIGNAL || mode == GU_SYNC_DONE) && "Invalid sync mode");
	assert((what == GU_SYNC_WAIT || what == GU_SYNC_NOWAIT) && "Invalid sync what");	
#endif

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
