/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

static int tbpcmd_tbl[8] = { 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7 };		// 0x30A18
static int tbwcmd_tbl[8] = { 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf };		// 0x30A38
static int tsizecmd_tbl[8] = { 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf };	// 0x30A58

int getExp(int val)
{
	unsigned int i;
	asm("clz %0, %1\n":"=r"(i):"r"(val&0x3FF));
	return 31-i;
/*
	unsigned int i;
	for (i = 9; (i > 0) && !((val >> i) & 1); --i);
	return i;
*/
}

void sceGuTexImage(int mipmap, int width, int height, int tbw, const void* tbp)
{
	sendCommandi(tbpcmd_tbl[mipmap],((unsigned int)tbp) & 0xffffff);
	sendCommandi(tbwcmd_tbl[mipmap],((((unsigned int)tbp) >> 8) & 0x0f0000)|tbw);
	sendCommandi(tsizecmd_tbl[mipmap],(getExp(height) << 8)|(getExp(width)));
	sceGuTexFlush();
}
