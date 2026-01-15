/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspdisplay.h>

int sceGuDisplay(int state)
{
#ifdef GU_DEBUG
	printf("sceGuDisplay(%d);\n", state);
	assert(gu_init && "GU not initialized");
	assert((state == GU_TRUE || state == GU_FALSE) && "Invalid display state");
#endif

	if (state == GU_TRUE)
		sceDisplaySetFrameBuf((void *)((unsigned int)ge_edram_address + (unsigned int)gu_draw_buffer.disp_buffer), gu_draw_buffer.frame_width, gu_draw_buffer.pixel_size, PSP_DISPLAY_SETBUF_NEXTVSYNC);
	else
		sceDisplaySetFrameBuf(NULL, 0, 0, PSP_DISPLAY_SETBUF_NEXTVSYNC);

	gu_display_on = state;
	return state;
}

int guGetDisplayState()
{
	return gu_display_on;
}
