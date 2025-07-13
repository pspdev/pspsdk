/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSetAllStatus(int status)
{
#ifdef GU_DEBUG
	printf("sceGuSetAllStatus(%d);\n", status);
	assert(gu_init && "GU not initialized");
#endif

	unsigned int i;
	for (i = 0; i < GU_MAX_STATUS; ++i)
	{
		if ((status >> i) & 1)
			sceGuEnable(i);
		else
			sceGuDisable(i);
	}
}
