/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspdisplay.h>

int sceGuDisplay(int state)
{
	if (state)
		sceDisplaySetFrameBuf((void*)((unsigned int)ge_edram_address+(unsigned int)gu_draw_buffer.disp_buffer),gu_draw_buffer.frame_width,gu_draw_buffer.pixel_size,PSP_DISPLAY_SETBUF_NEXTFRAME);
	else
		sceDisplaySetFrameBuf(0,0,0,PSP_DISPLAY_SETBUF_NEXTFRAME);

	gu_display_on = state;
	return state;
}
