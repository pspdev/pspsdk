/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

void sceGuDepthRange(int near, int far)
{
	GuContext* context = &gu_contexts[gu_curr_context];              

	unsigned int max = (unsigned int)near + (unsigned int)far;
	int val = (int)((max >> 31) + max);
	float z = (float)(val >> 1);

	context->near_plane = near;
        context->far_plane = far;

        sendCommandf(68,z - ((float)near));
        sendCommandf(71,z + ((float)context->depth_offset));

	if (near > far)
        {
          int temp = near;
          near = far;
          far = temp;
        }

        sendCommandi(214,near);
        sendCommandi(215,far);
}
