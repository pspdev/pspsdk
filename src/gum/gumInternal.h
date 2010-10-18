/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#ifndef __gumInternal_h__
#define __gumInternal_h__

#include <alloca.h>

#include "pspgum.h"
#include "../gu/pspgu.h"

#define GUM_EPSILON 0.00001f

//#define GUM_USE_VFPU

// these macros are because GCC cannot handle aligned matrices declared on the stack
#define GUM_ALIGNED_MATRIX() (ScePspFMatrix4*)((((unsigned int)alloca(sizeof(ScePspFMatrix4)+64)) + 63) & ~63)
#define GUM_ALIGNED_VECTOR() (ScePspFVector4*)((((unsigned int)alloca(sizeof(ScePspFVector4)+64)) + 63) & ~63)

extern int gum_current_mode;
extern int gum_matrix_update[4];
extern int gum_current_matrix_update;
extern ScePspFMatrix4* gum_current_matrix;
extern ScePspFMatrix4* gum_stack_depth[4];
extern ScePspFMatrix4 gum_matrix_stack[4][32];

extern struct pspvfpu_context *gum_vfpucontext;

#endif
