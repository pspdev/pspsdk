/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuSignal(int mode, int id)
{
	sendCommandi(SIGNAL, ((mode & 0xff) << 16) | (id & 0xffff));
	sendCommandi(END, 0);

	if (mode == GU_SIGNAL_PAUSE)
	{
		sendCommandi(FINISH, 0);
		sendCommandi(END, 0);
	}

	_sceGuUpdateStallAddr();
}