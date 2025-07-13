/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "guInternal.h"

#include <pspkernel.h>
#include <pspge.h>
#include <pspdisplay.h>

// Zero value
#define ZV(command) (uint32_t)(command << 24 | 0x00000000)

// Concrete value
#define CV(command, value) (uint32_t)(command << 24 | value)

static unsigned int __attribute__((aligned(16))) ge_init_list[] = {
	ZV(NOP),
	ZV(VADDR),
	ZV(IADDR),
	ZV(BASE),
	ZV(VERTEX_TYPE),
	ZV(OFFSET_ADDR),
	ZV(REGION1),
	ZV(REGION2),
	ZV(LIGHTING_ENABLE),
	ZV(LIGHT_ENABLE0),
	ZV(LIGHT_ENABLE1),
	ZV(LIGHT_ENABLE2),
	ZV(LIGHT_ENABLE3),
	ZV(DEPTH_CLIP_ENABLE),
	ZV(CULL_FACE_ENABLE),
	ZV(TEXTURE_ENABLE),
	ZV(FOG_ENABLE),
	ZV(DITHER_ENABLE),
	ZV(ALPHA_BLEND_ENABLE),
	ZV(ALPHA_TEST_ENABLE),
	ZV(Z_TEST_ENABLE),
	ZV(STENCIL_TEST_ENABLE),
	ZV(ANTI_ALIAS_ENABLE),
	ZV(PATCH_CULL_ENABLE),
	ZV(COLOR_TEST_ENABLE),
	ZV(LOGIC_OP_ENABLE),
	ZV(BONE_MATRIX_NUMBER),
	ZV(BONE_MATRIX_DATA),
	ZV(MORPH_WEIGHT0),
	ZV(MORPH_WEIGHT1),
	ZV(MORPH_WEIGHT2),
	ZV(MORPH_WEIGHT3),
	ZV(MORPH_WEIGHT4),
	ZV(MORPH_WEIGHT5),
	ZV(MORPH_WEIGHT6),
	ZV(MORPH_WEIGHT7),
	ZV(PATCH_DIVISION),
	ZV(PATCH_PRIMITIVE),
	ZV(PATCH_FACING),
	ZV(WORLD_MATRIX_NUMBER),
	ZV(WORLD_MATRIX_DATA),
	ZV(VIEW_MATRIX_NUMBER),
	ZV(VIEW_MATRIX_DATA),
	ZV(PROJ_MATRIX_NUMBER),
	ZV(PROJ_MATRIX_DATA),
	ZV(TGEN_MATRIX_NUMBER),
	ZV(TGEN_MATRIX_DATA),
	ZV(VIEWPORT_X_SCALE),
	ZV(VIEWPORT_Y_SCALE),
	ZV(VIEWPORT_Z_SCALE),
	ZV(VIEWPORT_X_CENTER),
	ZV(VIEWPORT_Y_CENTER),
	ZV(VIEWPORT_Z_CENTER),
	ZV(TEX_SCALE_U),
	ZV(TEX_SCALE_V),
	ZV(TEX_OFFSET_U),
	ZV(TEX_OFFSET_V),
	ZV(OFFSET_X),
	ZV(OFFSET_Y),
	ZV(SHADE_MODE),
	ZV(NORMAL_REVERSE),
	ZV(MATERIAL_COLOR),
	ZV(MATERIAL_EMISSIVE),
	ZV(AMBIENT_COLOR),
	ZV(MATERIAL_DIFFUSE),
	ZV(MATERIAL_SPECULAR),
	ZV(AMBIENT_ALPHA),
	ZV(MATERIAL_SPECULAR_COEF),
	ZV(AMBIENT_LIGHT_COLOR),
	ZV(AMBIENT_LIGHT_ALPHA),
	ZV(LIGHT_MODE),
	ZV(LIGHT_TYPE0),
	ZV(LIGHT_TYPE1),
	ZV(LIGHT_TYPE2),
	ZV(LIGHT_TYPE3),
	ZV(LIGHT0_X),
	ZV(LIGHT0_Y),
	ZV(LIGHT0_Z),
	ZV(LIGHT1_X),
	ZV(LIGHT1_Y),
	ZV(LIGHT1_Z),
	ZV(LIGHT2_X),
	ZV(LIGHT2_Y),
	ZV(LIGHT2_Z),
	ZV(LIGHT3_X),
	ZV(LIGHT3_Y),
	ZV(LIGHT3_Z),
	ZV(LIGHT0_DIRECTION_X),
	ZV(LIGHT0_DIRECTION_Y),
	ZV(LIGHT0_DIRECTION_Z),
	ZV(LIGHT1_DIRECTION_X),
	ZV(LIGHT1_DIRECTION_Y),
	ZV(LIGHT1_DIRECTION_Z),
	ZV(LIGHT2_DIRECTION_X),
	ZV(LIGHT2_DIRECTION_Y),
	ZV(LIGHT2_DIRECTION_Z),
	ZV(LIGHT3_DIRECTION_X),
	ZV(LIGHT3_DIRECTION_Y),
	ZV(LIGHT3_DIRECTION_Z),
	ZV(LIGHT0_CONSTANT_ATTEN),
	ZV(LIGHT0_LINEAR_ATTEN),
	ZV(LIGHT0_QUADRATIC_ATTEN),
	ZV(LIGHT1_CONSTANT_ATTEN),
	ZV(LIGHT1_LINEAR_ATTEN),
	ZV(LIGHT1_QUADRATIC_ATTEN),
	ZV(LIGHT2_CONSTANT_ATTEN),
	ZV(LIGHT2_LINEAR_ATTEN),
	ZV(LIGHT2_QUADRATIC_ATTEN),
	ZV(LIGHT3_CONSTANT_ATTEN),
	ZV(LIGHT3_LINEAR_ATTEN),
	ZV(LIGHT3_QUADRATIC_ATTEN),
	ZV(LIGHT0_EXPONENT_ATTEN),
	ZV(LIGHT1_EXPONENT_ATTEN),
	ZV(LIGHT2_EXPONENT_ATTEN),
	ZV(LIGHT3_EXPONENT_ATTEN),
	ZV(LIGHT0_CUTOFF_ATTEN),
	ZV(LIGHT1_CUTOFF_ATTEN),
	ZV(LIGHT2_CUTOFF_ATTEN),
	ZV(LIGHT3_CUTOFF_ATTEN),
	ZV(LIGHT0_AMBIENT),
	ZV(LIGHT0_DIFFUSE),
	ZV(LIGHT0_SPECULAR),
	ZV(LIGHT1_AMBIENT),
	ZV(LIGHT1_DIFFUSE),
	ZV(LIGHT1_SPECULAR),
	ZV(LIGHT2_AMBIENT),
	ZV(LIGHT2_DIFFUSE),
	ZV(LIGHT2_SPECULAR),
	ZV(LIGHT3_AMBIENT),
	ZV(LIGHT3_DIFFUSE),
	ZV(LIGHT3_SPECULAR),
	ZV(CULL),
	ZV(FRAME_BUF_PTR),
	ZV(FRAME_BUF_WIDTH),
	ZV(Z_BUF_PTR),
	ZV(Z_BUF_WIDTH),
	ZV(TEX_ADDR0),
	ZV(TEX_ADDR1),
	ZV(TEX_ADDR2),
	ZV(TEX_ADDR3),
	ZV(TEX_ADDR4),
	ZV(TEX_ADDR5),
	ZV(TEX_ADDR6),
	ZV(TEX_ADDR7),
	ZV(TEX_BUF_WIDTH0),
	ZV(TEX_BUF_WIDTH1),
	ZV(TEX_BUF_WIDTH2),
	ZV(TEX_BUF_WIDTH3),
	ZV(TEX_BUF_WIDTH4),
	ZV(TEX_BUF_WIDTH5),
	ZV(TEX_BUF_WIDTH6),
	ZV(TEX_BUF_WIDTH7),
	ZV(CLUT_BUF_PTR),
	ZV(CLUT_BUF_WIDTH),
	ZV(TRANSFER_SRC),
	ZV(TRANSFER_SRC_W),
	ZV(TRANSFER_DST),
	ZV(TRANSFER_DST_W),
	ZV(TEX_SIZE0),
	ZV(TEX_SIZE1),
	ZV(TEX_SIZE2),
	ZV(TEX_SIZE3),
	ZV(TEX_SIZE4),
	ZV(TEX_SIZE5),
	ZV(TEX_SIZE6),
	ZV(TEX_SIZE7),
	ZV(TEX_MAP_MODE),
	ZV(TEX_SHADE_MAPPING),
	ZV(TEX_MODE),
	ZV(TEX_FORMAT),
	ZV(CLUT_LOAD),
	ZV(CLUT_FORMAT),
	ZV(TEX_FILTER),
	ZV(TEX_WRAP),
	ZV(TEX_LEVEL),
	ZV(TEX_FUNC),
	ZV(TEX_ENV_COLOR),
	ZV(TEX_FLUSH),
	ZV(TEX_SYNC),
	ZV(FOG1),
	ZV(FOG2),
	ZV(FOG_COLOR),
	ZV(TEX_LOD_SLOPE),
	ZV(FRAMEBUF_PIX_FORMAT),
	ZV(CLEAR_MODE),
	ZV(SCISSOR1),
	ZV(SCISSOR2),
	ZV(MIN_Z),
	ZV(MAX_Z),
	ZV(COLOR_TEST),
	ZV(COLOR_REF),
	ZV(COLOR_TESTMASK),
	ZV(ALPHA_TEST),
	ZV(STENCIL_TEST),
	ZV(STENCIL_OP),
	ZV(Z_TEST),
	ZV(BLEND_MODE),
	ZV(BLEND_FIXED_A),
	ZV(BLEND_FIXED_B),
	ZV(DITH0),
	ZV(DITH1),
	ZV(DITH2),
	ZV(DITH3),
	ZV(LOGIC_OP),
	ZV(Z_MASK),
	ZV(MASK_COLOR),
	ZV(MASK_ALPHA),
	ZV(TRANSFER_SRC_OFFSET),
	ZV(TRANSFER_DST_OFFSET),
	ZV(TRANSFER_SIZE),

	ZV(FINISH),
	ZV(END),
};

