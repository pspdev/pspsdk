/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawArrayN(int primitive_type, int vertex_type, int vcount, int primcount, const void *indices, const void *vertices)
{
	if (vertex_type)
		sendCommandi(VERTEX_TYPE, vertex_type);

	if (indices)
	{
		sendCommandi(BASE, (((unsigned int)indices) >> 8) & 0xf0000);
		sendCommandi(IADDR, (unsigned int)indices);
	}

	if (vertices)
	{
		sendCommandi(BASE, (((unsigned int)vertices) >> 8) & 0xf0000);
		sendCommandi(VADDR, (unsigned int)vertices);
	}

	if (primcount > 0)
	{
		int i;
		for (i = 0; i < primcount; i++)
			sendCommandi(PRIM, (primitive_type << 16) | vcount);
	}

	_sceGuUpdateStallAddr();
}
