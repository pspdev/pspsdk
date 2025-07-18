/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuBoneMatrix(unsigned int index, const ScePspFMatrix4 *matrix)
{
#ifdef GU_DEBUG
	printf("sceGuBoneMatrix(%d, %p);\n", index, matrix);
	assert(gu_init && "GU not initialized");
	assert(index < 8 && "Invalid bone matrix index");
#endif

	unsigned int offset = ((index << 1) + index) << 2; // 3*4 matrix
	unsigned int i, j;
	const float *fmatrix = (const float *)matrix;

	sendCommandi(BONE_MATRIX_NUMBER, offset);
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			sendCommandf(BONE_MATRIX_DATA, fmatrix[j + (i << 2)]);
		}
	}
}
