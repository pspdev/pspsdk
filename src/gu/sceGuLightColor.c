/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLightColor(int light, int component, unsigned int color)
{
	GuLightSettings* settings = &light_settings[light];

	switch (component)
	{
		case GU_AMBIENT: sendCommandi(settings->ambient, color); break;
		case GU_DIFFUSE: sendCommandi(settings->diffuse, color); break;
		case GU_AMBIENT_AND_DIFFUSE:
		{
			sendCommandi(settings->ambient, color); break;
			sendCommandi(settings->diffuse, color); break;
		}
		break;
		
		case GU_SPECULAR: sendCommandi(settings->specular, color); break;
		case GU_DIFFUSE_AND_SPECULAR:
		{
			sendCommandi(settings->diffuse, color); break;
			sendCommandi(settings->specular, color); break;
		}
		break;
	}
}
