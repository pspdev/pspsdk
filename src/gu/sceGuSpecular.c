/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSpecular(float power) // specular power
{
#ifdef GU_DEBUG
	printf("sceGuSpecular(%f);\n", power);
	assert(gu_init && "GU not initialized");
#endif

	sendCommandf(MATERIAL_SPECULAR_COEF, power);
}
