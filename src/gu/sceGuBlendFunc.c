/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuBlendFunc(int op, int src, int dest, unsigned int srcfix, unsigned int destfix)
{
	sendCommandi(223,src | (dest << 4) | (op << 8));
	sendCommandi(224,srcfix & 0xffffff);
	sendCommandi(225,destfix & 0xffffff);
}
