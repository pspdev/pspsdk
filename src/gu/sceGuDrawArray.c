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
#ifdef GU_DEBUG
	printf("sceGuDrawArray(%d, %d, %d, %p, %p);\n", prim, vtype, count, indices, vertices);
	assert(gu_init && "GU not initialized");
	assert(count > 0 && count <= 65535 && "Invalid vertex count");
	assert(prim >= GU_POINTS && prim <= GU_SPRITES && "Invalid primitive type");
#endif

  if (vtype)
    sendCommandi(VERTEX_TYPE, vtype);

  if (indices)
  {
    sendCommandi(BASE, (((unsigned int)indices) >> 8) & 0xf0000);
    sendCommandi(IADDR, ((unsigned int)indices));
  }

  if (vertices)
  {
    sendCommandi(BASE, (((unsigned int)vertices) >> 8) & 0xf0000);
    sendCommandi(VADDR, ((unsigned int)vertices));
  }

  sendCommandi(PRIM, (prim << 16) | count);
  _sceGuUpdateStallAddr();
}
