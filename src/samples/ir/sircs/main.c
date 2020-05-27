/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Infrared Remote example
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Matthew H <matthewh@webone.com.au>
 *
 * $$
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspsircs.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("SIRCS", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

// sircs commands are easily found in lirc
// - interpret as described at 
//   http://sourceforge.net/mailarchive/message.php?msg_id=8833252

#define SIRCS_ADDR_DVD	0x1b5a
#define SIRCS_CMD_RESET	0x15
#define SIRCS_CMD_PLAY	0x32
#define SIRCS_CMD_PAUSE	0x39

void send_code(int type, int dev, int cmd) 
{
	struct sircs_data sd;
	int ret;
	int count = 20; // this seems like a good number

	sd.type = type;
	sd.cmd = cmd & 0x7f;
	sd.dev = dev & 0x1fff;

	ret = sceSircsSend(&sd, count); 
	if (ret < 0) 
	{
		printf ("sceSircsSend returned %d\n", ret);
	}
}

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	sceKernelExitGame();

	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
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

int main(void)
{
	SceCtrlData pad;
	u32 buttonsold = 0;
	int sirc_bits = 20; // # of bits in code, choose from 12, 15 or 20

	SetupCallbacks();
	pspDebugScreenInit();

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

	printf ("Sircs Example\n");
        printf ("-------\n");
	printf ("This example can be used with a PS2\n\n");
        printf ("Press CROSS to send PLAY\n");
        printf ("Press SQUARE to send PAUSE\n");
        printf ("Press CIRCLE to send RESET\n");

	do {
		sceCtrlReadBufferPositive(&pad, 1);

		if (pad.Buttons != buttonsold) 
		{

			if (pad.Buttons & PSP_CTRL_CIRCLE) 
			{
				printf ("Sending SIRCS_CMD_RESET\n");
				send_code(sirc_bits, SIRCS_ADDR_DVD, SIRCS_CMD_RESET);
			}

			if (pad.Buttons & PSP_CTRL_CROSS) 
			{
				printf ("Sending SIRCS_CMD_PLAY\n");
				send_code(sirc_bits, SIRCS_ADDR_DVD, SIRCS_CMD_PLAY);
			}

			if (pad.Buttons & PSP_CTRL_SQUARE)
			{
				printf ("Sending SIRCS_CMD_PAUSE\n");
				send_code(sirc_bits, SIRCS_ADDR_DVD, SIRCS_CMD_PAUSE);
			}

			buttonsold = pad.Buttons;
		}

		sceDisplayWaitVblankStart(); 
	} while (1);

	return 0;
}
