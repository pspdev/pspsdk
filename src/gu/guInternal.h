/*
 * PSP Software Development Kit - https://github.com/pspdev
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
	unsigned int *start;
	unsigned int *current;
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
	void *frame_buffer;
	void *disp_buffer;
	void *depth_buffer;
	int depth_width;
	int width;
	int height;
} GuDrawBuffer;

extern GuContext gu_contexts[3];
extern int ge_list_executed[2];
extern void *ge_edram_address;
extern GuSettings gu_settings;
extern GuDisplayList *gu_list;
extern int gu_curr_context;
extern int gu_init;
extern int gu_display_on;
extern int gu_call_mode;
extern int gu_states;
extern GuDrawBuffer gu_draw_buffer;

extern unsigned int *gu_object_stack[];
extern int gu_object_stack_depth;

void callbackSig(int id, void *arg);
void callbackFin(int id, void *arg);

typedef enum GECommand
{
	/* No operation */
	NOP = 0x0,			
	/* Vertex data */
	VADDR = 0x1,		
	/* Index data */
	IADDR = 0x2,		
	/* Draw Primitive */
	PRIM = 0x4,			
	/* Draw Bezier surface */
	BEZIER = 0x5,		
	/* Draw Spline surface */
	SPLINE = 0x6,		
	/* Bounding Box */
	BOUNDING_BOX = 0x7, 
	/* Jump */
	JUMP = 0x8,			
	/* Conditional Jump */
	BJUMP = 0x9,		
	/* List Call */
	CALL = 0xa,			
	/* List Return */
	RET = 0xb,			
	/* End reading */
	END = 0xc,			
	/* Signal interrupt */
	SIGNAL = 0xe,		
	/* Finish drawing */
	FINISH = 0xf,		
	/* Address base */
	BASE = 0x10,		
	/* Vertex type */
	VERTEX_TYPE = 0x12, 
	/* Offset address */
	OFFSET_ADDR = 0x13, 
	/* Origin address */
	ORIGIN = 0x14,		
	/* Drawing region 1, origin */
	REGION1 = 0x15,		
	/* Drawing region 2, end */
	REGION2 = 0x16,		

	/* Lighting enable */
	LIGHTING_ENABLE = 0x17,		
	/* Light 0 enable */
	LIGHT_ENABLE0 = 0x18,		
	/* Light 1 enable */
	LIGHT_ENABLE1 = 0x19,		
	/* Light 2 enable */
	LIGHT_ENABLE2 = 0x1a,		
	/* Light 3 enable */
	LIGHT_ENABLE3 = 0x1b,		
	/* Clipping enable */
	DEPTH_CLIP_ENABLE = 0x1c,	
	/* Culling enable */
	CULL_FACE_ENABLE = 0x1d,	
	/* Texture mapping enable */
	TEXTURE_ENABLE = 0x1e,		
	/* Fog enable */
	FOG_ENABLE = 0x1f,			
	/* Dithering enable */
	DITHER_ENABLE = 0x20,		
	/* Alpha blending enable */
	ALPHA_BLEND_ENABLE = 0x21,	
	/* Alpha testing enable */
	ALPHA_TEST_ENABLE = 0x22,	
	/* Z testing enable */
	Z_TEST_ENABLE = 0x23,		
	/* Stencil testing enable */
	STENCIL_TEST_ENABLE = 0x24, 
	/* Anti-aliasing enable */
	ANTI_ALIAS_ENABLE = 0x25,	
	/* Patch culling enable */
	PATCH_CULL_ENABLE = 0x26,	
	/* Color testing enable */
	COLOR_TEST_ENABLE = 0x27,	
	/* Logical operation enable */
	LOGIC_OP_ENABLE = 0x28,		

	/* Bone matrix number */
	BONE_MATRIX_NUMBER = 0x2a, 
	/* Bone matrix data */
	BONE_MATRIX_DATA = 0x2b,   
	/* Morph weight 0 */
	MORPH_WEIGHT0 = 0x2c,	   
	/* Morph weight 1 */
	MORPH_WEIGHT1 = 0x2d,	   
	/* Morph weight 2 */
	MORPH_WEIGHT2 = 0x2e,	   
	/* Morph weight 3 */
	MORPH_WEIGHT3 = 0x2f,	   
	/* Morph weight 4 */
	MORPH_WEIGHT4 = 0x30,	   
	/* Morph weight 5 */
	MORPH_WEIGHT5 = 0x31,	   
	/* Morph weight 6 */
	MORPH_WEIGHT6 = 0x32,	   
	/* Morph weight 7 */
	MORPH_WEIGHT7 = 0x33,	   

	/* Patch division count */
	PATCH_DIVISION = 0x36,		
	/* Patch primitive type */
	PATCH_PRIMITIVE = 0x37,		
	/* Patch facing */
	PATCH_FACING = 0x38,		
	/* World matrix number */
	WORLD_MATRIX_NUMBER = 0x3a, 
	/* World matrix data */
	WORLD_MATRIX_DATA = 0x3b,	
	/* View matrix number */
	VIEW_MATRIX_NUMBER = 0x3c,	
	/* View matrix data */
	VIEW_MATRIX_DATA = 0x3d,	
	/* Projection matrix number */
	PROJ_MATRIX_NUMBER = 0x3e,	
	/* Projection matrix data */
	PROJ_MATRIX_DATA = 0x3f,	
	/* Texture generation matrix number */
	TGEN_MATRIX_NUMBER = 0x40,	
	/* Texture generation matrix data */
	TGEN_MATRIX_DATA = 0x41,	

	/* Viewport X scale */
	VIEWPORT_X_SCALE = 0x42,  
	/* Viewport Y scale */
	VIEWPORT_Y_SCALE = 0x43,  
	/* Viewport Z scale */
	VIEWPORT_Z_SCALE = 0x44,  
	/* Viewport X center */
	VIEWPORT_X_CENTER = 0x45, 
	/* Viewport Y center */
	VIEWPORT_Y_CENTER = 0x46, 
	/* Viewport Z center */
	VIEWPORT_Z_CENTER = 0x47, 
	/* Texture scale U */
	TEX_SCALE_U = 0x48,		  
	/* Texture scale V */
	TEX_SCALE_V = 0x49,		  
	/* Texture offset U */
	TEX_OFFSET_U = 0x4a,	  
	/* Texture offset V */
	TEX_OFFSET_V = 0x4b,	  
	/* Screen Offset X */
	OFFSET_X = 0x4c,		  
	/* Screen Offset Y */
	OFFSET_Y = 0x4d,		  

	/* Shade mode */
	SHADE_MODE = 0x50,			   
	/* Normal reverse */
	NORMAL_REVERSE = 0x51,		   
	/* Material color */
	MATERIAL_COLOR = 0x53,		   
	/* Material emissive */
	MATERIAL_EMISSIVE = 0x54,	   
	/* Ambient color */
	AMBIENT_COLOR = 0x55,		   
	/* Material diffuse */
	MATERIAL_DIFFUSE = 0x56,	   
	/* Material specular */
	MATERIAL_SPECULAR = 0x57,	   
	/* Ambient alpha */
	AMBIENT_ALPHA = 0x58,		   
	/* Material specular coefficient */
	MATERIAL_SPECULAR_COEF = 0x5b, 
	/* Ambient light color */
	AMBIENT_LIGHT_COLOR = 0x5c,	   
	/* Ambient light alpha */
	AMBIENT_LIGHT_ALPHA = 0x5d,	   
	/* Light mode */
	LIGHT_MODE = 0x5e,			   

	/* Light type 0 */
	LIGHT_TYPE0 = 0x5f, 
	/* Light type 1 */
	LIGHT_TYPE1 = 0x60, 
	/* Light type 2 */
	LIGHT_TYPE2 = 0x61, 
	/* Light type 3 */
	LIGHT_TYPE3 = 0x62, 
	/* Light 0 X */
	LIGHT0_X = 0x63,	
	/* Light 0 Y */
	LIGHT0_Y = 0x64,	
	/* Light 0 Z */
	LIGHT0_Z = 0x65,	
	/* Light 1 X */
	LIGHT1_X = 0x66,	
	/* Light 1 Y */
	LIGHT1_Y = 0x67,	
	/* Light 1 Z */
	LIGHT1_Z = 0x68,	
	/* Light 2 X */
	LIGHT2_X = 0x69,	
	/* Light 2 Y */
	LIGHT2_Y = 0x6a,	
	/* Light 2 Z */
	LIGHT2_Z = 0x6b,	
	/* Light 3 X */
	LIGHT3_X = 0x6c,	
	/* Light 3 Y */
	LIGHT3_Y = 0x6d,	
	/* Light 3 Z */
	LIGHT3_Z = 0x6e,	

	/* Light 0 direction X */
	LIGHT0_DIRECTION_X = 0x6f, 
	/* Light 0 direction Y */
	LIGHT0_DIRECTION_Y = 0x70, 
	/* Light 0 direction Z */
	LIGHT0_DIRECTION_Z = 0x71, 
	/* Light 1 direction X */
	LIGHT1_DIRECTION_X = 0x72, 
	/* Light 1 direction Y */
	LIGHT1_DIRECTION_Y = 0x73, 
	/* Light 1 direction Z */
	LIGHT1_DIRECTION_Z = 0x74, 
	/* Light 2 direction X */
	LIGHT2_DIRECTION_X = 0x75, 
	/* Light 2 direction Y */
	LIGHT2_DIRECTION_Y = 0x76, 
	/* Light 2 direction Z */
	LIGHT2_DIRECTION_Z = 0x77, 
	/* Light 3 direction X */
	LIGHT3_DIRECTION_X = 0x78, 
	/* Light 3 direction Y */
	LIGHT3_DIRECTION_Y = 0x79, 
	/* Light 3 direction Z */
	LIGHT3_DIRECTION_Z = 0x7a, 

	/* Light 0 constant attenuation */
	LIGHT0_CONSTANT_ATTEN = 0x7b,  
	/* Light 0 linear attenuation */
	LIGHT0_LINEAR_ATTEN = 0x7c,	   
	/* Light 0 quadratic attenuation */
	LIGHT0_QUADRATIC_ATTEN = 0x7d, 
	/* Light 1 constant attenuation */
	LIGHT1_CONSTANT_ATTEN = 0x7e,  
	/* Light 1 linear attenuation */
	LIGHT1_LINEAR_ATTEN = 0x7f,	   
	/* Light 1 quadratic attenuation */
	LIGHT1_QUADRATIC_ATTEN = 0x80, 
	/* Light 2 constant attenuation */
	LIGHT2_CONSTANT_ATTEN = 0x81,  
	/* Light 2 linear attenuation */
	LIGHT2_LINEAR_ATTEN = 0x82,	   
	/* Light 2 quadratic attenuation */
	LIGHT2_QUADRATIC_ATTEN = 0x83, 
	/* Light 3 constant attenuation */
	LIGHT3_CONSTANT_ATTEN = 0x84,  
	/* Light 3 linear attenuation */
	LIGHT3_LINEAR_ATTEN = 0x85,	   
	/* Light 3 quadratic attenuation */
	LIGHT3_QUADRATIC_ATTEN = 0x86, 

	/* Light 0 exponent attenuation */
	LIGHT0_EXPONENT_ATTEN = 0x87, 
	/* Light 1 exponent attenuation */
	LIGHT1_EXPONENT_ATTEN = 0x88, 
	/* Light 2 exponent attenuation */
	LIGHT2_EXPONENT_ATTEN = 0x89, 
	/* Light 3 exponent attenuation */
	LIGHT3_EXPONENT_ATTEN = 0x8a, 

	/* Light 0 cutoff attenuation */
	LIGHT0_CUTOFF_ATTEN = 0x8b, 
	/* Light 1 cutoff attenuation */
	LIGHT1_CUTOFF_ATTEN = 0x8c, 
	/* Light 2 cutoff attenuation */
	LIGHT2_CUTOFF_ATTEN = 0x8d, 
	/* Light 3 cutoff attenuation */
	LIGHT3_CUTOFF_ATTEN = 0x8e, 

	/* Light 0 ambient */
	LIGHT0_AMBIENT = 0x8f,	
	/* Light 0 diffuse */
	LIGHT0_DIFFUSE = 0x90,	
	/* Light 0 specular */
	LIGHT0_SPECULAR = 0x91, 
	/* Light 1 ambient */
	LIGHT1_AMBIENT = 0x92,	
	/* Light 1 diffuse */
	LIGHT1_DIFFUSE = 0x93,	
	/* Light 1 specular */
	LIGHT1_SPECULAR = 0x94, 
	/* Light 2 ambient */
	LIGHT2_AMBIENT = 0x95,	
	/* Light 2 diffuse */
	LIGHT2_DIFFUSE = 0x96,	
	/* Light 2 specular */
	LIGHT2_SPECULAR = 0x97, 
	/* Light 3 ambient */
	LIGHT3_AMBIENT = 0x98,	
	/* Light 3 diffuse */
	LIGHT3_DIFFUSE = 0x99,	
	/* Light 3 specular */
	LIGHT3_SPECULAR = 0x9a, 

	/* Culling */
	CULL = 0x9b, 

	/* Frame buffer pointer */
	FRAME_BUF_PTR = 0x9c,	
	/* Frame buffer width */
	FRAME_BUF_WIDTH = 0x9d, 
	/* Z buffer pointer */
	Z_BUF_PTR = 0x9e,		
	/* Z buffer width */
	Z_BUF_WIDTH = 0x9f,		

	/* Texture address 0 */
	TEX_ADDR0 = 0xa0,	   
	/* Texture address 1 */
	TEX_ADDR1 = 0xa1,	   
	/* Texture address 2 */
	TEX_ADDR2 = 0xa2,	   
	/* Texture address 3 */
	TEX_ADDR3 = 0xa3,	   
	/* Texture address 4 */
	TEX_ADDR4 = 0xa4,	   
	/* Texture address 5 */
	TEX_ADDR5 = 0xa5,	   
	/* Texture address 6 */
	TEX_ADDR6 = 0xa6,	   
	/* Texture address 7 */
	TEX_ADDR7 = 0xa7,	   
	/* Texture buffer width 0 */
	TEX_BUF_WIDTH0 = 0xa8, 
	/* Texture buffer width 1 */
	TEX_BUF_WIDTH1 = 0xa9, 
	/* Texture buffer width 2 */
	TEX_BUF_WIDTH2 = 0xaa, 
	/* Texture buffer width 3 */
	TEX_BUF_WIDTH3 = 0xab, 
	/* Texture buffer width 4 */
	TEX_BUF_WIDTH4 = 0xac, 
	/* Texture buffer width 5 */
	TEX_BUF_WIDTH5 = 0xad, 
	/* Texture buffer width 6 */
	TEX_BUF_WIDTH6 = 0xae, 
	/* Texture buffer width 7 */
	TEX_BUF_WIDTH7 = 0xaf, 

	/* CLUT buffer pointer */
	CLUT_BUF_PTR = 0xb0,
	/* CLUT buffer width */
	CLUT_BUF_WIDTH = 0xb1, 

	/* Transfer source */
	TRANSFER_SRC = 0xb2,   
	/* Transfer source width */
	TRANSFER_SRC_W = 0xb3, 
	/* Transfer destination */
	TRANSFER_DST = 0xb4,   
	/* Transfer destination width */
	TRANSFER_DST_W = 0xb5, 

	/* Texture size 0 */
	TEX_SIZE0 = 0xb8, 
	/* Texture size 1 */
	TEX_SIZE1 = 0xb9, 
	/* Texture size 2 */
	TEX_SIZE2 = 0xba, 
	/* Texture size 3 */
	TEX_SIZE3 = 0xbb, 
	/* Texture size 4 */
	TEX_SIZE4 = 0xbc, 
	/* Texture size 5 */
	TEX_SIZE5 = 0xbd, 
	/* Texture size 6 */
	TEX_SIZE6 = 0xbe, 
	/* Texture size 7 */
	TEX_SIZE7 = 0xbf, 

	/* Texture map mode */
	TEX_MAP_MODE = 0xc0,	  
	/* Texture shade mapping */
	TEX_SHADE_MAPPING = 0xc1, 
	/* Texture mode */
	TEX_MODE = 0xc2,		  
	/* Texture format */
	TEX_FORMAT = 0xc3,		  
	/* Load CLUT */
	CLUT_LOAD = 0xc4,		  
	/* CLUT format */
	CLUT_FORMAT = 0xc5,		  
	/* Texture filter */
	TEX_FILTER = 0xc6,		  
	/* Texture wrap */
	TEX_WRAP = 0xc7,		  
	/* Texture level */
	TEX_LEVEL = 0xc8,		  
	/* Texture function */
	TEX_FUNC = 0xc9,		  
	/* Texture environment color */
	TEX_ENV_COLOR = 0xca,	  
	/* Texture flush */
	TEX_FLUSH = 0xcb,		  
	/* Texture sync */
	TEX_SYNC = 0xcc,		  

	/* Fog 1 */
	FOG1 = 0xcd,		  
	/* Fog 2 */
	FOG2 = 0xce,		  
	/* Fog color */
	FOG_COLOR = 0xcf,	  
	/* Texture LOD slope */
	TEX_LOD_SLOPE = 0xd0, 

	/* Frame buffer pixel format */
	FRAMEBUF_PIX_FORMAT = 0xd2, 
	/* Clear mode */
	CLEAR_MODE = 0xd3,			
	/* Scissor 1 */
	SCISSOR1 = 0xd4,			
	/* Scissor 2 */
	SCISSOR2 = 0xd5,			

	/* Minimum Z */
	MIN_Z = 0xd6,		   
	/* Maximum Z */
	MAX_Z = 0xd7,		   
	/* Color test */
	COLOR_TEST = 0xd8,	   
	/* Color reference */
	COLOR_REF = 0xd9,	   
	/* Color test mask */
	COLOR_TESTMASK = 0xda, 
	/* Alpha test */
	ALPHA_TEST = 0xdb,	   
	/* Stencil test */
	STENCIL_TEST = 0xdc,   
	/* Stencil operation */
	STENCIL_OP = 0xdd,	   
	/* Z test */
	Z_TEST = 0xde,		   
	/* Blend mode */
	BLEND_MODE = 0xdf,	   
	/* Blend fixed A */
	BLEND_FIXED_A = 0xe0,  
	/* Blend fixed B */
	BLEND_FIXED_B = 0xe1,  
	/* Dither 0 */
	DITH0 = 0xe2,		   
	/* Dither 1 */
	DITH1 = 0xe3,		   
	/* Dither 2 */
	DITH2 = 0xe4,		   
	/* Dither 3 */
	DITH3 = 0xe5,		   

	/* Logical operation */
	LOGIC_OP = 0xe6,   
	/* Z mask */
	Z_MASK = 0xe7,	   
	/* Mask color */
	MASK_COLOR = 0xe8, 
	/* Mask alpha */
	MASK_ALPHA = 0xe9, 

	/* Transfer start */
	TRANSFER_START = 0xea,		
	/* Transfer source offset */
	TRANSFER_SRC_OFFSET = 0xeb, 
	/* Transfer destination offset */
	TRANSFER_DST_OFFSET = 0xec, 
	/* Transfer format */
	TRANSFER_FORMAT = 0xed,		
	/* Transfer size */
	TRANSFER_SIZE = 0xee,		

	/* Transfer flip */
	TRANSFER_FLIP = 0xef,				   
	/* Transfer out size */
	TRANSFER_OUT_SIZE = 0xf0,			   
	/* Transfer out format */
	TRANSFER_OUT_FORMAT = 0xf1,			   
	/* Vertex weight */
	VERTEX_WEIGHT = 0xf2,				   
	/* Vertex weight address */
	VERTEX_WEIGHT_ADDR = 0xf3,			   
	/* Vertex weight size */
	VERTEX_WEIGHT_SIZE = 0xf4,			   
	/* Vertex weight type */
	VERTEX_WEIGHT_TYPE = 0xf5,			   
	/* Vertex weight model */
	VERTEX_WEIGHT_MODEL = 0xf6,			   
	/* Vertex weight normalize */
	VERTEX_WEIGHT_NORMALIZE = 0xf7,		   
	/* Vertex weight offset */
	VERTEX_WEIGHT_OFFSET = 0xf8,		   
	/* Vertex weight scale */
	VERTEX_WEIGHT_SCALE = 0xf9,			   
	/* Vertex weight matrix */
	VERTEX_WEIGHT_MATRIX = 0xfa,		   
	/* Vertex weight matrix address */
	VERTEX_WEIGHT_MATRIX_ADDR = 0xfb,	   
	/* Vertex weight matrix size */
	VERTEX_WEIGHT_MATRIX_SIZE = 0xfc,	   
	/* Vertex weight matrix type */
	VERTEX_WEIGHT_MATRIX_TYPE = 0xfd,	   
	/* Vertex weight matrix model */
	VERTEX_WEIGHT_MATRIX_MODEL = 0xfe,	   
	/* Vertex weight matrix normalize */
	VERTEX_WEIGHT_MATRIX_NORMALIZE = 0xff, 
} GECommand;

static inline void sendCommandi(GECommand cmd, int argument)
{
	*(gu_list->current++) = (cmd << 24) | (argument & 0xffffff);
}

static inline void sendCommandf(GECommand cmd, float argument)
{
	union
	{
		float f;
		unsigned int i;
	} t;
	t.f = argument;

	sendCommandi(cmd, t.i >> 8);
}

static inline int _sceGuUpdateStallAddr(void) {
	if (gu_curr_context == GU_DIRECT) {
		// Just if there are no objects in the stack (no guBeginObject)
		if (!gu_object_stack_depth) {
			int res;
			res = sceGeListUpdateStallAddr(ge_list_executed[0], gu_list->current);
			if (res < 0) {
				return res;
			}
		}
	} 
	return 0;
}

#endif
