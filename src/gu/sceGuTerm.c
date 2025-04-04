/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include <pspgu.h>

#include <pspkernel.h>
#include <pspge.h>

// To avoid including whole headers
int sceKernelDeleteEventFlag(int evid);

void sceGuTerm(void)
{
	sceKernelDeleteEventFlag(gu_settings.kernel_event_flag);
	sceGeUnsetCallback(gu_settings.ge_callback_id);
}