static void sceGuResetGlobalVariables(void)
{
	unsigned int i;

	gu_init = 0;

	gu_states = 0;
	gu_object_stack_depth = 0;

	gu_display_on = GU_DISPLAY_OFF;
	gu_call_mode = GU_CALL_NORMAL;

	gu_draw_buffer.pixel_size = GU_PSM_5551;
	gu_draw_buffer.frame_width = GU_SCR_WIDTH;
	gu_draw_buffer.frame_buffer = 0;
	gu_draw_buffer.disp_buffer = 0;
	gu_draw_buffer.depth_buffer = 0;
	gu_draw_buffer.depth_width = 0;
	gu_draw_buffer.width = GU_SCR_WIDTH;
	gu_draw_buffer.height = GU_SCR_HEIGHT;

	for (i = 0; i < 3; ++i)
	{
		GuContext* context = &gu_contexts[i];

		context->scissor_enable = 0;
		context->scissor_start[0] = 0;
		context->scissor_start[1] = 0;
		context->scissor_end[0] = 0;
		context->scissor_end[1] = 0;

		context->near_plane = 0;
		context->far_plane = 1;

		context->depth_offset = 0;
		context->fragment_2x = 0;
		context->texture_function = 0;
		context->texture_proj_map_mode = 0;
		context->texture_map_mode = 0;
		context->sprite_mode[0] = 0;
		context->sprite_mode[1] = 0;
		context->sprite_mode[2] = 0;
		context->sprite_mode[3] = 0;
		context->clear_color = 0;
		context->clear_stencil = 0;
		context->clear_depth = 0xffff;
		context->texture_mode = 0;
	}

	gu_settings.sig = NULL;
	gu_settings.fin = NULL;
}

