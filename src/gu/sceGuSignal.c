/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSignal(int signal, int argument)
{
	sendCommandi(14,((signal & 0xff) << 16) | (argument & 0xffff));
	sendCommandi(12,0);

	if (signal == 3)
	{
		sendCommandi(15,0);
		sendCommandi(12,0);
	}

	sendCommandiStall(0,0);
}
