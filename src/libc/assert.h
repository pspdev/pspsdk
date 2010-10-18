/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * assert.h
 *
 * Copyright (c) 2002-2004 PS2DEV
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: assert.h 1095 2005-09-27 21:02:16Z jim $
 */
#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <pspkernel.h>
#include <stdio.h>

#ifdef NDEBUG
#define assert(cond)
#else
#ifdef __cplusplus
extern "C" {
#endif
    int __assert_fail (const char *assertion, const char *file, unsigned int line) __attribute__((noreturn));
#ifdef __cplusplus
}
#endif
#define assert(cond) (void)((cond)?0:__assert_fail(#cond, __FILE__, __LINE__))
#endif

#endif
