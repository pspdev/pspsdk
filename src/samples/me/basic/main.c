/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - A basic example of getting code onto the ME. This was based on
 * the sample code written by crazyc on the pspdev forums.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("mebasic", 0x1000, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(0);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

void me_run(void);
void me_end(void);

int main(int argc, char *argv[])
{
	SceCtrlData ctl;

	pspDebugScreenInit();

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

	/* Copy our small program into the ME reset vector */
	memcpy((void *)0xbfc00040, me_run, (int)(me_end - me_run));
	sceKernelDcacheWritebackInvalidateAll();

	sceSysregMeResetEnable();
	sceSysregMeBusClockEnable();
	sceSysregMeResetDisable();
	sceSysregVmeResetDisable(); 

	while(1)
	{
		volatile u32 *count = (u32*) 0xBFC00060;

		pspDebugScreenSetXY(0, 0);
		pspDebugScreenPrintf("ME Basic Example, press Home to exit\n");
		sceKernelDcacheWritebackInvalidateAll();
		pspDebugScreenPrintf("ME Counter: %08x\n", *count);
		sceCtrlReadBufferPositive(&ctl, 1);
		if(ctl.Buttons & PSP_CTRL_HOME)
		{
			sceKernelExitGame();
		}

		sceDisplayWaitVblankStart();
	}

	return 0;
}
