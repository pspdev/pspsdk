/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void* sceGuSetCallback(int signal, GuCallback callback)
{
	GuCallback old_callback = 0;

	switch (signal)
	{
		case GU_CALLBACK_SIGNAL:
		{
			old_callback = gu_settings.sig;
			gu_settings.sig = callback;
		}
		break;

		case GU_CALLBACK_FINISH:
		{
			old_callback = gu_settings.fin;
			gu_settings.fin = callback;
		}
		break;
	}

	return old_callback;
}
