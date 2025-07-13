/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuShadeModel(int mode)
{
#ifdef GU_DEBUG
	printf("sceGuShadeModel(%d);\n", mode);
	assert(gu_init && "GU not initialized");
	assert((mode == GU_FLAT || mode == GU_SMOOTH) && "Invalid shade model");
#endif

	sendCommandi(SHADE_MODE, mode);
}
