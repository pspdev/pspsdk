/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuCopyImage(int psm, int sx, int sy, int width, int height, int srcw, void *src, int dx, int dy, int destw, void *dest)
{
	sendCommandi(TRANSFER_SRC, ((unsigned int)src));
	sendCommandi(TRANSFER_SRC_W, ((((unsigned int)src) & 0xff000000) >> 8) | srcw);
	sendCommandi(TRANSFER_SRC_OFFSET, (sy << 10) | sx);
	sendCommandi(TRANSFER_DST, ((unsigned int)dest));
	sendCommandi(TRANSFER_DST_W, ((((unsigned int)dest) & 0xff000000) >> 8) | destw);
	sendCommandi(TRANSFER_DST_OFFSET, (dy << 10) | dx);
	sendCommandi(TRANSFER_SIZE, ((height - 1) << 10) | (width - 1));
	sendCommandi(TRANSFER_START, (psm ^ 0x03) ? 0 : 1);
}
