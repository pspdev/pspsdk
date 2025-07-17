/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuStencilOp(int fail, int zfail, int zpass)
{
#ifdef GU_DEBUG
	printf("sceGuStencilOp(%d, %d, %d);\n", fail, zfail, zpass);
	assert(gu_init && "GU not initialized");
	assert(fail >= GU_KEEP && fail <= GU_DECR && "Invalid stencil fail operation");
	assert(zfail >= GU_KEEP && zfail <= GU_DECR && "Invalid stencil zfail operation");
	assert(zpass >= GU_KEEP && zpass <= GU_DECR && "Invalid stencil zpass operation");
#endif

	int arg = fail | (zfail << 8) | (zpass << 16);
	sendCommandi(STENCIL_OP, arg);
}
