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
int sceAudioRoutingGetMode();

#endif

