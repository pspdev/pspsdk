/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLightAtt(int light, float atten0, float atten1, float atten2)
{
	GuLightSettings* settings = &light_settings[light];

	sendCommandf(settings->constant,atten0);
	sendCommandf(settings->linear,atten1);
	sendCommandf(settings->quadratic,atten2);
}
