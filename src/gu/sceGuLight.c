/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#define LTYPE_POWERED_DIFFUSE (2)
#define LTYPE_DIFFUSE_AND_SPECULAR (1)
#define LTYPE_DIFFUSE (0)

void sceGuLight(int light, int type, int components, const ScePspFVector3 *position)
{
#ifdef GU_DEBUG
	printf("sceGuLight(%d, %d, %d, %p);\n", light, type, components, position);
	assert(gu_init && "GU not initialized");
	assert(light >= 0 && light <= 3 && "Invalid light index");
	assert(type >= GU_DIRECTIONAL && type <= GU_SPOTLIGHT && "Invalid light type");
	assert(components >= GU_AMBIENT && components <= GU_DIFFUSE_AND_SPECULAR && "Invalid light components");
#endif

	int offset = light * 3;
	int ltype;

	if (components == GU_POWERED_DIFFUSE) {
		ltype = LTYPE_POWERED_DIFFUSE;
	} else if (components == GU_DIFFUSE_AND_SPECULAR) {
		ltype = LTYPE_DIFFUSE_AND_SPECULAR;
	} else {
		ltype = LTYPE_DIFFUSE;
	}

	// Light position
	sendCommandf(LIGHT0_X + offset, position->x);
	sendCommandf(LIGHT0_Y + offset, position->y);
	sendCommandf(LIGHT0_Z + offset, position->z);
	// Light type and components
	sendCommandi(LIGHT_TYPE0 + light, ((type & GU_AMBIENT_AND_DIFFUSE) << 8) | ltype);
}
