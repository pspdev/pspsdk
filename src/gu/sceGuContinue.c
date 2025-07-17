/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

int sceGuContinue(void)
{
#ifdef GU_DEBUG
	printf("sceGuContinue();\n");
	assert(gu_init && "GU not initialized");
#endif
	return sceGeContinue();
}
