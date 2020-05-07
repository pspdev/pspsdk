/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Simple Systimer example
 *
 * Copyright (c) 2007 Iaroslav Gaponenko <adrahil@gmail.com>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include "pspsystimer.h"

#define printf pspDebugScreenPrintf

/* Define the module info section */
PSP_MODULE_INFO("systimer", 0x1000, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_VFPU);

SceSysTimerId timer;
int tic = 0;

int my_tick_handler(void){
  static int div;
  div++;
  //arrange to get more or less seconds...
  if(div > 12){
    div = 0;
    if(tic){
      pspDebugScreenPrintf("Tac!\n");
    }else{
      pspDebugScreenPrintf("Tic!\n");
    }
    tic = ~tic;
  }
  return -1;
}

int main(int argc, char *argv[]) {

  pspDebugScreenInit();
  pspDebugScreenPrintf("SysTimer sample by Adrahil.\n");

  timer = sceSTimerAlloc();
  sceSTimerStartCount(timer);
  sceSTimerSetHandler(timer, 4194303, my_tick_handler, 0);

  sceKernelSleepThreadCB();
  return 0;

} 
