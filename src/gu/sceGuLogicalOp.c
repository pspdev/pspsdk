/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuLogicalOp(int op)
{
#ifdef GU_DEBUG
	printf("sceGuLogicalOp(%d);\n", op);
	assert(gu_init && "GU not initialized");
	assert(op >= GU_CLEAR && op <= GU_SET && "Invalid logical operation");
#endif

	sendCommandi(LOGIC_OP, op & 0x0f);
}
