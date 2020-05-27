/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic SysEvent handler example
 *
 * Copyright (c) 2007 Iaroslav Gaponenko <adrahil@gmail.com>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsysevent.h>
#define printf pspDebugScreenPrintf
 
/* Define the module info section */
PSP_MODULE_INFO("template", 0x1000, 1, 1);
 
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(0);
 
//This is the handler for the event.
int my_handler(int ev_id, char* ev_name, void* param, int* result){
  //we won't do anything special, just print the event number and name.
  pspDebugScreenPrintf("Event number 0x%x (%s)\n", ev_id, ev_name);
 
  //return 0 if the event should not be stopped (it has to be configured as breakable before in order to do so: set break_nonzero to 1.
  return 0;
}
 
int main(int argc, char *argv[])
{
	int ret;
 
	//This is the initialisation part for the event handler. 
	PspSysEventHandler events;
	//structure size. mandatory 0x40.
	events.size = 0x40;
	//name which can be used for debugging purposes.
        events.name = "MyEventGrabber";
	//mask
	events.type_mask = 0x0000000F;
	//pointer to the handler function.
	events.handler = my_handler;
 
	pspDebugScreenInit();
	pspDebugScreenPrintf("Loaded app...\n");
 
	//register the system event handler.
	ret = sceKernelRegisterSysEventHandler(&events);
	pspDebugScreenPrintf("Registered handler. Return: %i\n", ret);
	sceKernelDelayThreadCB(1000000);
 
	//Dispatch a few test events to see if it works.
 
	ret = sceKernelSysEventDispatch(0x0000000F, 0x123, "pspsdk", NULL, NULL, 0, NULL);
	pspDebugScreenPrintf("Sending event 1. Return: %i\n", ret);
	sceKernelDelayThreadCB(1000000);
	ret = sceKernelSysEventDispatch(0x0000000F, 0x456, "rules", NULL, NULL, 0, NULL);
	pspDebugScreenPrintf("Sending event 2. Return: %i\n", ret);
	sceKernelDelayThreadCB(1000000);
	ret = sceKernelSysEventDispatch(0x0000000F, 0x789, "the world", NULL, NULL, 0, NULL);
	pspDebugScreenPrintf("Sending event 3. Return: %i\n", ret);
 
	//wait till the end of time.
	while(1){
		sceKernelDelayThreadCB(1000000);
	}
	return 0;
}
