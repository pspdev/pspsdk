/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>

void callbackSig(int id, void* arg)
{
	GuSettings* settings = (GuSettings*)arg;

	settings->signal_history[(settings->signal_offset++) & 15] = id & 0xffff;

	if (settings->sig)
		settings->sig(id & 0xffff);

	sceKernelSetEventFlag(settings->kernel_event_flag,1);
}
