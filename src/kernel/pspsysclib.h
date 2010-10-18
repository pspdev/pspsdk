/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsysclib.h - Interface to sysclib library.
 *
 * Copyright (c) 2007 James F
 *
 * $Id$
 */

#ifndef PSPSYSCLIB_H
#define PSPSYSCLIB_H

#include <pspkerneltypes.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Callback type, ch is 0x200 on start of string, 0x201 on end */
typedef void (*prnt_callback)(void *ctx, int ch);

/** 
 * Generic print routine
 *
 * @param cb - Callback, called for every character printed
 * @param ctx - Context parameter passed to the callback
 * @param fmt - Format data
 * @param args - Arguments for format
 *
 */
void prnt(prnt_callback cb, void *ctx, const char *fmt, va_list args);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
