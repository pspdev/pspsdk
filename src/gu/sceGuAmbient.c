/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuAmbient(unsigned int color)
{
#ifdef GU_DEBUG
	printf("sceGuAmbient(%08X);\n", color);
	assert(gu_init && "GU not initialized");
#endif

	sendCommandi(AMBIENT_LIGHT_COLOR,(color));
	sendCommandi(AMBIENT_LIGHT_ALPHA,(color >> 24));
}
