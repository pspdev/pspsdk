#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <string.h>
#include <psputility.h>

PSP_MODULE_INFO("OSK Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static int done = 0;

int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
	
	return 0;
}

int CallbackThread(SceSize args, void *argp)
{
	int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	
	return 0;
}

int SetupCallbacks(void)
{
	int thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, PSP_THREAD_ATTR_USER, 0);
	
	if(thid >= 0)
		sceKernelStartThread(thid, 0, 0);

	return thid;
}

static unsigned int __attribute__((aligned(16))) list[262144];

#define BUF_WIDTH	(512)
#define SCR_WIDTH	(480)
#define SCR_HEIGHT	(272)
#define PIXEL_SIZE	(4)
#define FRAME_SIZE	(BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE	(BUF_WIDTH SCR_HEIGHT * 2)

#define NUM_INPUT_FIELDS	(3)
#define TEXT_LENGTH			(128)

int main(int argc, char* argv[])
{
	SetupCallbacks();

	sceGuInit();
	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,(void*)0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,(void*)0x88000,BUF_WIDTH);
	sceGuDepthBuffer((void*)0x110000,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(0xc350,0x2710);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_FLAT);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);
	
	unsigned short intext[NUM_INPUT_FIELDS][TEXT_LENGTH];
	unsigned short outtext[NUM_INPUT_FIELDS][TEXT_LENGTH];
	unsigned short desc[NUM_INPUT_FIELDS][TEXT_LENGTH];
	
	memset(&intext, 0, NUM_INPUT_FIELDS * TEXT_LENGTH * sizeof(unsigned short));
	memset(&outtext, 0, NUM_INPUT_FIELDS * TEXT_LENGTH * sizeof(unsigned short));
	memset(&desc, 0, NUM_INPUT_FIELDS * TEXT_LENGTH * sizeof(unsigned short));
	
	int i;
	
	for(i = 0;i < NUM_INPUT_FIELDS;i++)
	{
		desc[i][0] = 'F';
		desc[i][1] = 'i';
		desc[i][2] = 'e';
		desc[i][3] = 'l';
		desc[i][4] = 'd';
		desc[i][5] = ' ';
		desc[i][6] = i + 48 + 1; // Convert i to ASCII value.
		desc[i][7] = 0;
		
		intext[i][0] = 'T';
		intext[i][1] = 'e';
		intext[i][2] = 'x';
		intext[i][3] = 't';
		intext[i][4] = ' ';
		intext[i][5] = i + 48 + 1; // Convert i to ASCII value.
		intext[i][6] = 0;
		
	}

	SceUtilityOskData data[NUM_INPUT_FIELDS];
	
	for(i = 0; i < NUM_INPUT_FIELDS;i++)
	{
		memset(&data[i], 0, sizeof(SceUtilityOskData));
		data[i].language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT; // Use system default for text input
		data[i].lines = 1;
		data[i].unk_24 = 1;
		data[i].inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL; // Allow all input types
		data[i].desc = desc[i];
		data[i].intext = intext[i];
		data[i].outtextlength = TEXT_LENGTH;
		data[i].outtextlimit = 32; // Limit input to 32 characters
		data[i].outtext = outtext[i];
	}
	
	SceUtilityOskParams params;
	memset(&params, 0, sizeof(params));
	params.base.size = sizeof(params);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.base.language);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.base.buttonSwap);
	params.base.graphicsThread = 17;
	params.base.accessThread = 19;
	params.base.fontThread = 18;
	params.base.soundThread = 16;
	params.datacount = NUM_INPUT_FIELDS;
	params.data = data;

	sceUtilityOskInitStart(&params);

	while(!done)
	{
		sceGuStart(GU_DIRECT,list);
		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		sceGuFinish();
		sceGuSync(0,0);

		switch(sceUtilityOskGetStatus())
		{
			case PSP_UTILITY_DIALOG_INIT:
				break;
			
			case PSP_UTILITY_DIALOG_VISIBLE:
				sceUtilityOskUpdate(1);
				break;
			
			case PSP_UTILITY_DIALOG_QUIT:
				sceUtilityOskShutdownStart();
				break;
			
			case PSP_UTILITY_DIALOG_FINISHED:
				break;
				
			case PSP_UTILITY_DIALOG_NONE:
				done = 1;
				
			default :
				break;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}

	pspDebugScreenInit();
	pspDebugScreenSetXY(0, 0);
	
	int j;
	
	for(i = 0; i < NUM_INPUT_FIELDS;i++)
	{
		pspDebugScreenPrintf("Field %d: ", i+1);
		
		switch(data[i].result)
		{
			case PSP_UTILITY_OSK_RESULT_UNCHANGED:
				pspDebugScreenPrintf("UNCHANGED: ");
				break;
			
			case PSP_UTILITY_OSK_RESULT_CANCELLED:
				pspDebugScreenPrintf("CANCELLED: ");
				break;
				
			case PSP_UTILITY_OSK_RESULT_CHANGED:
				pspDebugScreenPrintf("CHANGED: ");
				break;
				
			default:
				break;
		}
		
		for(j = 0; data[i].outtext[j]; j++)
		{
			unsigned c = data[i].outtext[j];
			
			if(32 <= c && c <= 127) // print ascii only
				pspDebugScreenPrintf("%c", data[i].outtext[j]);
		}
		
		pspDebugScreenPrintf("\n");
	}

	done = 0;

	while(!done)
		sceKernelDelayThread(1000);	

	sceGuTerm();
	
	sceKernelExitGame();

	return 0;
}
