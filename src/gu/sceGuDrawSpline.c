/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawSpline(int vertex_type, int ucount, int vcount, int uedge, int vedge, const void* indices, const void* vertices)
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

  sendCommandi(6,(vedge << 18)|(uedge << 16)|(vcount << 8)|ucount);
}
