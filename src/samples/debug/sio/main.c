/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic sample to demonstrate the remote port sio.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspsdk.h>
#include <pspctrl.h>
#include <stdio.h>
#include <string.h>

PSP_MODULE_INFO("REMOTE", 0x1000, 1, 1);
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(0);

int main(void)
{
	pspDebugScreenInit();

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	/* Initialise SIO and install a kprintf handler */
	pspDebugSioInit();
	pspDebugSioInstallKprintf();

	/* Install a stdout handler */
	pspDebugInstallStdoutHandler(pspDebugSioPutData);

	Kprintf("Hi from %s!\n", "Kprintf");
	printf("Also hi from stdio\r\n");

	pspDebugScreenPrintf("Press X to exit, tap away on your terminal to echo\n");
	sceDisplayWaitVblankStart();

	while(1)
	{
		SceCtrlData pad;
		int ch;

		sceCtrlReadBufferPositive(&pad, 1);
		if(pad.Buttons & PSP_CTRL_CROSS)
		{
			break;
		}

		ch = pspDebugSioGetchar();
		if(ch >= 0)
		{
			pspDebugScreenPrintf("Received %d\n", ch);
			if(ch == '\r')
			{
				pspDebugSioPutchar('\r');
				pspDebugSioPutchar('\n');
			}
			else
			{
				pspDebugSioPutchar(ch);
			}
		}

		sceDisplayWaitVblankStart();
	}

	sceKernelExitGame();

	return 0;
}
