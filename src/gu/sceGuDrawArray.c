/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDrawArray(int prim, int vtype, int count, const void* indices, const void* vertices)
{
  if (vtype)
    sendCommandi(18,vtype);

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

  sendCommandiStall(4,(prim << 16)|count);
}
