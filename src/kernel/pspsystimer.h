/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsystimer.h - Prototypes for the sceSystimer library.
 *
 * Copyright (c) 2007 Iaroslav Gaponenko <adrahil@gmail.com>
 *
 * $Id: pspsystimer.h 2149 2007-01-25 20:46:21Z tyranid $
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

/* Unknown functions. */
//probably something to set the cycle of an active timer.
void SysTimerForKernel_53231A15(SceSysTimerId timer, int unk1);
//more complex. computes some ratio (unk2/unk1) and saves both parameters into the hardware registers. Might be some sort of scaling factor?
void SysTimerForKernel_B53534B4(SceSysTimerId timer, int unk1, int unk2);



#ifdef __cplusplus
}
#endif

#endif
