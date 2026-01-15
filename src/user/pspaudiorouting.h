/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspaudiorouting.h - Interface to sceAudioRouting.
 *
 * Copyright (c) 2007 Alexander Berl <raphael@fx-world.org>
 *
 */
#ifndef __PSPAUDIOROUTING_H__
#define __PSPAUDIOROUTING_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Set routing mode.
 *
 * @param mode The routing mode to set (0 or 1)
 *
 * @return the previous routing mode, or < 0 on error
*/
int sceAudioRoutingSetMode( int mode );

/**
 * Get routing mode.
 *
 * @return the current routing mode.
*/
int sceAudioRoutingGetMode(void);

/** Get the current routing volume mode.
 *
 * @return The current routing volume mode.
 */
int sceAudioRoutingGetVolumeMode(void);

/** Set the routing volume mode.
 *
 * @param vol_mode The routing volume to set (`0` or `1`).
 *
 * @return `0` on success, `< 0` on error.
 */
int sceAudioRoutingSetVolumeMode(int vol_mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PSPAUDIOROUTING_H__ */

