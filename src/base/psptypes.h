/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psptypes.h - Commonly used typedefs.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id: psptypes.h 2312 2007-09-09 15:02:23Z chip $
 */

/* Note: Some of the structures, types, and definitions in this file were
   extrapolated from symbolic debugging information found in the Japanese
   version of Puzzle Bobble. */

#ifndef _PSPTYPES_H_
#define _PSPTYPES_H_ 1

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL	0
#else
#define NULL	((void *) 0)
#endif /* __cplusplus */
#endif

/* Legacy ps2dev types. */
#ifndef PSP_LEGACY_TYPES_DEFINED
#define PSP_LEGACY_TYPES_DEFINED
typedef	uint8_t				u8;
typedef uint16_t			u16;

typedef uint32_t			u32;
typedef uint64_t			u64;

typedef int8_t				s8;
typedef int16_t				s16;

typedef int32_t				s32;
typedef int64_t				s64;
#endif

#ifndef PSP_LEGACY_VOLATILE_TYPES_DEFINED
#define PSP_LEGACY_VOLATILE_TYPES_DEFINED
typedef	volatile uint8_t		vu8;
typedef volatile uint16_t		vu16;

typedef volatile uint32_t		vu32;
typedef volatile uint64_t		vu64;

typedef volatile int8_t			vs8;
typedef volatile int16_t		vs16;

typedef volatile int32_t		vs32;
typedef volatile int64_t		vs64;
#endif

/* MIPS-like accessor macros. */
static __inline__ u8  _lb(u32 addr) { return *(vu8 *)addr; }
static __inline__ u16 _lh(u32 addr) { return *(vu16 *)addr; }
static __inline__ u32 _lw(u32 addr) { return *(vu32 *)addr; }
static __inline__ u64 _ld(u32 addr) { return *(vu64 *)addr; }

static __inline__ void _sb(u8 val, u32 addr) { *(vu8 *)addr = val; }
static __inline__ void _sh(u16 val, u32 addr) { *(vu16 *)addr = val; }
static __inline__ void _sw(u32 val, u32 addr) { *(vu32 *)addr = val; }
static __inline__ void _sd(u64 val, u32 addr) { *(vu64 *)addr = val; }

/* SCE types. */
typedef unsigned char SceUChar8;
typedef uint16_t SceUShort16;
typedef uint32_t SceUInt32;
typedef uint64_t SceUInt64;
typedef uint64_t SceULong64;
/*typedef unsigned int SceULong128 __attribute__((mode(TI)));*/

typedef char SceChar8;
typedef int16_t SceShort16;
typedef int32_t SceInt32;
typedef int64_t SceInt64;
typedef int64_t SceLong64;
/*typedef int SceLong128 __attribute__((mode(TI)));*/

typedef float SceFloat;
typedef float SceFloat32;

typedef short unsigned int SceWChar16;
typedef unsigned int SceWChar32;

typedef int SceBool;

typedef void SceVoid;
typedef void * ScePVoid;


/* PSP types. */

/* Rectangles. */
typedef struct ScePspSRect {
	short int 	x;
	short int 	y;
	short int 	w;
	short int 	h;
} ScePspSRect;

typedef struct ScePspIRect {
	int 	x;
	int 	y;
	int 	w;
	int 	h;
} ScePspIRect;

typedef struct ScePspL64Rect {
	SceLong64 	x;
	SceLong64 	y;
	SceLong64 	w;
	SceLong64 	h;
} ScePspL64Rect;

typedef struct ScePspFRect {
	float 	x;
	float 	y;
	float 	w;
	float 	h;
} ScePspFRect;

/* 2D vectors. */
typedef struct ScePspSVector2 {
	short int 	x;
	short int 	y;
} ScePspSVector2;

typedef struct ScePspIVector2 {
	int 	x;
	int 	y;
} ScePspIVector2;

typedef struct ScePspL64Vector2 {
	SceLong64 	x;
	SceLong64 	y;
} ScePspL64Vector2;

typedef struct ScePspFVector2 {
	float 	x;
	float 	y;
} ScePspFVector2;

