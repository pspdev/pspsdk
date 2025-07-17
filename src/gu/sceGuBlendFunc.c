/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuBlendFunc(int op, int src, int dest, unsigned int srcfix, unsigned int destfix)
{
#ifdef GU_DEBUG
	printf("sceGuBlendFunc(%d, %d, %d, 0x%08X, 0x%08X);\n", op, src, dest, srcfix, destfix);
	assert(gu_init && "GU not initialized");
	assert(op >= GU_ADD && op <= GU_ABS && "Invalid blend operation");
	assert(src >= GU_OTHER_COLOR && src <= GU_FIX && "Invalid source blend factor");
	assert(dest >= GU_OTHER_COLOR && dest <= GU_FIX && "Invalid destination blend factor");
#endif

	sendCommandi(BLEND_MODE, src | (dest << 4) | (op << 8));
	sendCommandi(BLEND_FIXED_A, srcfix);
	sendCommandi(BLEND_FIXED_B, destfix);
}
