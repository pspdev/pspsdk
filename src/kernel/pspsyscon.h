/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsyscon.h - Interface to sceSyscon_driver.
 *
 * Copyright (c) 2006 James F
 *
 * $Id: pspsyscon.h 2413 2008-07-23 22:04:04Z raphael $
 */

#ifndef PSPSYSCON_H
#define PSPSYSCON_H

#include <pspkerneltypes.h>

/** @defgroup Syscon Interface to the sceSyscon_driver library.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Syscon Interface to the sceSyscon_driver library. */
/*@{*/

/**
  * Force the PSP to go into standby
  */
void sceSysconPowerStandby(void);

/**
 * Reset the PSP
 *
 * @param unk1 - Unknown, pass 1
 * @param unk2 - Unknown, pass 1
 */
void sceSysconResetDevice(int unk1, int unk2);

#define SCE_LED_POWER 1
#define LED_ON 1
#define LED_OFF 0
/**
 * Control an LED
 *
 * @param SceLED - The led to toggle (only SCE_LED_POWER)
 * @param state - Whether to turn on or off
 */
int sceSysconCtrlLED(int SceLED, int state);

/**
 * Control the remote control power
 *
 * @param power - 1 is on, 0 is off
 * 
 * @return < 0 on error
 */
int sceSysconCtrlHRPower(int power);


int	sceSysconGetHPConnect(void);

int sceSysconSetHPConnectCallback( void (*)(int), int unk0 );

int sceSysconSetHRPowerCallback( void (*)(int), int unk0 );

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
