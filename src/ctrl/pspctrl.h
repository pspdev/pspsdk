/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspctrl.h - Prototypes for the sceCtrl library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

/* Note: Some of the structures, types, and definitions in this file were
   extrapolated from symbolic debugging information found in the Japanese
   version of Puzzle Bobble. */

#ifndef __CTRL_H__
#define __CTRL_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Ctrl Controller Kernel Library */
/**@{*/

/**
 * Enumeration for the digital controller buttons.
 *
 * @note PSP_CTRL_HOME, PSP_CTRL_NOTE, PSP_CTRL_SCREEN, PSP_CTRL_VOLUP, PSP_CTRL_VOLDOWN, PSP_CTRL_DISC, PSP_CTRL_WLAN_UP, PSP_CTRL_REMOTE, PSP_CTRL_MS can only be read in kernel mode
 */
enum PspCtrlButtons
{
	/** Select button. */
	PSP_CTRL_SELECT     = 0x000001,
	/** Start button. */
	PSP_CTRL_START      = 0x000008,
	/** Up D-Pad button. */
	PSP_CTRL_UP         = 0x000010,
	/** Right D-Pad button. */
	PSP_CTRL_RIGHT      = 0x000020,
	/** Down D-Pad button. */
	PSP_CTRL_DOWN      	= 0x000040,
	/** Left D-Pad button. */
	PSP_CTRL_LEFT      	= 0x000080,
	/** Left trigger. */
	PSP_CTRL_LTRIGGER   = 0x000100,
	/** Right trigger. */
	PSP_CTRL_RTRIGGER   = 0x000200,
	/** Triangle button. */
	PSP_CTRL_TRIANGLE   = 0x001000,
	/** Circle button. */
	PSP_CTRL_CIRCLE     = 0x002000,
	/** Cross button. */
	PSP_CTRL_CROSS      = 0x004000,
	/** Square button. */
	PSP_CTRL_SQUARE     = 0x008000,
	/** Home button. In user mode this bit is set if the exit dialog is visible. */
	PSP_CTRL_HOME       = 0x010000,
	/** Hold button. */
	PSP_CTRL_HOLD       = 0x020000,
	/** Music Note button. */
	PSP_CTRL_NOTE       = 0x800000,
	/** Screen button. */
	PSP_CTRL_SCREEN     = 0x400000,
	/** Volume up button. */
	PSP_CTRL_VOLUP      = 0x100000,
	/** Volume down button. */
	PSP_CTRL_VOLDOWN    = 0x200000,
	/** Wlan switch up. */
	PSP_CTRL_WLAN_UP    = 0x040000,
	/** Remote hold position. */
	PSP_CTRL_REMOTE     = 0x080000,	
	/** Disc present. */
	PSP_CTRL_DISC       = 0x1000000,
	/** Memory stick present. */
	PSP_CTRL_MS         = 0x2000000,
};

/** Controller mode. */
enum PspCtrlMode
{
	/* Digitial. */
	PSP_CTRL_MODE_DIGITAL = 0,
	/* Analog. */
	PSP_CTRL_MODE_ANALOG
};

/** Returned controller data */
typedef struct SceCtrlData {
	/** The current read frame. */
	unsigned int 	TimeStamp;
	/** Bit mask containing zero or more of ::PspCtrlButtons. */
	unsigned int 	Buttons;
	/** Analogue stick, X axis. */
	unsigned char 	Lx;
	/** Analogue stick, Y axis. */
	unsigned char 	Ly;
	/** Reserved. */
	unsigned char 	Rsrv[6];
} SceCtrlData;

/** 
 * This structure represents controller button latch data.
 * 
 * With each sampling cycle, the controller service compares the new pressed & released button states
 * with the previously collected pressed button states. This comparison will result in the following possible
 * states for each button:
 *
 *    • [make]: The button has just been pressed with its prior state being the released state. Transition from
 *      'released' state to 'pressed' state.
 *    • [press]: The button is currently in the 'pressed' state.
 *    • [break]: The button has just been released with its prior state being the 'pressed' state. Transition from
 *      'pressed' state to 'release' state.
 *    • [release]: The button is currently in the 'released' state.
 * 
 * It is possible for a button to (briefly) be in two states at the same time. Valid combinations are as follows:
 * 
 *    • [make] & [press] 
 *    • [break] & [release]   
 * 
 * In other words, if a button is in the [make] state, then it is also in the [press] state. However, this is not the case
 * for the inverse. A button in the [press] state does not need to be in the [make] state.
 * 
 * These comparison results are stored internally as latch data and can be retrieved using the APIs ::sceCtrlPeekLatch() and 
 * ::sceCtrlReadLatch(). ::SceCtrlPadButtons can be used to find out the state of each button.
 * 
 * @remark The same can be accomplished by using the different sceCtrl[Read/Peek]Buffer[Positive/Negative]() APIs
 * and comparing the currently collected button sampling data with the previously collected one.
 * 
 * @see ::sceCtrlPeekLatch()
 * @see ::sceCtrlReadLatch()
 */
typedef struct SceCtrlLatch {
	/** Button transitioned to pressed state. */
	unsigned int 	uiMake;
	/** Button transitioned to released state. */
	unsigned int 	uiBreak;
	/** Button is in the pressed state. */
	unsigned int 	uiPress;
	/** Button is in the released state. */
	unsigned int 	uiRelease;
} SceCtrlLatch;

/**
 * Set the controller cycle setting.
 *
 * @param cycle - Cycle.  Normally set to 0.
 *
 * @return The previous cycle setting.
 */
