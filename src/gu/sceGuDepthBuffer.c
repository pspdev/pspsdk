/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDepthBuffer(void* zbp, int zbw)
{
	gu_draw_buffer.depth_buffer = zbp;

	if (!gu_draw_buffer.depth_width || (gu_draw_buffer.depth_width != zbw))
		gu_draw_buffer.depth_width = zbw;

	sendCommandi(158,((unsigned int)zbp) & 0xffffff);
	sendCommandi(159,((((unsigned int)zbp) & 0xff000000) >> 8)|zbw);
}
