/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void *sceGuSetCallback(int signal, GuCallback callback)
{
#ifdef GU_DEBUG
	printf("sceGuSetCallback(%d, %p);\n", signal, callback);
	assert(gu_init && "GU not initialized");
	assert((signal == GU_CALLBACK_SIGNAL || signal == GU_CALLBACK_FINISH) && "Invalid signal");
#endif

	GuCallback old_callback = NULL;

	switch (signal)
	{
	case GU_CALLBACK_SIGNAL:
		old_callback = gu_settings.sig;
		gu_settings.sig = callback;
		break;
	case GU_CALLBACK_FINISH:
		old_callback = gu_settings.fin;
		gu_settings.fin = callback;
		break;
	}

	return old_callback;
}