int sceCtrlSetSamplingCycle(int cycle);

/**
 * Get the controller current cycle setting.
 *
 * @param pcycle - Return value.
 *
 * @return 0.
 */
int sceCtrlGetSamplingCycle(int *pcycle);

/**
 * Set the controller mode.
 *
 * @param mode - One of ::PspCtrlMode.
 *
 * @return The previous mode.
 */
int sceCtrlSetSamplingMode(int mode);

/**
 * Get the current controller mode.
 *
 * @param pmode - Return value.
 *
 * @return 0.
 */
int sceCtrlGetSamplingMode(int *pmode);

int sceCtrlPeekBufferPositive(SceCtrlData *pad_data, int count);

int sceCtrlPeekBufferNegative(SceCtrlData *pad_data, int count);

/**
 * Read buffer positive
 *
 * @par Example:
 * @code
 * SceCtrlData pad;

 * sceCtrlSetSamplingCycle(0);
 * sceCtrlSetSamplingMode(1);
 * sceCtrlReadBufferPositive(&pad, 1);
 * // Do something with the read controller data
 * @endcode
 *
 * @param pad_data - Pointer to a ::SceCtrlData structure used hold the returned pad data.
 * @param count - Number of ::SceCtrlData buffers to read.
 */
int sceCtrlReadBufferPositive(SceCtrlData *pad_data, int count);

int sceCtrlReadBufferNegative(SceCtrlData *pad_data, int count);

/**
 * @brief Get the latch data.
 *
 * This function reads the latch data collected by the controller service. At each sampling
 * interval, the controller service compares the new pressed/released button states with the previously sampled pressed
 * button states and stores that comparison as latch data.
 *
 * Compared to ::sceCtrlReadLatch(), calling this API will not result in clearing the internal latch data. As such,
 * the data returned is the accumulated latch data since the last time ::sceCtrlReadLatch() was called. Consequently,
 * the returned data should not be relied on whether a button is currently in a pressed or released state.
 *
 * @param latch_data Pointer to a ::SceCtrlLatch variable which is to receive the accumulated button latch data.
 *
 * @return On success, the number of times the controller service performed sampling since the last time
 * ::sceCtrlReadLatch() was called.
 * @return < 0 on error.
 * 
 * @see ::SceCtrlLatch
 * @see ::sceCtrlReadLatch()
 */
int sceCtrlPeekLatch(SceCtrlLatch *latch_data);

/**
 * @brief Get the latch data. 
 * 
 * This function reads the most recent latch data collected by the controller service. At each sampling
 * interval, the controller service compares the new pressed/released button states with the previously sampled pressed
 * button states and stores that comparison as latch data.
 * 
 * Compared to ::sceCtrlPeekLatch(), calling this API will result in clearing the internal latch data. As such,
 * calling code might have to explicitly wait for the controller service to update its collected latch data.
 * 
 * @param latch_data Pointer to a ::SceCtrlLatch variable which is to receive the current button latch data.
 * 
 * @return On success, the number of times the controller service performed sampling since the last time
 * ::sceCtrlReadLatch() was called.
 * @return < 0 on error.
 * 
 * @par Example:
 * @code
 * SceCtrlLatch latchData;
 * 
 * while (1) {
 *     // Obtain latch data
 *     sceCtrlReadLatch(&latchData);
 * 
 *     if (latchData.buttonMake & PSP_CTRL_CROSS)
 *     {
 *         // The Cross button has just been pressed (transition from 'released' state to 'pressed' state)
 *     }
 * 
 *     if (latchData.buttonPress & PSP_CTRL_SQUARE)
 *     {
 *         // The Square button is currently in the 'pressed' state
 *     }
 * 
 *    if (latchData.buttonBreak & PSP_CTRL_TRIANGLE)
 *    {
 *        // The Triangle button has just been released (transition from 'pressed' state to 'released' state)
 *    }
 * 
 *    if (latchData.buttonRelease & PSP_CTRL_CIRCLE)
 *    {
 *        // The Circle button is currently in the 'released' state
 *    }
 * 
 *    // As we clear the internal latch data with the ReadLatch() call, we can explicitly wait for the VBLANK interval
 *    // to give the controller service the time it needs to collect new latch data again. This guarantees the next call
 *    // to sceCtrlReadLatch() will return collected data again.
 *    //
 *    // Note: The sceCtrlReadBuffer*() APIs are implicitly waiting for a VBLANK interval if necessary.
 *    sceDisplayWaitVBlank();
 * }
 * @endcode
 * 
 * @see ::SceCtrlLatch
 * @see ::sceCtrlPeekLatch()
 */
int sceCtrlReadLatch(SceCtrlLatch *latch_data);

/**
 * Set analog threshold relating to the idle timer.
 *
 * @param idlereset - Movement needed by the analog to reset the idle timer.
 * @param idleback - Movement needed by the analog to bring the PSP back from an idle state.
 *
 * Set to -1 for analog to not cancel idle timer.
 * Set to 0 for idle timer to be cancelled even if the analog is not moved.
 * Set between 1 - 128 to specify the movement on either axis needed by the analog to fire the event.
 *
 * @return < 0 on error.
 */
int sceCtrlSetIdleCancelThreshold(int idlereset, int idleback);

/**
 * Get the idle threshold values.
 *
 * @param idlerest - Movement needed by the analog to reset the idle timer.
 * @param idleback - Movement needed by the analog to bring the PSP back from an idle state.
 *
 * @return < 0 on error.
 */
int sceCtrlGetIdleCancelThreshold(int *idlerest, int *idleback);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif
