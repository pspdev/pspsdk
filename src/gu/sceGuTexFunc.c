/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuTexFunc(int tfx, int tcc)
{
#ifdef GU_DEBUG
	printf("sceGuTexFunc(%d, %d);\n", tfx, tcc);
	assert(gu_init && "GU not initialized");
	assert(tfx >= GU_TFX_MODULATE && tfx <= GU_TFX_ADD && "Invalid texture function");
	assert(tcc >= GU_TCC_RGB && tcc <= GU_TCC_RGBA && "Invalid texture color component");
#endif

	GuContext *context = &gu_contexts[gu_curr_context];
	context->texture_function = tfx | (tcc << 8);
	sendCommandi(TEX_FUNC, context->texture_function | context->fragment_2x);
}
