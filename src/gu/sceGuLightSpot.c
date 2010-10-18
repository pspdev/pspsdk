/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLightSpot(int light, const ScePspFVector3* direction, float exponent, float cutoff)
{
	GuLightSettings* settings = &light_settings[light];

	sendCommandf(settings->exponent,exponent);
	sendCommandf(settings->cutoff,cutoff);

	sendCommandf(settings->xdir,direction->x);
	sendCommandf(settings->ydir,direction->y);
	sendCommandf(settings->zdir,direction->z);
}
