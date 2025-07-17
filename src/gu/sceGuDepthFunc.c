/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDepthFunc(int function)
{
#ifdef GU_DEBUG
	printf("sceGuDepthFunc(%d);\n", function);
	assert(gu_init && "GU not initialized");
	assert(function >= GU_NEVER && function <= GU_GEQUAL && "Invalid depth function");
#endif

	sendCommandi(Z_TEST, function);
}
