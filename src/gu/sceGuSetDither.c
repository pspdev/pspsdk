/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSetDither(const ScePspIMatrix4 *matrix)
{
#ifdef GU_DEBUG
	printf("sceGuSetDither(%p);\n", matrix);
	assert(gu_init && "GU not initialized");
#endif

	sendCommandi(DITH0, (matrix->x.x & 0x0f) | ((matrix->x.y & 0x0f) << 4) | ((matrix->x.z & 0x0f) << 8) | ((matrix->x.w & 0x0f) << 12));
	sendCommandi(DITH1, (matrix->y.x & 0x0f) | ((matrix->y.y & 0x0f) << 4) | ((matrix->y.z & 0x0f) << 8) | ((matrix->y.w & 0x0f) << 12));
	sendCommandi(DITH2, (matrix->z.x & 0x0f) | ((matrix->z.y & 0x0f) << 4) | ((matrix->z.z & 0x0f) << 8) | ((matrix->z.w & 0x0f) << 12));
	sendCommandi(DITH3, (matrix->w.x & 0x0f) | ((matrix->w.y & 0x0f) << 4) | ((matrix->w.z & 0x0f) << 8) | ((matrix->w.w & 0x0f) << 12));
}
