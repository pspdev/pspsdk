/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawBezier(int vertex_type, int ucount, int vcount, const void *indices, const void *vertices)
{
#ifdef GU_DEBUG
	printf("sceGuDrawBezier(%d, %d, %d, %p, %p);\n", vertex_type, ucount, vcount, indices, vertices);
	assert(gu_init && "GU not initialized");
	assert(ucount > 1 && ucount <= 255 && (ucount % 3) == 1 && "Invalid U count, must be 3*N+1");
	assert(vcount > 1 && vcount <= 255 && (vcount % 3) == 1 && "Invalid V count, must be 3*N+1");
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

  sendCommandi(BEZIER, (vcount << 8) | ucount);
  _sceGuUpdateStallAddr();
}
