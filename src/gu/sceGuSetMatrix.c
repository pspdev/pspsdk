/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSetMatrix(int type, const ScePspFMatrix4* matrix)
{
	unsigned int i,j;
	const float* fmatrix = (const float*)matrix;

	switch (type)
	{
		case 0:
		{
			sendCommandf(62,0);

			// 4*4 - most probably projection
			for (i = 0; i < 16; ++i)
				sendCommandf(63,fmatrix[i]);
		}
		break;

		case 1:
		{
			sendCommandf(60,0);

			// 4*4 -> 3*4 - view matrix?
			for (i = 0; i < 4; ++i)
			{
				for (j = 0; j < 3; ++j)
					sendCommandf(61,fmatrix[j+i*4]);
			}
		}
		break;

		case 2:
		{
			sendCommandf(58,0);

			// 4*4 -> 3*4 - ???
			for (i = 0; i < 4; ++i)
			{
				for (j = 0; j < 3; ++j)
					sendCommandf(59,fmatrix[j+i*4]);
			}
		}
		break;

		case 3:
		{
			sendCommandf(64,0);

			// 4*4 -> 3*4 - ???
			for (i = 0; i < 4; ++i)
			{
				for (j = 0; j < 3; ++j)
					sendCommandf(65,fmatrix[j+i*4]);
			}
		}
		break;
	}
}
