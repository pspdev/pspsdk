/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * types.h - Definition of basic cross platform types.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id: types.h 2333 2007-10-31 19:37:40Z tyranid $
 */

#ifndef __TYPES_H__
#define __TYPES_H__

#include "config.h"
#ifdef HAVE_STDINT_H
#include <stdint.h>
#else
#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#else
#include <sys/types.h>
#define uint8_t u_int8_t
#define uint16_t u_int16_t
#define uint32_t u_int32_t
#define uint64_t u_int64_t
#endif
#endif

/* Re-define some system types */
typedef uint8_t 	u8;
typedef uint16_t 	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;
typedef int8_t		s8;
typedef int16_t		s16;
typedef int32_t		s32;
typedef int64_t		s64;

#ifdef WORDS_BIGENDIAN
inline u32 lw_le(u32 data)
{
	u8 *ptr;
	u32 val;

	ptr = (u8*) &data;

	val = ptr[0] | (ptr[1] << 8) | (ptr[2] << 16) | (ptr[3] << 24);

	return val;
}

inline u16 lh_le(u16 data)
{
	u8 *ptr;
	u16 val;

	ptr = (u8*) &data;

	val = ptr[0] | (ptr[1] << 8);

	return val;
}

#define LW_LE(x) (lw_le((x)))
#define LW_BE(x) (x)
#define LH_LE(x) (lh_le((x)))
#define LH_BE(x) (x)

#else

inline u32 lw_be(u32 data)
{
	u8 *ptr;
	u32 val;

	ptr = (u8*) &data;

	val = (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];

	return val;
}

inline u16 lh_be(u16 data)
{
	u8 *ptr;
	u16 val;

	ptr = (u8*) &data;

	val = (ptr[0] << 16) | ptr[1];

	return val;
}

#define LW_LE(x) (x)
#define LW_BE(x) (lw_be((x)))
#define LH_LE(x) (x)
#define LH_BE(x) (lh_be((x)))

#endif

#define LW(x) (LW_LE(x))
#define LH(x) (LH_LE(x))


#ifdef WORDS_BIGENDIAN
inline void sw_le(u32 *data, u32 val)
{
	u8* ptr = (u8*) data;

	ptr[0] = (u8) (val & 0xFF);
	ptr[1] = (u8) ((val >> 8) & 0xFF);
	ptr[2] = (u8) ((val >> 16) & 0xFF);
	ptr[3] = (u8) ((val >> 24) & 0xFF);
}

inline void sh_le(u16 *data, u16 val)
{
	u8 *ptr = (u8*) data;

	ptr[0] = (u8) (val & 0xFF);
	ptr[1] = (u8) ((val >> 8) & 0xFF);
}

#define SW_LE(x, v) (sw_le((x), (v)))
#define SW_BE(x, v) (*(x) = (v))
#define SH_LE(x, v) (sh_le((x), (v)))
#define SH_BE(x, v) (*(x) = (v))

#else

inline void sw_be(u32 *data, u32 val)
{
	u8 *ptr = (u8*) data;

	ptr[0] = (u8) ((val >> 24) & 0xFF);
	ptr[1] = (u8) ((val >> 16) & 0xFF);
	ptr[2] = (u8) ((val >> 8) & 0xFF);
	ptr[3] = (u8) (val & 0xFF);
}

inline void sh_be(u16 *data, u16 val)
{
	u8* ptr = (u8*) data;

	ptr[0] = (u8) ((val >> 8) & 0xFF);
	ptr[1] = (u8) (val & 0xFF);
}

#define SW_LE(x, v) (*(x) = (v))
#define SW_BE(x, v) (sw_be((x), (v)))
#define SH_LE(x, v) (*(x) = (v))
#define SH_BE(x, v) (sh_be((x), (v)))

#endif

#define SW(x, v) (SW_LE(x, v))
#define SH(x, v) (SH_LE(x, v))

#endif
