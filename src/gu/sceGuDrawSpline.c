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

  sendCommandi(SPLINE, (vedge << 18) | (uedge << 16) | (vcount << 8) | ucount);
}
