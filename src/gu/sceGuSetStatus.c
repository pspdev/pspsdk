/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSetStatus(int state, int status)
{
#ifdef GU_DEBUG
	printf("sceGuSetStatus(%d, %d);\n", state, status);
	assert(gu_init && "GU not initialized");
	assert(state >= 0 && state < GU_MAX_STATUS && "Invalid state");
	assert((status == 0 || status == 1) && "Invalid status");
#endif

	if (status)
		sceGuEnable(state);
	else
		sceGuDisable(state);
}
