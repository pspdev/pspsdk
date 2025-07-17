/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLightMode(int mode)
{
#ifdef GU_DEBUG
	printf("sceGuLightMode(%d);\n", mode);
	assert(gu_init && "GU not initialized");
	assert(mode >= GU_SINGLE_COLOR && mode <= GU_SEPARATE_SPECULAR_COLOR && "Invalid light mode");
#endif

	sendCommandi(LIGHT_MODE, mode);
}
