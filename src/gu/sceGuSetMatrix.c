/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSetMatrix(int type, const ScePspFMatrix4 *matrix)
{
#ifdef GU_DEBUG
	printf("sceGuSetMatrix(%d, %p);\n", type, matrix);
	assert(gu_init && "GU not initialized");
	assert(type >= GU_PROJECTION && type <= GU_TEXTURE && "Invalid matrix type");
#endif

	unsigned int i, j;
	const float *fmatrix = (const float *)matrix;

	switch (type)
	{
	case GU_PROJECTION:
	{
		sendCommandf(PROJ_MATRIX_NUMBER, 0);

		// 4*4 - most probably projection
		for (i = 0; i < 16; ++i)
			sendCommandf(PROJ_MATRIX_DATA, fmatrix[i]);
	}
	break;

	case GU_VIEW:
	{
		sendCommandf(VIEW_MATRIX_NUMBER, 0);

		// 4*4 -> 3*4 - view matrix?
		for (i = 0; i < 4; ++i)
		{
			for (j = 0; j < 3; ++j)
				sendCommandf(VIEW_MATRIX_DATA, fmatrix[j + i * 4]);
		}
	}
	break;

	case GU_MODEL:
	{
		sendCommandf(WORLD_MATRIX_NUMBER, 0);

		// 4*4 -> 3*4 - ???
		for (i = 0; i < 4; ++i)
		{
			for (j = 0; j < 3; ++j)
				sendCommandf(WORLD_MATRIX_DATA, fmatrix[j + i * 4]);
		}
	}
	break;

	case GU_TEXTURE:
	{
		sendCommandf(TGEN_MATRIX_NUMBER, 0);

		// 4*4 -> 3*4 - ???
		for (i = 0; i < 4; ++i)
		{
			for (j = 0; j < 3; ++j)
				sendCommandf(TGEN_MATRIX_DATA, fmatrix[j + i * 4]);
		}
	}
	break;
	}
}
