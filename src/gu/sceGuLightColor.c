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

	int offset = light * 3;

	switch (component)
	{
		case GU_AMBIENT: 
			sendCommandi(LIGHT0_AMBIENT + offset, color); 
			break;
		case GU_DIFFUSE: 
			sendCommandi(LIGHT0_DIFFUSE + offset, color); 
			break;
		case GU_SPECULAR: 
			sendCommandi(LIGHT0_SPECULAR + offset, color); 
			break;
		case GU_AMBIENT_AND_DIFFUSE:
			sendCommandi(LIGHT0_AMBIENT + offset, color); 
			sendCommandi(LIGHT0_DIFFUSE + offset, color); 
			break;
		case GU_DIFFUSE_AND_SPECULAR:
			sendCommandi(LIGHT0_DIFFUSE + offset, color); 
			sendCommandi(LIGHT0_SPECULAR + offset, color); 
			break;
	}
}
