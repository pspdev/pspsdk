/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawArray(int prim, int vtype, int count, const void *indices, const void *vertices)
{
  if (vtype)
    sendCommandi(VERTEX_TYPE, vtype);

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

  sendCommandiStall(PRIM, (prim << 16) | count);
}
