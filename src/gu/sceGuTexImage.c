/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

static inline int getExp(int val)
{
	return 31 - __builtin_clz(val & 0x3FF);
}

void sceGuTexImage(int mipmap, int width, int height, int tbw, const void *tbp)
{
	GECommand texAddr = (GECommand)(TEX_ADDR0 + mipmap);
	GECommand texBufWidth = (GECommand)(TEX_BUF_WIDTH0 + mipmap);
	GECommand texSize = (GECommand)(TEX_SIZE0 + mipmap);
	sendCommandi(texAddr, ((unsigned int)tbp) & 0xffffff);
	sendCommandi(texBufWidth, ((((unsigned int)tbp) >> 8) & 0x0f0000) | tbw);
	sendCommandi(texSize, (getExp(height) << 8) | (getExp(width)));
	sceGuTexFlush();
}
