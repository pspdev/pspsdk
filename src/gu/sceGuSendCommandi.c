/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSendCommandi(int cmd, int argument)
{
#ifdef GU_DEBUG
	assert(gu_init && "GU not initialized");
#endif

	sendCommandi(cmd, argument);
}
