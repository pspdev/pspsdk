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
#ifdef GU_DEBUG
	printf("sceGuTexImage(%d, %d, %d, %d, %p);\n", mipmap, width, height, tbw, tbp);
	assert(gu_init && "GU not initialized");
	assert(((unsigned int)tbp & 0xF) == 0 && "Texture buffer pointer must be 16-byte aligned");
	assert(mipmap >= 0 && mipmap <= 7 && "Invalid mipmap level");
	assert(width >= 1 && width <= 512 && "Invalid texture width");
	assert(height >= 1 && height <= 512 && "Invalid texture height");
	assert(tbw >= 1 && tbw <= 1024 && "Invalid texture buffer width");
	assert((width & (width - 1)) == 0 && "Texture width must be power of 2");
	assert((height & (height - 1)) == 0 && "Texture height must be power of 2");
#endif

	GECommand texAddr = (GECommand)(TEX_ADDR0 + mipmap);
	GECommand texBufWidth = (GECommand)(TEX_BUF_WIDTH0 + mipmap);
	GECommand texSize = (GECommand)(TEX_SIZE0 + mipmap);
	sendCommandi(texAddr, ((unsigned int)tbp));
	sendCommandi(texBufWidth, ((((unsigned int)tbp) >> 8) & 0x0f0000) | tbw);
	sendCommandi(texSize, (getExp(height) << 8) | (getExp(width)));
	sceGuTexFlush();
}
