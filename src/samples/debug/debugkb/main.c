/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  debugkb.c - Example of a simple screen debug keyboard
 *
 * Copyright (c) 2006 Mike Mallett <mike@nerdcore.net>
 *
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pspdebugkb.h>

/* Define the module info section */
PSP_MODULE_INFO("Debug Screen Text Input", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#define printf pspDebugScreenPrintf
#define setXY pspDebugScreenSetXY
#define setTextColor pspDebugScreenSetTextColor
#define setBackColor pspDebugScreenSetBackColor

/* Exit callback */
int exit_callback()
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

  thid = sceKernelCreateThread("update_thread", CallbackThread,
			       0x11, 0xFA0, 0, 0);
  if(thid >= 0)
    {
      sceKernelStartThread(thid, 0, 0);
    }

  return thid;
}


int main(void)
{
  SetupCallbacks();

  pspDebugScreenInit();

  printf ("Debug Screen Text Input Box\n");
  printf("Press Left Trigger and Right Trigger to bring up the keyboard.\n");

  char str[PSP_DEBUG_KB_MAXLEN];
  bzero(str, PSP_DEBUG_KB_MAXLEN);

  sceCtrlSetSamplingCycle(0);
  sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

  SceCtrlData input;

  while (1) {
    sceCtrlReadBufferPositive(&input, 1);

    if (input.Buttons & PSP_CTRL_LTRIGGER && input.Buttons & PSP_CTRL_RTRIGGER) {
      pspDebugKbInit(str);

      setTextColor(0xffffffff);
      setBackColor(0x00000000);
      setXY(0, 3);
      printf("str = \"%s\"", str);
      setXY(0, 4);
      printf("str is %d characters long", strlen(str));
    }
  }

  sceKernelSleepThread();

  sceKernelExitGame();
  return 0;
}
