/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDepthBuffer(void *zbp, int zbw)
{
#ifdef GU_DEBUG
	printf("sceGuDepthBuffer(%p, %d);\n", zbp, zbw);
	assert(gu_init && "GU not initialized");
	assert(((unsigned int)zbp & 0x1FFF) == 0 && "Depth buffer pointer must be 8192-byte aligned");
	assert(zbw > 64 && zbw <= 1024 && (zbw & 0x3F) == 0 && "Invalid depth buffer width, must be multiple of 64");
#endif

	sendCommandi(Z_BUF_PTR, ((unsigned int)zbp));
	sendCommandi(Z_BUF_WIDTH, ((((unsigned int)zbp) & 0xff000000) >> 8) | zbw);
	
	gu_draw_buffer.depth_buffer = zbp;

	if (!gu_draw_buffer.depth_width || (gu_draw_buffer.depth_width != zbw))
		gu_draw_buffer.depth_width = zbw;
}
