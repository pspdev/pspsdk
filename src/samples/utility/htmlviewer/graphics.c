
#include "graphics.h"

#include <pspgu.h>
#include <pspdisplay.h>

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

static char list[0x10000] __attribute__((aligned(64)));

void setupGu()
{
	sceGuInit();

	sceGuStart(GU_DIRECT, list);
	sceGuDrawBuffer(GU_PSM_8888, 0, BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, (void*)0x88000, BUF_WIDTH);
	sceGuDepthBuffer((void*)0x110000, BUF_WIDTH);

	sceGuOffset(0, 0);

	sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);

	sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
	sceGuEnable(GU_BLEND);

	sceGuClearColor(0);
	sceGuClearDepth(0);
	sceGuClearStencil(0);

	sceGuFinish();
	sceGuSync(0, 0);
	
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);
}

void draw()
{
	sceGuStart(GU_DIRECT, list);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_STENCIL_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	sceGuFinish();
	sceGuSync(0, 0);	
}