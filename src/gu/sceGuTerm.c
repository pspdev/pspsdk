/*
 * PSP Software Development Kit - http://www.pspdev.org
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
	sceKernelDeleteEventFlag(gu_settings.kernel_event_flag);
	sceGeUnsetCallback(gu_settings.ge_callback_id);
}
