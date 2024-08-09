/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawArrayN(int primitive_type, int vertex_type, int count, int a3, const void *indices, const void *vertices)
{
	if (vertex_type)
		sendCommandi(VERTEX_TYPE, vertex_type);

	if (indices)
	{
		sendCommandi(BASE, (((unsigned int)indices) >> 8) & 0xf0000);
		sendCommandi(IADDR, ((unsigned int)indices) & 0xffffff);
	}

	if (vertices)
	{
		sendCommandi(BASE, (((unsigned int)vertices) >> 8) & 0xf0000);
		sendCommandi(VADDR, ((unsigned int)vertices) & 0xffffff);
	}

	if (a3 > 0)
	{
		// TODO: not sure about this loop, might be off. review
		int i;
		for (i = a3 - 1; i > 0; --i)
			sendCommandi(PRIM, (primitive_type << 16) | count);
		sendCommandiStall(PRIM, (primitive_type << 16) | count);
	}
}
