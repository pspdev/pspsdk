/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspge.h>

void sceGuTerm(void)
{
#ifdef GU_DEBUG
	printf("sceGuTerm();\n");
	assert(gu_init && "GU not initialized");
	assert(gu_settings.kernel_event_flag >= 0 && "Invalid kernel event flag");
	assert(gu_settings.ge_callback_id >= 0 && "Invalid GE callback ID");
#endif

	sceKernelDeleteEventFlag(gu_settings.kernel_event_flag);
	sceGeUnsetCallback(gu_settings.ge_callback_id);
}
