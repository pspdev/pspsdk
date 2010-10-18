/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"
#include <math.h>
#include <string.h>

int gum_current_mode = GU_PROJECTION;

int gum_matrix_update[4] = { 0 };
int gum_current_matrix_update = 0;

ScePspFMatrix4* gum_current_matrix = gum_matrix_stack[GU_PROJECTION];

ScePspFMatrix4* gum_stack_depth[4] =
{
  gum_matrix_stack[GU_PROJECTION],
  gum_matrix_stack[GU_VIEW],
  gum_matrix_stack[GU_MODEL],
  gum_matrix_stack[GU_TEXTURE]
};

ScePspFMatrix4 gum_matrix_stack[4][32];

struct pspvfpu_context *gum_vfpucontext;
