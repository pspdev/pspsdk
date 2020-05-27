/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Sample to demonstrate proper use of the power library
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <stdio.h>
#include <pspmoduleinfo.h>
#include <psppower.h>

/* Define the module info section */
PSP_MODULE_INFO("PowerTest", 0, 0, 71);

char powerCBMessage[256];

/* Define printf, just to make typing easier */
#define printf  pspDebugScreenPrintf

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
    sceKernelExitGame();

	return 0;
}

/* Power Callback */
int power_callback(int unknown, int pwrflags, void *common)
{
    /* check for power switch and suspending as one is manual and the other automatic */
    if (pwrflags & PSP_POWER_CB_POWER_SWITCH || pwrflags & PSP_POWER_CB_SUSPENDING) {
	sprintf(powerCBMessage,
		"first arg: 0x%08X, flags: 0x%08X: suspending\n", unknown, pwrflags);
    } else if (pwrflags & PSP_POWER_CB_RESUMING) {
	sprintf(powerCBMessage,
		"first arg: 0x%08X, flags: 0x%08X: resuming from suspend mode\n",
		unknown, pwrflags);
    } else if (pwrflags & PSP_POWER_CB_RESUME_COMPLETE) {
	sprintf(powerCBMessage,
		"first arg: 0x%08X, flags: 0x%08X: resume complete\n", unknown, pwrflags);
    } else if (pwrflags & PSP_POWER_CB_STANDBY) {
	sprintf(powerCBMessage,
		"first arg: 0x%08X, flags: 0x%08X: entering standby mode\n", unknown, pwrflags);
    } else {
	sprintf(powerCBMessage, "first arg: 0x%08X, flags: 0x%08X: Unhandled power event\n", unknown, pwrflags);
    }
    sceDisplayWaitVblankStart();

	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
    int cbid;
    cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    cbid = sceKernelCreateCallback("Power Callback", power_callback, NULL);
    scePowerRegisterCallback(0, cbid);
    sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
    int thid = 0;
    thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
    if (thid >= 0)
	sceKernelStartThread(thid, 0, 0);
    return thid;
}

/* main routine */
int main(int argc, char *argv[])
{
    SceCtrlData pad;
    int i = 0;
    int powerLocked = 0;
    int powerTicks = 0;
    u32 oldButtons = 0;
    int batteryLifeTime = 0;
    
    //init screen and callbacks
    pspDebugScreenInit();
    pspDebugScreenClear();
    SetupCallbacks();

    // Setup Pad
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(0);

    //fetch and print out power and battery information
    for (;;) {
    	/* fix so the screen lines up right if the battery disappears */
    	if (!scePowerIsBatteryExist()) {
	    pspDebugScreenClear();
    	}
    	
	pspDebugScreenSetXY(0, 0);
	printf("PSP Power Sample v1.0 by John_K\n\n");
	sceCtrlReadBufferPositive(&pad, 1);

	printf("External Power: %s\n", scePowerIsPowerOnline()? "yes" : "no ");
	printf("%-14s: %s\n", "Battery", scePowerIsBatteryExist()? "present" : "absent ");

	if (scePowerIsBatteryExist()) {
	    printf("%-14s: %s\n", "Low Charge", scePowerIsLowBattery()? "yes" : "no ");
	    printf("%-14s: %s\n", "Charging", scePowerIsBatteryCharging()? "yes" : "no ");
	    batteryLifeTime = scePowerGetBatteryLifeTime();
	    printf("%-14s: %d%% (%02dh%02dm)     \n", "Charge",
		   scePowerGetBatteryLifePercent(), batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60));
	    printf("%-14s: %0.3fV\n", "Volts", (float) scePowerGetBatteryVolt() / 1000.0);
	    printf("%-14s: %d deg C\n", "Battery Temp", scePowerGetBatteryTemp());
	} else
	    printf("Battery stats unavailable\n");

	printf("%-14s: %d mHz\n", "CPU Speed", scePowerGetCpuClockFrequency());
	printf("%-14s: %d mHz\n", "Bus Speed", scePowerGetBusClockFrequency());
	printf("%-14s: %s       \n", "Power Switch", powerLocked == 0 ? "unlocked" : "locked");
	printf("%-14s: %s  \n", "Send Ticks", powerTicks == 1 ? "yes" : "no");
	printf("\nPress X to switch CPU between 333 and 222 mHz\n");
	printf("Press O to toggle power switch lock\n");
	printf("Press [] to toggle sending power ticks\n");
	//send powerTicks if enabled
	if (powerTicks == 1)
	    if (scePowerTick(0) != 0)
		printf("Error calling  scePowerTick(0)\n");

	//only check buttons if they've changed since last frame
	if (oldButtons != pad.Buttons) {
	    //check to see if the user pressed X to toggle CPU speed
	    if (pad.Buttons & PSP_CTRL_CROSS) {
		if (i == 0) {
		    i = scePowerSetClockFrequency(333, 333, 166);
		    if (i == 0) {
			i = 1;
		    } else {
			printf("\nCould not set CPU to 333mHz (0x%08X)\n", i);
			i = 0;
		    }
		} else {
		    i = scePowerSetClockFrequency(222, 222, 111);
		    if (i != 0) {
			printf("\nCould not set CPU to 222mHz (0x%08X)\n", i);
			i = 1;
		    }
		}
	    }
	    //check to see if the user pressed O to toggle power locking
	    if (pad.Buttons & PSP_CTRL_CIRCLE) {
		if (powerLocked == 0) {
		    if (scePowerLock(0) == 0)
			powerLocked = 1;
		    else
			printf("Error locking power switch\n");
		} else {
		    if (scePowerUnlock(0) == 0)
			powerLocked = 0;
		    else
			printf("Error unlocking power switch\n");
		}
	    }
	    //check to see if the user pressed [] to toggle PowerTicks
	    if (pad.Buttons & PSP_CTRL_SQUARE)
		powerTicks = powerTicks == 1 ? 0 : 1;
	}

	pspDebugScreenSetXY(0, 30);
	printf("Power callback messages appear below:\n%s\n", powerCBMessage);
	oldButtons = pad.Buttons;

	sceDisplayWaitVblankStart();
    }

    sceKernelSleepThread();
    sceKernelExitGame();

    return 0;
}
