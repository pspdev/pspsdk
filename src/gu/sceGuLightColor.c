/*
 * PSP Software Development Kit - http://www.pspdev.org
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
		case GU_AMBIENT: sendCommandi(settings->ambient, color & 0xffffff); break;
		case GU_DIFFUSE: sendCommandi(settings->diffuse, color & 0xffffff); break;
		case GU_AMBIENT_AND_DIFFUSE:
		{
			sendCommandi(settings->ambient, color & 0xffffff); break;
			sendCommandi(settings->diffuse, color & 0xffffff); break;
		}
		break;
		
		case GU_SPECULAR: sendCommandi(settings->specular, color & 0xffffff); break;
		case GU_DIFFUSE_AND_SPECULAR:
		{
			sendCommandi(settings->diffuse, color & 0xffffff); break;
			sendCommandi(settings->specular, color & 0xffffff); break;
		}
		break;
	}
}
