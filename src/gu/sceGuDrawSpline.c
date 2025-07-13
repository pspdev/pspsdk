/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawSpline(int vertex_type, int ucount, int vcount, int uedge, int vedge, const void *indices, const void *vertices)
{
#ifdef GU_DEBUG
	printf("sceGuDrawSpline(%d, %d, %d, %d, %d, %p, %p);\n", vertex_type, ucount, vcount, uedge, vedge, indices, vertices);
	assert(gu_init && "GU not initialized");
	assert(ucount >= 4 && ucount <= 255 && "Invalid U count - must be between 4 and 255");
	assert(vcount >= 4 && vcount <= 255 && "Invalid V count - must be between 4 and 255");
	assert(uedge >= 0 && uedge <= 3 && "Invalid U edge");
	assert(vedge >= 0 && vedge <= 3 && "Invalid V edge");
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

  sendCommandi(SPLINE, (vedge << 18) | (uedge << 16) | (vcount << 8) | ucount);
  _sceGuUpdateStallAddr();
}