typedef union ScePspVector2 {
	ScePspFVector2 	fv;
	ScePspIVector2 	iv;
	float 			f[2];
	int 			i[2];
} ScePspVector2;

/* 3D vectors. */
typedef struct ScePspSVector3 {
	short int 	x;
	short int 	y;
	short int 	z;
} ScePspSVector3;

typedef struct ScePspIVector3 {
	int 	x;
	int 	y;
	int 	z;
} ScePspIVector3;

typedef struct ScePspL64Vector3 {
	SceLong64 	x;
	SceLong64 	y;
	SceLong64 	z;
} ScePspL64Vector3;

typedef struct ScePspFVector3 {
	float 	x;
	float 	y;
	float 	z;
} ScePspFVector3;

typedef union ScePspVector3 {
	ScePspFVector3 	fv;
	ScePspIVector3 	iv;
	float 			f[3];
	int 			i[3];
} ScePspVector3;

/* 4D vectors. */
typedef struct ScePspSVector4 {
	short int 	x;
	short int 	y;
	short int 	z;
	short int 	w;
} ScePspSVector4;

typedef struct ScePspIVector4 {
	int 	x;
	int 	y;
	int 	z;
	int 	w;
} ScePspIVector4;

typedef struct ScePspL64Vector4 {
	SceLong64 	x;
	SceLong64 	y;
	SceLong64 	z;
	SceLong64 	w;
} ScePspL64Vector4;

typedef struct ScePspFVector4 {
	float 	x;
	float 	y;
	float 	z;
	float 	w;
} ScePspFVector4 __attribute__((aligned(16)));

typedef struct ScePspFVector4Unaligned {
	float 	x;
	float 	y;
	float 	z;
	float 	w;
} ScePspFVector4Unaligned;

typedef union ScePspVector4 {
	ScePspFVector4 	fv;
	ScePspIVector4 	iv;
/*	SceULong128 	qw;*/	/* Missing compiler support. */
	float 			f[4];
	int 			i[4];
} ScePspVector4 __attribute__((aligned(16)));

/* 2D matrix types. */
typedef struct ScePspIMatrix2 {
	ScePspIVector2 	x;
	ScePspIVector2 	y;
} ScePspIMatrix2;

typedef struct ScePspFMatrix2 {
	ScePspFVector2 	x;
	ScePspFVector2 	y;
} ScePspFMatrix2;

typedef union ScePspMatrix2 {
	ScePspFMatrix2 	fm;
	ScePspIMatrix2 	im;
	ScePspFVector2 	fv[2];
	ScePspIVector2 	iv[2];
	ScePspVector2 	v[2];
/*	SceULong128 	qw[2];*/	/* Missing compiler support. */
	float 			f[2][2];
	int 			i[2][2];
} ScePspMatrix2;

/* 3D matrix types. */
typedef struct ScePspIMatrix3 {
	ScePspIVector3 	x;
	ScePspIVector3 	y;
	ScePspIVector3 	z;
} ScePspIMatrix3;

typedef struct ScePspFMatrix3 {
	ScePspFVector3 	x;
	ScePspFVector3 	y;
	ScePspFVector3 	z;
} ScePspFMatrix3;

typedef union ScePspMatrix3 {
	ScePspFMatrix3 	fm;
	ScePspIMatrix3 	im;
	ScePspFVector3 	fv[3];
	ScePspIVector3 	iv[3];
	ScePspVector3 	v[3];
/*	SceULong128 	qw[3];*/	/* Missing compiler support. */
	float 			f[3][3];
	int 			i[3][3];
} ScePspMatrix3;

/* 4D matrix types. */
typedef struct ScePspIMatrix4 {
	ScePspIVector4 	x;
	ScePspIVector4 	y;
	ScePspIVector4 	z;
	ScePspIVector4 	w;
} ScePspIMatrix4 __attribute__((aligned(16)));

typedef struct ScePspIMatrix4Unaligned {
	ScePspIVector4 	x;
	ScePspIVector4 	y;
	ScePspIVector4 	z;
	ScePspIVector4 	w;
} ScePspIMatrix4Unaligned;

