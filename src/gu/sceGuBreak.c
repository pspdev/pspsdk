/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "pspge.h"

int sceGuBreak(int mode)
{
	PspGeBreakParam bParam;
	return sceGeBreak(mode, &bParam);
}
