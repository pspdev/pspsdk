/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#ifndef __guInternal_h__
#define __guInternal_h__

#include "pspgu.h"

typedef void (*GuCallback)(int);

typedef struct
{
	GuCallback sig;
	GuCallback fin;
	short signal_history[16];
	int signal_offset;
	int kernel_event_flag;
	int ge_callback_id;

	GuSwapBuffersCallback swapBuffersCallback;
	int swapBuffersBehaviour;	
} GuSettings;

typedef struct
{
	unsigned int* start;
	unsigned int* current;
	int parent_context;
} GuDisplayList;

typedef struct
{
	GuDisplayList list;
	int scissor_enable;
	int scissor_start[2];
	int scissor_end[2];
	int near_plane;
	int far_plane;
	int depth_offset;
	int fragment_2x;
	int texture_function;
	int texture_proj_map_mode;
	int texture_map_mode;
	int sprite_mode[4];
	unsigned int clear_color;
	unsigned int clear_stencil;
	unsigned int clear_depth;
	int texture_mode;
} GuContext;

typedef struct
{
	int pixel_size;
	int frame_width;
	void* frame_buffer;
	void* disp_buffer;
	void* depth_buffer;
	int depth_width;
	int width;
	int height;
} GuDrawBuffer;

typedef struct
{
	/* row 0 */

	unsigned char enable;	// Light enable
	unsigned char type;	// Light type
	unsigned char xpos;	// X position
	unsigned char ypos;	// Y position

	/* row 1 */

	unsigned char zpos;	// Z position
	unsigned char xdir;	// X direction
	unsigned char ydir;	// Y direction
	unsigned char zdir;	// Z direction

	/* row 2 */

	unsigned char ambient;	// Ambient color
	unsigned char diffuse;	// Diffuse color
	unsigned char specular;	// Specular color
	unsigned char constant;	// Constant attenuation

	/* row 3 */

	unsigned char linear;	// Linear attenuation
	unsigned char quadratic;// Quadratic attenuation
	unsigned char exponent;	// Light exponent
	unsigned char cutoff;	// Light cutoff
} GuLightSettings;

extern unsigned int gu_current_frame;
extern GuContext gu_contexts[3];
extern int ge_list_executed[2];
extern void* ge_edram_address;
extern GuSettings gu_settings;
extern GuDisplayList* gu_list;
extern int gu_curr_context;
extern int gu_init;
extern int gu_display_on;
extern int gu_call_mode;
extern int gu_states;
extern GuDrawBuffer gu_draw_buffer;

extern unsigned int* gu_object_stack[];
extern int gu_object_stack_depth;

extern GuLightSettings light_settings[4];

void sendCommandi(int cmd, int argument);
void sendCommandiStall(int cmd, int argument);
void sendCommandf(int cmd, float argument);

void callbackSig(int id, void* arg);
void callbackFin(int id, void* arg);
void resetValues();

#endif
