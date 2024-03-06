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
 * @brief Enumeration representing digital controller button flags.
 *
 * Each flag corresponds to a different button and can be used to extract button states from ::SceCtrlData and ::SceCtrlLatch structures.
 * Flags can be combined using bitwise OR operation to check for mutliple key states at once.
 *
 * @note Some button states are available only in kernel mode.
 *
 * @see ::SceCtrlData
 * @see ::SceCtrlLatch
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
	/**
	 * Kernel mode: Home button state.
	 * User mode: Exit dialog visible.
	 */
	PSP_CTRL_HOME       = 0x010000,
	/** Hold button. */
	PSP_CTRL_HOLD       = 0x020000,
	/** Music note button - kernel mode only.*/
	PSP_CTRL_NOTE       = 0x800000,
	/** Screen button - kernel mode only.*/
	PSP_CTRL_SCREEN     = 0x400000,
	/** Volume up button - kernel mode only.*/
	PSP_CTRL_VOLUP      = 0x100000,
	/** Volume down button - kernel mode only.*/
	PSP_CTRL_VOLDOWN    = 0x200000,
	/** Wlan switch up - kernel mode only.*/
	PSP_CTRL_WLAN_UP    = 0x040000,
	/** Remote hold position - kernel mode only.*/
	PSP_CTRL_REMOTE     = 0x080000,
	/** Disc present - kernel mode only.*/
	PSP_CTRL_DISC       = 0x1000000,
	/** Memory stick present - kernel mode only.*/
	PSP_CTRL_MS         = 0x2000000,
};

/**
 * @brief Controller mode.
 *
 * Specifies if analog data should be included in ::SceCtrlData.
 *
 * @see ::sceCtrlSetSamplingMode()
 * @see ::sceCtrlGetSamplingMode()
 * @see ::SceCtrlData
 */
enum PspCtrlMode
{
	/* Digital. */
	PSP_CTRL_MODE_DIGITAL = 0,
	/* Analog. */
	PSP_CTRL_MODE_ANALOG = 1,
};

/**
 * @brief Controller data.
 *
 * Contains current button and axis state.
 *
 * @note Axis state is present only in ::PSP_CTRL_MODE_ANALOG controller mode.
 *
 * @see ::sceCtrlPeekBufferPositive()
 * @see ::sceCtrlPeekBufferNegative()
 * @see ::sceCtrlReadBufferPositive()
 * @see ::sceCtrlReadBufferNegative()
 * @see ::PspCtrlMode
 */
typedef struct SceCtrlData {
	/** Current read frame. */
	unsigned int 	TimeStamp;
	/**
	 * Buttons in pressed state.
	 *
	 * Mask the value with one or more ::PspCtrlButtons flags to access specific buttons.
	 */
	unsigned int 	Buttons;
	/** X-axis value of the Analog Stick.*/
	unsigned char 	Lx;
	/** Y-axis value of the Analog Stick.*/
	unsigned char 	Ly;
	/** Reserved. */
	unsigned char 	Rsrv[6];
} SceCtrlData;

/** 
 * @brief Controller latch data.
 * 
 * Contains information about button state changes between two controller service sampling cycles.
 *
 * @parblock
 * @note Mask **uiMake**, **uiBreak**, **uiPress** or **uiRelease** with one or more
 * ::PspCtrlButtonsflags to access specific buttons.
 * @endparblock
 * @parblock
 * @note If a button transitioned to pressed state between two cycles, corresponding
 * ::PspCtrlButtons flag will be present in both **uiMake** and **uiPress** bit fields.
 * Similarly, when a button is released a flag will be present in **uiBreak** and **uiRelease**.
 * @endparblock
 *
 * @see ::PspCtrlButtons
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
 * @param mode - One of ::PspCtrlMode. If this is ::PSP_CTRL_MODE_DIGITAL, no data about the analog stick
 * will be present in the SceCtrlData struct read by SceCtrlReadBuffer.
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

/**
 * @brief Read latest controller data from the controller service.
 *
 * Controller data contains current button and axis state.
 *
 * @note Axis state is present only in ::PSP_CTRL_MODE_ANALOG controller mode.
 *
 * @param pad_data - A pointer to ::SceCtrlData structure that receives controller data.
 * @param count - Number of ::SceCtrlData structures to read.
 *
 * @see ::SceCtrlData
 * @see ::sceCtrlPeekBufferNegative()
 * @see ::sceCtrlReadBufferPositive()
 */
int sceCtrlPeekBufferPositive(SceCtrlData *pad_data, int count);

int sceCtrlPeekBufferNegative(SceCtrlData *pad_data, int count);

/**
 * @brief Read new controller data from the controller service.
 *
 * Controller data contains current button and axis state.
 *
 * @note Axis state is present only in ::PSP_CTRL_MODE_ANALOG controller mode.
 *
 * @warning Controller data is collected once every controller sampling cycle.
 * If controller data was already read during a cycle, trying to read it again
 * will block the execution until the next one.
 *
 * @param pad_data - A pointer to ::SceCtrlData structure that receives controller data.
 * @param count - Number of ::SceCtrlData structures to read.
 *
 * @see ::SceCtrlData
 * @see ::sceCtrlReadBufferNegative()
 * @see ::sceCtrlPeekBufferPositive()
 */
int sceCtrlReadBufferPositive(SceCtrlData *pad_data, int count);

int sceCtrlReadBufferNegative(SceCtrlData *pad_data, int count);

/**
 * @brief Read latest latch data from the controller service.
 *
 * Latch data contains information about button state changes between two controller service sampling cycles.
 *
 * @param latch_data A pointer to ::SceCtrlLatch structure that receives latch data.
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
 * @brief Read new latch data from the controller service.
 * 
 * Latch data contains information about button state changes between two controller service sampling cycles.
 * 
 * @warning Latch data is produced once every controller sampling cycle. If latch data was already read
 * during a cycle, trying to read it again will block the execution until the next one.
 * 
 * @param latch_data A pointer to ::SceCtrlLatch structure that receives latch data.
 * 
 * @return On success, the number of times the controller service performed sampling since the last time
 * ::sceCtrlReadLatch() was called.
 * @return < 0 on error.
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
