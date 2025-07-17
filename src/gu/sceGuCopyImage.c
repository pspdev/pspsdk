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
#ifdef GU_DEBUG
	printf("sceGuCopyImage(%d, %d, %d, %d, %d, %d, %p, %d, %d, %d, %p);\n", psm, sx, sy, width, height, srcw, src, dx, dy, destw, dest);
	assert(gu_init && "GU not initialized");
	assert(psm >= GU_PSM_5650 && psm <= GU_PSM_8888 && "Invalid pixel format");
	assert(width > 0 && width <= 1023 && "Invalid width");
	assert(height > 0 && height <= 1023 && "Invalid height");
	assert(srcw > 8 && srcw <= 1024 && (srcw & 0x7) == 0 && "Invalid source width, must be multiple of 8");
	assert(destw > 8 && destw <= 1024 && (destw & 0x7) == 0 && "Invalid destination width, must be multiple of 8");
	assert(sx >= 0 && sx < 1023 && "Invalid source X");
	assert(sy >= 0 && sy < 1023 && "Invalid source Y");
	assert(dx >= 0 && dx < 1023 && "Invalid destination X");
	assert(dy >= 0 && dy < 1023 && "Invalid destination Y");
#endif

	sendCommandi(TRANSFER_SRC, ((unsigned int)src));
	sendCommandi(TRANSFER_SRC_W, ((((unsigned int)src) & 0xff000000) >> 8) | srcw);
	sendCommandi(TRANSFER_SRC_OFFSET, (sy << 10) | sx);
	sendCommandi(TRANSFER_DST, ((unsigned int)dest));
	sendCommandi(TRANSFER_DST_W, ((((unsigned int)dest) & 0xff000000) >> 8) | destw);
	sendCommandi(TRANSFER_DST_OFFSET, (dy << 10) | dx);
	sendCommandi(TRANSFER_SIZE, ((height - 1) << 10) | (width - 1));
	sendCommandi(TRANSFER_START, (psm ^ 0x03) ? 0 : 1);
}
