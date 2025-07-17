/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuClearStencil(unsigned int stencil)
{
#ifdef GU_DEBUG
	printf("sceGuClearStencil(%u);\n", stencil);
	assert(gu_init && "GU not initialized");
	switch (gu_draw_buffer.pixel_size)
	{
	case GU_PSM_8888:
		assert(stencil <= 255 && "Invalid stencil value for GU_PSM_8888");
		break;
	case GU_PSM_4444:
		assert(stencil <= 15 && "Invalid stencil value for GU_PSM_4444");
		break;
	case GU_PSM_5551:
		assert(stencil <= 1 && "Invalid stencil value for GU_PSM_5551");
		break;
	case GU_PSM_5650:
		assert(0 && "Stencil not supported for GU_PSM_5650");
		break;	
	default:
		assert(0 && "Invalid pixel format");
		break;
	}
#endif

	GuContext* context = &gu_contexts[gu_curr_context];
	context->clear_stencil = stencil;
}
