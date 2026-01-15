/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspdisplay.h>

void sceGuDispBuffer(int width, int height, void *dispbp, int dispbw)
{
#ifdef GU_DEBUG
	printf("sceGuDispBuffer(%d, %d, %p, %d);\n", width, height, dispbp, dispbw);
	assert(gu_init && "GU not initialized");
	assert(((unsigned int)dispbp & 0x1F) == 0 && "Display buffer pointer must be 32-byte aligned");
	assert(dispbw >= 64 && dispbw <= 1024 && (dispbw & 0x3F) == 0 && "Display buffer width must be multiple of 64");
#endif

	gu_draw_buffer.width = width;
	gu_draw_buffer.height = height;
	gu_draw_buffer.disp_buffer = dispbp;

	if (!gu_draw_buffer.frame_width || (gu_draw_buffer.frame_width != dispbw))
		gu_draw_buffer.frame_width = dispbw;

	sceDisplaySetMode(PSP_DISPLAY_MODE_LCD, gu_draw_buffer.width, gu_draw_buffer.height);

	if (gu_display_on == GU_DISPLAY_ON)
		sceDisplaySetFrameBuf((void *)(((unsigned int)ge_edram_address) + ((unsigned int)gu_draw_buffer.disp_buffer)), dispbw, gu_draw_buffer.pixel_size, PSP_DISPLAY_SETBUF_NEXTVSYNC);
}
