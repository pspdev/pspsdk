/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psppower.h - Prototypes for the scePower library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 David Perry <tias_dp@hotmail.com>
 *
 * $Id: psppower.h 2433 2008-10-15 10:00:27Z iwn $
 */
#ifndef __POWER_H__
#define __POWER_H__

#include <pspkerneltypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Power callback flags
 */
 /*indicates the power switch it pushed, putting the unit into suspend mode*/
#define PSP_POWER_CB_POWER_SWITCH	0x80000000
/*indicates the hold switch is on*/
#define PSP_POWER_CB_HOLD_SWITCH	0x40000000
/*what is standby mode?*/
#define PSP_POWER_CB_STANDBY		0x00080000
/*indicates the resume process has been completed (only seems to be triggered when another event happens)*/
#define PSP_POWER_CB_RESUME_COMPLETE	0x00040000
/*indicates the unit is resuming from suspend mode*/
#define PSP_POWER_CB_RESUMING		0x00020000
/*indicates the unit is suspending, seems to occur due to inactivity*/
#define PSP_POWER_CB_SUSPENDING		0x00010000
/*indicates the unit is plugged into an AC outlet*/
#define PSP_POWER_CB_AC_POWER		0x00001000
/*indicates the battery charge level is low*/
#define PSP_POWER_CB_BATTERY_LOW	0x00000100
/*indicates there is a battery present in the unit*/
#define PSP_POWER_CB_BATTERY_EXIST	0x00000080
/*unknown*/
#define PSP_POWER_CB_BATTPOWER		0x0000007F

/**
 * Power tick flags
 */
/* All */
#define PSP_POWER_TICK_ALL		0
/* Suspend */
#define PSP_POWER_TICK_SUSPEND	1
/* Display */
#define PSP_POWER_TICK_DISPLAY	6

/**
 * Power Callback Function Definition
 *
 * @param unknown - unknown function, appears to cycle between 1,2 and 3
 * @param powerInfo - combination of PSP_POWER_CB_ flags
 */
typedef void (*powerCallback_t)(int unknown, int powerInfo);

/**
 * Register Power Callback Function
 *
 * @param slot - slot of the callback in the list, 0 to 15, pass -1 to get an auto assignment.
 * @param cbid - callback id from calling sceKernelCreateCallback
 *
 * @return 0 on success, the slot number if -1 is passed, < 0 on error.
 */
int scePowerRegisterCallback(int slot, SceUID cbid);

/**
 * Unregister Power Callback Function
 *
 * @param slot - slot of the callback
 *
 * @return 0 on success, < 0 on error.
 */
int scePowerUnregisterCallback(int slot);

/**
 * Check if unit is plugged in
 *
 * @return 1 if plugged in, 0 if not plugged in, < 0 on error.
 */
int scePowerIsPowerOnline(void);

/**
 * Check if a battery is present
 *
 * @return 1 if battery present, 0 if battery not present, < 0 on error.
 */
int scePowerIsBatteryExist(void);

/**
 * Check if the battery is charging
 *
 * @return 1 if battery charging, 0 if battery not charging, < 0 on error.
 */
int scePowerIsBatteryCharging(void);

/**
 * Get the status of the battery charging
 */
int scePowerGetBatteryChargingStatus(void);

/**
 * Check if the battery is low
 *
 * @return 1 if the battery is low, 0 if the battery is not low, < 0 on error.
 */
int scePowerIsLowBattery(void);

/**
 * Get battery life as integer percent
 *
 * @return Battery charge percentage (0-100), < 0 on error.
 */
int scePowerGetBatteryLifePercent(void);

/**
 * Get battery life as time
 *
 * @return Battery life in minutes, < 0 on error.
 */
int scePowerGetBatteryLifeTime(void);

/**
 * Get temperature of the battery
 */
int scePowerGetBatteryTemp(void);

/**
 * unknown? - crashes PSP in usermode
 */
int scePowerGetBatteryElec(void);

/**
 * Get battery volt level
 */
int scePowerGetBatteryVolt(void);

/**
 * Set CPU Frequency
 * @param cpufreq - new CPU frequency, valid values are 1 - 333
 */
int scePowerSetCpuClockFrequency(int cpufreq);

/**
 * Set Bus Frequency
 * @param busfreq - new BUS frequency, valid values are 1 - 167
 */
int scePowerSetBusClockFrequency(int busfreq);

/**
 * Alias for scePowerGetCpuClockFrequencyInt
 * @return frequency as int
 */
int scePowerGetCpuClockFrequency(void);

/**
 * Get CPU Frequency as Integer
 * @return frequency as int
 */
int scePowerGetCpuClockFrequencyInt(void);

/**
 * Get CPU Frequency as Float
 * @return frequency as float
 */
float scePowerGetCpuClockFrequencyFloat(void);

/**
 * Alias for scePowerGetBusClockFrequencyInt
 * @return frequency as int
 */
int scePowerGetBusClockFrequency(void);

/**
 * Get Bus fequency as Integer
 * @return frequency as int
 */
int scePowerGetBusClockFrequencyInt(void);

/**
 * Get Bus frequency as Float
 * @return frequency as float
 */
float scePowerGetBusClockFrequencyFloat(void);

/**
 * Set Clock Frequencies
 *
 * @param pllfreq - pll frequency, valid from 19-333
 * @param cpufreq - cpu frequency, valid from 1-333
 * @param busfreq - bus frequency, valid from 1-167
 * 
 * and:
 * 
 * cpufreq <= pllfreq
 * busfreq*2 <= pllfreq
 *
 */
int scePowerSetClockFrequency(int pllfreq, int cpufreq, int busfreq);

/**
 * Lock power switch
 *
 * Note: if the power switch is toggled while locked
 * it will fire immediately after being unlocked.
 *
 * @param unknown - pass 0
 *
 * @return 0 on success, < 0 on error.
 */
int scePowerLock(int unknown);

/**
 * Unlock power switch
 *
 * @param unknown - pass 0
 *
 * @return 0 on success, < 0 on error.
 */
int scePowerUnlock(int unknown);

/**
 * Generate a power tick, preventing unit from 
 * powering off and turning off display.
 *
 * @param type - Either PSP_POWER_TICK_ALL, PSP_POWER_TICK_SUSPEND or PSP_POWER_TICK_DISPLAY
 *
 * @return 0 on success, < 0 on error.
 */
int scePowerTick(int type);

/**
 * Get Idle timer
 *
 */
int scePowerGetIdleTimer(void);

/**
 * Enable Idle timer
 *
 * @param unknown - pass 0
 */
int scePowerIdleTimerEnable(int unknown);

/**
 * Disable Idle timer
 *
 * @param unknown - pass 0
 */
int scePowerIdleTimerDisable(int unknown);

/**
 * Request the PSP to go into standby
 *
 * @return 0 always
 */
int scePowerRequestStandby(void);

/**
 * Request the PSP to go into suspend
 *
 * @return 0 always
 */
int scePowerRequestSuspend(void);


#ifdef __cplusplus
}
#endif

#endif
