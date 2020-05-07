/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - PRX MS insert/eject callback usage sample
 *
 * Copyright (c) 2006 Iaroslav Gaponenko <adrahil@gmail.com>
 *
 */
#include <pspkernel.h>
#include <stdio.h>
#include <pspmscm.h>
 
/* Define the module info section */
PSP_MODULE_INFO("MS CB Sample", 0, 1, 1);
 
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
 
int ms_callback(int arg1, int arg2, void *arg)
{
    if (arg2 == MS_CB_EVENT_INSERTED){
        printf("Memory Stick (c) has been inserted.\n");
    } else if (arg2 == MS_CB_EVENT_EJECTED){
        printf("Memory Stick (c) has been ejected.\n");
    }
    return 0;
}
 
int main(int argc, char *argv[])
{
    SceUID cb_id;
 
    cb_id = sceKernelCreateCallback("MSCB", ms_callback, NULL);
    printf("================================================\n");
    printf("Memory Stick (c) insert/eject callback sample.\n");
    printf("Adrahil (c) 2006, thanks to TyRaNiD, dot_blank\n");
    printf("\n");
    printf("\n");
    printf("================================================\n");
    printf("Created callback %08X\n", cb_id);
    printf("Registering callback %08X\n", MScmRegisterMSInsertEjectCallback(cb_id));
    printf("================================================\n");
    printf("Please remove your Memory Stick (c) now!\n");
    printf("\n");
 
    sceKernelSleepThreadCB();
 
    //This will not be reached, as the instruction above sleeps the thread, and since this is a one-thread application.
    // Nevertheless, this shows how to unregister the callback in case one needs it.
    MScmUnregisterMSInsertEjectCallback(cb_id);
    return 0;
}
