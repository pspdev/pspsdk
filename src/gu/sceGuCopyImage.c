/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuCopyImage(int psm, int sx, int sy, int width, int height, int srcw, void* src, int dx, int dy, int destw, void* dest)
{
	sendCommandi(178,((unsigned int)src) & 0xffffff);
	sendCommandi(179,((((unsigned int)src) & 0xff000000) >> 8)|srcw);
	sendCommandi(235,(sy << 10)|sx);
	sendCommandi(180,((unsigned int)dest) & 0xffffff);
	sendCommandi(181,((((unsigned int)dest) & 0xff000000) >> 8)|destw);
	sendCommandi(236,(dy << 10)|dx);
	sendCommandi(238,((height-1) << 10)|(width-1));
	sendCommandi(234,(psm ^ 0x03) ? 0 : 1);
}
