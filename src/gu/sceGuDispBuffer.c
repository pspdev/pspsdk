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

void drawRegion(int x, int y, int width, int height)
{
  sendCommandi(21,(y << 10) | x);
  sendCommandi(22,(((y + height)-1) << 10) | ((x + width)-1));
}

void sceGuDispBuffer(int width, int height, void* dispbp, int dispbw)
{
	gu_draw_buffer.width = width;
	gu_draw_buffer.height = height;
	gu_draw_buffer.disp_buffer = dispbp;

	if (!gu_draw_buffer.frame_width || (gu_draw_buffer.frame_width != dispbw))
		gu_draw_buffer.frame_width = dispbw;

	drawRegion(0,0,gu_draw_buffer.width,gu_draw_buffer.height);
	sceDisplaySetMode(0,gu_draw_buffer.width,gu_draw_buffer.height);

	if (gu_display_on)
		sceDisplaySetFrameBuf((void*)(((unsigned int)ge_edram_address) + ((unsigned int)gu_draw_buffer.disp_buffer)), dispbw, gu_draw_buffer.pixel_size, PSP_DISPLAY_SETBUF_NEXTFRAME);
}
