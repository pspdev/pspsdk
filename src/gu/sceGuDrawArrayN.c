/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawArrayN(int primitive_type, int vertex_type, int count, int a3, const void* indices, const void* vertices)
{
	if (vertex_type)
		sendCommandi(18,vertex_type);

	if (indices)
	{
		sendCommandi(16,(((unsigned int)indices) >> 8) & 0xf0000);
		sendCommandi(2,((unsigned int)indices) & 0xffffff);
	}

	if (vertices)
	{
		sendCommandi(16,(((unsigned int)vertices) >> 8) & 0xf0000);
		sendCommandi(1,((unsigned int)vertices) & 0xffffff);
	}

	if (a3 > 0)
	{
		// TODO: not sure about this loop, might be off. review
		int i;
		for (i = a3-1; i > 0; --i)
			sendCommandi(4,(primitive_type << 16)|count);
		sendCommandiStall(4,(primitive_type << 16)|count);
	}
}
