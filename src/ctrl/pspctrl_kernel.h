/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspctrl_kernel.h - Prototypes for the sceCtrl_driver library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

#ifndef __CTRL_KERNEL_H__
#define __CTRL_KERNEL_H__

#include <psptypes.h>

/** The callback function used by ::sceCtrlSetSpecialButtonCallback(). */
typedef void (*SceKernelButtonCallbackFunction)(u32 cur_buttons, u32 last_buttons, void *opt);

/** Button mask settings. */
typedef enum SceCtrlButtonMaskMode {
    /** No mask for the specified buttons. Button input is normally recognized. */
    SCE_CTRL_MASK_NO_MASK = 0,
    /**
     * The specified buttons are ignored, that means even if these buttons are pressed by the user
     * they won't be shown as pressed internally.
	 *
	 * You can only block user buttons for applications running in User Mode.
     */
    SCE_CTRL_MASK_IGNORE_BUTTONS = 1,
    /**
     * The specified buttons show up as being pressed, even if the user does not press them.
     *
	 * You can only turn ON user buttons for applications running in User Mode.
     */
    SCE_CTRL_MASK_APPLY_BUTTONS = 2,
} SceCtrlButtonMaskMode;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Sets a button mask mode for one or more buttons.
 *
 * You can only mask user mode buttons in user applications. Masking of kernel
 * mode buttons is ignored as well as buttons used in kernel mode applications.
 *
 * @param buttons The button value for which the button mask mode will be applied for. One or more buttons of `SceCtrlButtons`.
 * @param mask_mode Specifies the type of the button mask. One of `SceCtrlButtonMaskMode`.
 *
 * @return The previous button mask type for the given buttons. One of `SceCtrlButtonMaskMode`.
 *
 * @example Example:
 * @code
 * sceCtrlSetButtonIntercept(0xFFFF, 1);  // Mask lower 16bits
 * sceCtrlSetButtonIntercept(0x10000, 2); // Always return HOME key
 * // Do something
 * sceCtrlSetButtonIntercept(0x10000, 0); // Unset HOME key
 * sceCtrlSetButtonIntercept(0xFFFF, 0);  // Unset mask
 * @endcode
 */
u32 sceCtrlSetButtonIntercept(u32 buttons, u32 mask_mode);

/**
 * Get button mask mode.
 *
 * @param buttons The buttons to check for. One or more buttons of `SceCtrlButtons`.
 *
 * @return The button mask mode for the given buttons. One of `SceCtrlButtonMaskMode`.
 */
u32 sceCtrlGetButtonIntercept(u32 buttons);

/**
 * Registers a button callback.
 *
 * @param slot The slot used to register the callback. Between 0 - 3.
 * @param button_mask Bitwise OR'ed button values which will be checked for being pressed. One or more buttons of `SceCtrlButtons`.
 * @param callback A pointer to the callback function handling the button callbacks.
 * @param opt Optional user argument. Passed to the callback function as its third argument.
 *
 * @return 0 on success, < 0 on error.
 */
int sceCtrlSetSpecialButtonCallback(u32 slot, u32 button_mask, SceKernelButtonCallbackFunction callback, void *opt);

/* Just define some random names for the functions to make them easier to use */
#define sceCtrlSetButtonMasks sceCtrlSetButtonIntercept
#define sceCtrlGetButtonMask sceCtrlGetButtonIntercept
#define sceCtrlRegisterButtonCallback sceCtrlSetSpecialButtonCallback


#ifdef __cplusplus
}
#endif

#endif
