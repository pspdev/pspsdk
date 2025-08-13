/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

GuContext gu_contexts[3];
int ge_list_executed[2];
void* ge_edram_address;
GuSettings gu_settings;
GuDisplayList* gu_list;
int gu_curr_context;
int gu_init;
int gu_first_start;
int gu_display_on;
int gu_call_mode;
int gu_states;
GuDrawBuffer gu_draw_buffer;
unsigned int* gu_object_stack[GU_OBJECT_STACK_SIZE];
int gu_object_stack_depth;
