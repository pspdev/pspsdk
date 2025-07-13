/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"
#include <pspdisplay.h>
#include <pspuser.h>

int sceGuFinishId(unsigned int id)
{
#ifdef GU_DEBUG
	printf("sceGuFinishId(%08X);\n", id);
	assert(gu_init && "GU not initialized");
#endif

	int ret;
	int intr;

	switch (gu_curr_context)
	{
	case GU_DIRECT:
		sendCommandi(FINISH, id & 0xffff);
		sendCommandi(END, 0);
		ret = _sceGuUpdateStallAddr();
		if (ret < 0)
		{
			return ret;
		}
		break;
	case GU_SEND:
		sendCommandi(FINISH, id & 0xffff);
		sendCommandi(END, 0);
		break;
	case GU_CALL:
		if (gu_call_mode == GU_CALL_SIGNAL)
		{
			sendCommandi(SIGNAL, 0x12 << 16);
			sendCommandi(END, 0);
		}
		else
		{
			sendCommandi(RET, 0);
		}
		break;
	default:
		return SCE_DISPLAY_ERROR_ARGUMENT;
	}

	unsigned int size = ((unsigned int)gu_list->current) - ((unsigned int)gu_list->start);

	// go to parent list
	intr = sceKernelCpuSuspendIntr();
	gu_curr_context = gu_list->parent_context;
	gu_list = &gu_contexts[gu_curr_context].list;
	sceKernelCpuResumeIntr(intr);
	return size;
}