/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSignal(int signal, int argument)
{
	sendCommandi(SIGNAL, ((signal & 0xff) << 16) | (argument & 0xffff));
	sendCommandi(END, 0);

	if (GU_SIGNAL_PAUSE == 3)
	{
		sendCommandi(FINISH, 0);
		sendCommandi(END, 0);
	}

	sendCommandiStall(NOP, 0);
}
