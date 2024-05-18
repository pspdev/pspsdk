#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <pspgu.h>
#include <pspgum.h>

PSP_MODULE_INFO("SceGu Cube", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
	float u, v;
	unsigned int color;
	float x,y,z;
};

struct Vertex __attribute__((aligned(16))) vertices[12*3] =
{
	{0, 0, 0xff7f0000,-1,-1, 1}, // 0
	{1, 0, 0xff7f0000,-1, 1, 1}, // 4
	{1, 1, 0xff7f0000, 1, 1, 1}, // 5

	{0, 0, 0xff7f0000,-1,-1, 1}, // 0
	{1, 1, 0xff7f0000, 1, 1, 1}, // 5
	{0, 1, 0xff7f0000, 1,-1, 1}, // 1

	{0, 0, 0xff7f0000,-1,-1,-1}, // 3
	{1, 0, 0xff7f0000, 1,-1,-1}, // 2
	{1, 1, 0xff7f0000, 1, 1,-1}, // 6

	{0, 0, 0xff7f0000,-1,-1,-1}, // 3
	{1, 1, 0xff7f0000, 1, 1,-1}, // 6
	{0, 1, 0xff7f0000,-1, 1,-1}, // 7

	{0, 0, 0xff007f00, 1,-1,-1}, // 0
	{1, 0, 0xff007f00, 1,-1, 1}, // 3
	{1, 1, 0xff007f00, 1, 1, 1}, // 7

	{0, 0, 0xff007f00, 1,-1,-1}, // 0
	{1, 1, 0xff007f00, 1, 1, 1}, // 7
	{0, 1, 0xff007f00, 1, 1,-1}, // 4

	{0, 0, 0xff007f00,-1,-1,-1}, // 0
	{1, 0, 0xff007f00,-1, 1,-1}, // 3
	{1, 1, 0xff007f00,-1, 1, 1}, // 7

	{0, 0, 0xff007f00,-1,-1,-1}, // 0
	{1, 1, 0xff007f00,-1, 1, 1}, // 7
	{0, 1, 0xff007f00,-1,-1, 1}, // 4

	{0, 0, 0xff00007f,-1, 1,-1}, // 0
	{1, 0, 0xff00007f, 1, 1,-1}, // 1
	{1, 1, 0xff00007f, 1, 1, 1}, // 2

	{0, 0, 0xff00007f,-1, 1,-1}, // 0
	{1, 1, 0xff00007f, 1, 1, 1}, // 2
	{0, 1, 0xff00007f,-1, 1, 1}, // 3

	{0, 0, 0xff00007f,-1,-1,-1}, // 4
	{1, 0, 0xff00007f,-1,-1, 1}, // 7
	{1, 1, 0xff00007f, 1,-1, 1}, // 6

	{0, 0, 0xff00007f,-1,-1,-1}, // 4
	{1, 1, 0xff00007f, 1,-1, 1}, // 6
	{0, 1, 0xff00007f, 1,-1,-1}, // 5
};

int done = 0;
/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *arg)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();
	return cbid;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

extern void SpharmGenTest(int rendermode);
unsigned char *convertimage(unsigned char *inptr,int size);

extern unsigned char logo_start[];

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

unsigned char *logo_temp2;

//  from disablefpu.S
extern void _DisableFPUExceptions(void);

int main(int argc, char* argv[])
{
  SceCtrlData pad;
  unsigned int buttonsold = 0;
  int rendermode = 0;
	int i = 0;
	int val = 0;

  _DisableFPUExceptions();

	pspDebugScreenInit();
	//printf("Bootpath: %s\n", g_elf_name);
	SetupCallbacks();

  // Setup Pad
  sceCtrlSetSamplingCycle(0);
  sceCtrlSetSamplingMode(0);

	sceGuInit();

	printf("INIT OK\n");

  logo_temp2 = convertimage(logo_start,64);

	// setup
	sceGuStart(0,list);
	sceGuDrawBuffer(GU_PSM_8888,(void*)0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,(void*)0x88000,BUF_WIDTH);
	sceGuDepthBuffer((void*)0x110000,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(0xc350,0x2710);//0xc350=50000  0x2710=10000
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuBlendFunc(0,2,3,0,0);
	sceGuEnable(GU_BLEND);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuShadeModel(GU_SMOOTH);
	sceGuFrontFace(GU_CW); // NOTE: not CCW
	sceGuEnable(GU_CULL_FACE);
	//sceGuEnable(GU_STATE_TEXTURE);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(1);

  sceCtrlReadBufferPositive(&pad, 1);
  buttonsold = pad.Buttons;


	while (!done)
	{
		unsigned int x,y;

		sceGuStart(0,list);

		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		val++;

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f,16.0/9.0f,1.0f,1000.0f);

		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		sceGumMatrixMode(GU_TEXTURE);
		sceGumLoadIdentity();

		sceGumMatrixMode(GU_MODEL);
		{
			ScePspFVector3 pos = {-6.5f,-3.5f,-7.0f};
			ScePspFVector3 rot = {val * 0.79f * (GU_PI/180.0f), val * 0.98f * (GU_PI/180.0f), val * 1.32f * (GU_PI/180.0f)};

			sceGumLoadIdentity();
			sceGumTranslate(&pos);
			sceGumRotateXYZ(&rot);
		}

    sceGuTexMode(GU_PSM_8888,0,0,0);
    sceGuTexImage(0,64,64,64,logo_temp2);
	  sceGuTexFunc(GU_TFX_ADD,GU_TCC_RGB);
	  sceGuTexFilter(GU_LINEAR,GU_LINEAR);
	  sceGuTexScale(1.0f,1.0f);
	  sceGuTexOffset(0.0f,0.0f);
	  sceGuAmbientColor(0xff101010);

    sceGuTexMapMode(0,0,0);
    sceGuDisable(GU_LIGHTING);
    sceGuEnable(GU_TEXTURE_2D);

    sceGumDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,12*3,0,vertices);

    // now for the spherical harmonics
	sceGumMatrixMode(GU_MODEL);
	{
		ScePspFVector3 pos = {0,0,-130.0f};
		ScePspFVector3 rot = {val * 0.79f * (GU_PI/180.0f), val * 0.98f * (GU_PI/180.0f), val * 1.32f * (GU_PI/180.0f)};

		sceGumLoadIdentity();
		sceGumTranslate(&pos);
		sceGumRotateXYZ(&rot);
	}
		sceGuFinish();
		//sceGuSync(0,0);

    SpharmGenTest(rendermode);

    sceCtrlReadBufferPositive(&pad, 1);
    if (buttonsold != pad.Buttons) {
      if (pad.Buttons & PSP_CTRL_LEFT) {
        if (rendermode > 0) rendermode--;
      }
      if (pad.Buttons & PSP_CTRL_RIGHT) {
        if (rendermode < 9) rendermode++;
      }
      if (pad.Buttons & PSP_CTRL_UP) {
        rendermode = 0;
      }
      if (pad.Buttons & PSP_CTRL_DOWN) {
        rendermode = 9;
      }
    }
    buttonsold = pad.Buttons;

    sceGuSync(0,0);
    sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
