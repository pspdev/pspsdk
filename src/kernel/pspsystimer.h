/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsystimer.h - Prototypes for the sceSystimer library.
 *
 * Copyright (c) 2007 Iaroslav Gaponenko <adrahil@gmail.com>
 *
 */

#ifndef __SYSTIMER_H__
#define __SYSTIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef int SceSysTimerId;

/**
 * Allocate a new SysTimer timer instance.
 *
 * @return SysTimerId on success, < 0 on error
 */
SceSysTimerId sceSTimerAlloc(void);

/**
 * Free an instance of a SysTimer timer.
 *
 * @param timer - The timer id.
 *
 */
void sceSTimerFree(SceSysTimerId timer);

/**
 * Start the SysTimer timer count.
 *
 * @param timer - The timer id.
 *
 */
void sceSTimerStartCount(SceSysTimerId timer);

/**
 * Stop the current SysTimer timer count.
 *
 * @param timer - The timer id.
 *
 */
void sceSTimerStopCount(SceSysTimerId timer);

/**
 * Reset the current SysTimer timer count.
 *
 * @param timer - The timer id.
 *
 */
void sceSTimerResetCount(SceSysTimerId timer);

/**
 * Get the current SysTimer timer count.
 *
 * @param timer - The timer id.
 * @param count - The pointer to an integer into which the count will be written.
 *
 */
void sceSTimerGetCount(SceSysTimerId timer, int* count);

/**
 * Setup a SysTimer handler
 *
 * @param timer - The timer id.
 * @param cycle - The timer cycle in microseconds (???). Maximum: 4194303 which represents ~1/10 seconds.
 * @param handler - The handler function. Has to return -1.
 * @param unk1 - Unknown. Pass 0.
 *
 */
void sceSTimerSetHandler(SceSysTimerId timer, int cycle, int (*handler)(void), int unk1);

/**
 * Unknown purpose.
 *
 * Probably something to set the cycle of an active timer.
 *
 * @param timer The ID of the timer.
 * @param unk1 Unknown. Should not be less than `0` and greater `4194304`.
 *
 * @return `0` on success.
 */
//probably something to set the cycle of an active timer.
void sceSTimerSetTMCY(SceSysTimerId timer, int unk1);

/**
 * Set the prescale of a hardware timer. It can be only set on timers which are in the "not in use" state.
 *
 * The input signal is divided into the resulting ratio. The ratio has to be less than 1/11.
 *
 * @param timer The ID of the timer to set the prescale.
 * @param numerator The numerator of the prescale. Must not be `0`.
 * @param denominator The denominator of the prescale. Must not be `0`.
 *
 * @return `0` on success.
 */
void sceSTimerSetPrscl(SceSysTimerId timer, int unk1, int unk2);



#ifdef __cplusplus
}
#endif

#endif
