/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuCallMode(int mode)
{
#ifdef GU_DEBUG
	printf("sceGuCallMode(%d);\n", mode);
	assert(gu_init && "GU not initialized");
	assert(mode >= GU_CALL_NORMAL && mode <= GU_CALL_SIGNAL && "Invalid call mode");
#endif

	gu_call_mode = mode;
}
