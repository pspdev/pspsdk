/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuPatchPrim(int prim)
{
	switch(prim)
	{
		case GU_POINTS: sendCommandi(55,2); break;
		case GU_LINE_STRIP: sendCommandi(55,1); break;
		case GU_TRIANGLE_STRIP: sendCommandi(55,0); break;
	}
}
