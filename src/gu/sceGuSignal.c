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
#ifdef GU_DEBUG
	printf("sceGuSignal(%d, %d);\n", mode, id);
	assert(gu_init && "GU not initialized");
	assert(mode >= GU_SIGNAL_WAIT && mode <= GU_SIGNAL_PAUSE && "Invalid signal mode");
	assert(id >= 0 && id <= 65535 && "Invalid signal ID, must be between 0 and 65535");
#endif

	sendCommandi(SIGNAL, ((mode & 0xff) << 16) | (id & 0xffff));
	sendCommandi(END, 0);

	if (mode == GU_SIGNAL_PAUSE)
	{
		sendCommandi(FINISH, 0);
		sendCommandi(END, 0);
	}

	_sceGuUpdateStallAddr();
}