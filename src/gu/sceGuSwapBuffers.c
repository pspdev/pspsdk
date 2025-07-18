/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspdisplay.h>

void *sceGuSwapBuffers(void)
{
#ifdef GU_DEBUG
	printf("sceGuSwapBuffers();\n");
	assert(gu_init && "GU not initialized");
#endif

	if (gu_settings.swapBuffersCallback)
	{
		gu_settings.swapBuffersCallback(&gu_draw_buffer.disp_buffer, &gu_draw_buffer.frame_buffer);
	}
	else
	{
		void *temp = gu_draw_buffer.disp_buffer;
		gu_draw_buffer.disp_buffer = gu_draw_buffer.frame_buffer;
		gu_draw_buffer.frame_buffer = temp;
	}

	if (gu_display_on == GU_TRUE)
		sceDisplaySetFrameBuf((void *)((unsigned int)ge_edram_address + (unsigned int)gu_draw_buffer.disp_buffer), gu_draw_buffer.frame_width, gu_draw_buffer.pixel_size, gu_settings.swapBuffersBehaviour);

	return gu_draw_buffer.frame_buffer;
}

void guSwapBuffersBehaviour(int behaviour)
{
	gu_settings.swapBuffersBehaviour = behaviour;
}

void guSwapBuffersCallback(GuSwapBuffersCallback callback)
{
	gu_settings.swapBuffersCallback = callback;
}
