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
	sendCommandi(FRAMEBUF_PIX_FORMAT, psm);
	sendCommandi(FRAME_BUF_PTR, (unsigned int)fbp);
	sendCommandi(FRAME_BUF_WIDTH, ((((unsigned int)fbp) & 0xff000000) >> 8) | fbw);
}