typedef struct ScePspFMatrix4 {
	ScePspFVector4 	x;
	ScePspFVector4 	y;
	ScePspFVector4 	z;
	ScePspFVector4 	w;
} ScePspFMatrix4 __attribute__((aligned(16)));

typedef struct ScePspFMatrix4Unaligned {
	ScePspFVector4 	x;
	ScePspFVector4 	y;
	ScePspFVector4 	z;
	ScePspFVector4 	w;
} ScePspFMatrix4Unaligned;

typedef union ScePspMatrix4 {
	ScePspFMatrix4 	fm;
	ScePspIMatrix4 	im;
	ScePspFVector4 	fv[4];
	ScePspIVector4 	iv[4];
	ScePspVector4 	v[4];
/*	SceULong128 	qw[4];*/	/* Missing compiler support. */
	float 			f[4][4];
	int 			i[4][4];
} ScePspMatrix4;

/* Quaternions. */
typedef struct ScePspFQuaternion {
	float 	x;
	float 	y;
	float 	z;
	float 	w;
} ScePspFQuaternion __attribute__((aligned(16)));

typedef struct ScePspFQuaternionUnaligned {
	float 	x;
	float 	y;
	float 	z;
	float 	w;
} ScePspFQuaternionUnaligned;

/* Colors and pixel formats. */
typedef struct ScePspFColor {
	float 	r;
	float 	g;
	float 	b;
	float 	a;
} ScePspFColor __attribute__((aligned(16)));

typedef struct ScePspFColorUnaligned {
	float 	r;
	float 	g;
	float 	b;
	float 	a;
} ScePspFColorUnaligned;

typedef unsigned int ScePspRGBA8888;
typedef unsigned short ScePspRGBA4444;
typedef unsigned short ScePspRGBA5551;
typedef unsigned short ScePspRGB565;

/* Unions for converting between types. */
typedef union ScePspUnion32 {
	unsigned int 	ui;
	int 			i;
	unsigned short 	us[2];
	short int 		s[2];
	unsigned char 	uc[4];
	char 			c[4];
	float 			f;
	ScePspRGBA8888 	rgba8888;
	ScePspRGBA4444 	rgba4444[2];
	ScePspRGBA5551 	rgba5551[2];
	ScePspRGB565 	rgb565[2];
} ScePspUnion32;

typedef union ScePspUnion64 {
	SceULong64 		ul;
	SceLong64 		l;
	unsigned int 	ui[2];
	int 			i[2];
	unsigned short 	us[4];
	short int 		s[4];
	unsigned char 	uc[8];
	char 			c[8];
	float 			f[2];
	ScePspSRect 	sr;
	ScePspSVector4 	sv;
	ScePspRGBA8888 	rgba8888[2];
	ScePspRGBA4444 	rgba4444[4];
	ScePspRGBA5551 	rgba5551[4];
	ScePspRGB565 	rgb565[4];
} ScePspUnion64;

typedef union ScePspUnion128 {
/*	SceULong128 	qw;*/	/* Missing compiler support. */
/*	SceULong128 	uq;*/
/*	SceLong128 	q;*/
	SceULong64		ul[2];
	SceLong64		l[2];
	unsigned int 	ui[4];
	int 			i[4];
	unsigned short 	us[8];
	short int 		s[8];
	unsigned char 	uc[16];
	char 			c[16];
	float 			f[4];
	ScePspFRect 	fr;
	ScePspIRect 	ir;
	ScePspFVector4 	fv;
	ScePspIVector4 	iv;
	ScePspFQuaternion fq;
	ScePspFColor 	fc;
	ScePspRGBA8888 	rgba8888[4];
	ScePspRGBA4444 	rgba4444[8];
	ScePspRGBA5551 	rgba5551[8];
	ScePspRGB565 	rgb565[8];
} ScePspUnion128 __attribute__((aligned(16)));

/* Date and time. */
typedef struct ScePspDateTime {
	unsigned short	year;
	unsigned short 	month;
	unsigned short 	day;
	unsigned short 	hour;
	unsigned short 	minute;
	unsigned short 	second;
	unsigned int 	microsecond;
} ScePspDateTime;

#ifdef __cplusplus
}
#endif

#endif /* _PSPTYPES_H_ */
