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
#ifdef GU_DEBUG
	printf("sceGuDrawArrayN(%d, %d, %d, %d, %p, %p);\n", primitive_type, vertex_type, vcount, primcount, indices, vertices);
	assert(gu_init && "GU not initialized");
	assert(vcount > 0 && vcount <= 65535 && "Invalid vertex count");
	assert(primcount > 0 && primcount <= 65535 && "Invalid primitive count");
	assert(primitive_type >= GU_POINTS && primitive_type <= GU_TRIANGLE_FAN && "Invalid primitive type");
#endif

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
