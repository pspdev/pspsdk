/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawBufferList(int psm, void *fbp, int fbw)
{
#ifdef GU_DEBUG
	printf("sceGuDrawBufferList(%d, %p, %d);\n", psm, fbp, fbw);
	assert(gu_init && "GU not initialized");
	assert(((unsigned int)fbp & 0x1FFF) == 0 && "Frame buffer pointer must be 8192-byte aligned");
	assert(fbw >= 64 && fbw <= 1024 && (fbw & 0x3F) == 0 && "Frame buffer width must be multiple of 64");
	assert(psm >= GU_PSM_5650 && psm <= GU_PSM_8888 && "Invalid pixel format");
#endif

	sendCommandi(FRAMEBUF_PIX_FORMAT, psm);
	sendCommandi(FRAME_BUF_PTR, (unsigned int)fbp);
	sendCommandi(FRAME_BUF_WIDTH, ((((unsigned int)fbp) & 0xff000000) >> 8) | fbw);
}
