/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuPatchPrim(int prim)
{
	switch (prim)
	{
	case GU_POINTS:
		sendCommandi(PATCH_PRIMITIVE, 2);
		break;
	case GU_LINE_STRIP:
		sendCommandi(PATCH_PRIMITIVE, 1);
		break;
	case GU_TRIANGLE_STRIP:
		sendCommandi(PATCH_PRIMITIVE, 0);
		break;
	}
}
