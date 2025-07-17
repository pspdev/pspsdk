/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexSync()
{
#ifdef GU_DEBUG
	printf("sceGuTexSync();\n");
	assert(gu_init && "GU not initialized");
#endif

	sendCommandi(TEX_SYNC, 0);
}
