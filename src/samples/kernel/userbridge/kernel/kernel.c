/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - A basic example for checking the GProf profiler.
 *
 * Copyright (c) 2025 Joel16 - joel16dev@gmail.com
 *
 */
#include <pspsdk.h>
#include <pspsysreg.h>

PSP_MODULE_INFO("kernel", PSP_MODULE_KERNEL, 1, 0);
PSP_NO_CREATE_MAIN_THREAD();

u32 pspSysregGetTachyonVersion(void) {
    u32 k1 = pspSdkSetK1(0);

    u32 ret = sceSysregGetTachyonVersion();
        
    pspSdkSetK1(k1);

    return ret;
}

int module_start(SceSize args, void *argp) {
    return 0;
}

int module_stop(void) {
    return 0;
}