void callbackFin(int id, void *arg)
{
	GuSettings *settings = (GuSettings *)arg;
	if (settings->fin)
		settings->fin(id & 0xffff);
}

void callbackSig(int id, void *arg)
{
	GuSettings *settings = (GuSettings *)arg;

	settings->signal_history[(settings->signal_offset++) & 15] = id & 0xffff;

	if (settings->sig)
		settings->sig(id & 0xffff);

	sceKernelSetEventFlag(settings->kernel_event_flag, 1);
}

int sceGuInit(void)
{
#ifdef GU_DEBUG
	printf("sceGuInit();\n");
	assert(!gu_init && "GU already initialized");
#endif

	int res;
	PspGeCallbackData callback;

	ge_edram_address = sceGeEdramGetAddr();
#ifdef GU_DEBUG
	assert(ge_edram_address != NULL && "Failed to get EDRAM address");
#endif

	sceGuResetGlobalVariables();

	res = sceKernelCreateEventFlag("SceGuSignal", PSP_EVENT_WAITMULTIPLE, 3, 0);
	if (res < 0)
	{
#ifdef GU_DEBUG
		printf("Failed to create event flag: %d\n", res);
#endif
		return res;
	}
	gu_settings.kernel_event_flag = res;

	callback.signal_func = callbackSig;
	callback.signal_arg = &gu_settings;
	callback.finish_func = callbackFin;
	callback.finish_arg = &gu_settings;
	res = sceGeSetCallback(&callback);
	if (res < 0)
	{
#ifdef GU_DEBUG
		printf("Failed to set GE callback: %d\n", res);
#endif
		sceKernelDeleteEventFlag(gu_settings.kernel_event_flag);
		gu_settings.kernel_event_flag = -1;
		return res;
	}
	gu_settings.ge_callback_id = res;

	// initialize graphics hardware
	res = sceGeListEnQueue((void *)((unsigned int)ge_init_list & 0x1fffffff), NULL, gu_settings.ge_callback_id, NULL);
	if (res < 0)
	{
#ifdef GU_DEBUG
		printf("Failed to enqueue GE list: %d\n", res);
#endif
		sceKernelDeleteEventFlag(gu_settings.kernel_event_flag);
		sceGeUnsetCallback(gu_settings.ge_callback_id);
		gu_settings.ge_callback_id = -1;
		gu_settings.kernel_event_flag = -1;
		return res;
	}
	ge_list_executed[0] = res;
	// wait for init to complete
	sceGeListSync(ge_list_executed[0], 0);
	sceGeDrawSync(0);

	gu_settings.swapBuffersCallback = NULL;
	gu_settings.swapBuffersBehaviour = PSP_DISPLAY_SETBUF_NEXTHSYNC;

	gu_init = 1;
	return 0;
}
