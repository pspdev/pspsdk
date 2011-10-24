/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspfpu.h - PSP FPU library
 *
 * Copyright (c) 2009 JetCube
 * Copyright (c) 2006 TyRaNiD (James F.)
 *
 */
#include "pspfpu.h"

#define PSP_MATH_PI             3.14159265358979323846
#define PSP_MATH_TWOPI          (PSP_MATH_PI * 2.0)
#define PSP_MATH_SQRT2          1.41421356237309504880
#define PSP_MATH_LN2            0.69314718055994530942
#define PSP_MATH_LOG2E          1.4426950408889634074
#define COS_SIN_DIV             0.208

static const float logPoly[] = {
	 4194305.0 / (1024.0 * 1024.0 *  2.0), /* arround 2.0 */
	 5590817.0 / (1024.0 * 1024.0 *  8.0), /* arround 2.0/3.0 */
	13890687.0 / (1024.0 * 1024.0 * 32.0), /* arround 2.0/5.0 */
};

static const float triPoly[] = {
	(float)(2.0*PSP_MATH_PI),
	(float)(1.0),
	(float)(-0xAAAA98/(1024.0*1024*64)),
	(float)( 0x88801C/(1024.0*1024*1024)),
	(float)(-0xCB9F27/(1024.0*1024*1024*64)),

	(float)(-0xFFFFF9/(1024.0*1024*32)),
	(float)( 0xAAA6FB/(1024.0*1024*256)),
	(float)(-0xB3D431/(1024.0*1024*1024*8)),

	(float)(-0xAAAAAA/(1024.0*1024*32)),
	(float)( 0xCCCCCD/(1024.0*1024*64)),
	(float)(-0x8F5C29/(1024.0*1024*64)),
};

uint32_t pspFpuGetFCR31(void)
{
	uint32_t ret;

	asm(
			"cfc1 %0, $31\n"
			: "=r"(ret)
	   );

	return ret;
}

void pspFpuSetFCR31(uint32_t var)
{
	asm (
			"ctc1 %0, $31\n"
			:
			: "r"(var)
		);
}

void pspFpuSetRoundmode(enum PspFpuRoundMode mode)
{
	uint32_t fcr;

	fcr = pspFpuGetFCR31();
	fcr &= ~PSP_FPU_RM_MASK;
	fcr |= (mode & PSP_FPU_RM_MASK);
	pspFpuSetFCR31(fcr);
}

enum PspFpuRoundMode pspFpuGetRoundmode(void)
{
	return pspFpuGetFCR31() & PSP_FPU_RM_MASK;
}

uint32_t pspFpuGetFlags(void)
{
	uint32_t fcr;

	fcr = pspFpuGetFCR31();

	return (fcr & PSP_FPU_FLAGS_MASK) >> PSP_FPU_FLAGS_POS;
}

void pspFpuClearFlags(uint32_t clear)
{
	uint32_t fcr;

	clear &= 0x1F;
	fcr = pspFpuGetFCR31();
	fcr &= ~(clear << PSP_FPU_FLAGS_POS);
	pspFpuSetFCR31(fcr);
}

uint32_t pspFpuGetEnable(void)
{
	uint32_t fcr;

	fcr = pspFpuGetFCR31();

	return (fcr & PSP_FPU_ENABLE_MASK) >> PSP_FPU_ENABLE_POS;
}

void pspFpuSetEnable(uint32_t enable)
{
	uint32_t fcr;

	enable &= 0x1F;
	fcr = pspFpuGetFCR31() & ~PSP_FPU_ENABLE_MASK;
	fcr |= enable << PSP_FPU_ENABLE_POS;
	pspFpuSetFCR31(fcr);
}

uint32_t pspFpuGetCause(void)
{
	uint32_t fcr;

	fcr = pspFpuGetFCR31();

	return (fcr & PSP_FPU_CAUSE_MASK) >> PSP_FPU_CAUSE_POS;
}

void pspFpuClearCause(uint32_t clear)
{
	uint32_t fcr;

	clear &= 0x3F;
	fcr = pspFpuGetFCR31();
	fcr &= ~(clear << PSP_FPU_CAUSE_POS);
	pspFpuSetFCR31(fcr);
}

uint32_t pspFpuGetFS(void)
{
	uint32_t fcr;

	fcr = pspFpuGetFCR31();

	return (fcr & PSP_FPU_FS_MASK) >> PSP_FPU_FS_POS;
}

void pspFpuSetFS(uint32_t fs)
{
	uint32_t fcr;

	fcr = pspFpuGetFCR31();
	fcr &= ~PSP_FPU_FS_MASK;

	fcr |= ((fs & 1) << PSP_FPU_FS_POS);

	pspFpuSetFCR31(fcr);
}

uint32_t pspFpuGetCondbits(void)
{
	uint32_t fcr;
	uint32_t cond;

	fcr = pspFpuGetFCR31();
	cond = (fcr & PSP_FPU_CC0_MASK) >> PSP_FPU_CC0_POS;
	cond |= (fcr & PSP_FPU_CC17_MASK) >> (PSP_FPU_CC17_POS-1);

	return cond;
}

void pspFpuClearCondbits(uint32_t clear)
{
	uint32_t fcr;

	clear &= 0xFF;

	fcr = pspFpuGetFCR31();
	fcr &= ~((clear & 1) << PSP_FPU_CC0_POS);
	fcr &= ~((clear & 0xFE) << (PSP_FPU_CC17_POS-1));

	pspFpuSetFCR31(fcr);
}

float pspFpuAbs(float fs)
{
	register float fd;
	asm (
		"abs.s %0, %1\n"
		: "=f"(fd)
		: "f"(fs)
	);
	return (fd);
}

int pspFpuCeil(float fs)
{
	return (__builtin_allegrex_ceil_w_s(fs));
}

int pspFpuFloor(float fs)
{
	return (__builtin_allegrex_floor_w_s(fs));
}

float pspFpuMax(float fs1, float fs2)
{
	register float fd;
	fd = (fs1 > fs2) ? fs1 : fs2;
	return (fd);
}

float pspFpuMin(float fs1, float fs2)
{
	register float fd;
	fd = (fs1 < fs2) ? fs1 : fs2;
	return (fd);
}

float pspFpuNeg(float fs)
{
	register float fd;
	asm (
		"neg.s %0, %1\n"
		: "=f"(fd)
		: "f"(fs)
	);
	return (fd);
}

int pspFpuRound(float fs)
{
	return (__builtin_allegrex_round_w_s(fs));
}

float pspFpuRsqrt(float fs)
{
	return (1.0f / __builtin_allegrex_sqrt_s(fs));
}

float pspFpuSqrt(float fs)
{
	return (__builtin_allegrex_sqrt_s(fs));
}

int pspFpuTrunc(float fs)
{
	return (__builtin_allegrex_trunc_w_s(fs));
}

float pspFpuFmod(float fs, float fd)
{
	float v;
	asm (
		".set push\n"
		".set noreorder\n"
		"div.s %0, %1, %2\n"		// v = fs / fd
		"trunc.w.s %0, %0\n"		// v = trunc(v)
		"cvt.s.w %0, %0\n"		// v = (float)v = (float)trunc(v)
		"mul.s %0, %0, %2\n"		// v = v * fd
		"sub.s %0, %1, %0\n"		// v = fs - v*fd = fs - trunc(fs / fd)*fd
		".set pop\n"
		: "=&f"(v)
		: "f"(fs), "f"(fd)
	);
	return (v);
}

float pspFpuFrac(float fs)
{
	float v;
	asm (
		".set push\n"
		".set noreorder\n"
		"trunc.w.s %0, %1\n"		// v = trunc(fs)
		"cvt.s.w %0, %0\n"		// v = (float)v = (float)trunc(fs)
		"sub.s %0, %1, %0\n"		// v = fs - v
		".set pop\n"
		: "=&f"(v)
		: "f"(fs)
	);
	return (v);
}

float pspFpuReinterpretFloat(uint32_t ui)
{
	float v;
	asm (
		"mtc1 %1, %0\n"
		: "=f"(v)
		: "r"(ui)
	);
	return (v);
}

uint32_t pspFpuReinterpretUint(float fs)
{
	unsigned int v;
	asm (
		"mfc1 %0, %1\n"
		: "=r"(v)
		: "f"(fs)
	);
	return (v);
}

int   pspFpuIsEqual(float fs1, float fs2)
{
	int v;
	asm (
		".set push\n"
		".set noreorder\n"
		"c.eq.s %2, %1\n"		// compare fs1 to fs2
		"move %0, $0\n"			// v = 0
		"bc1tl 0f\n"			// if (fs1==fs2) goto 0f
		"addiu %0, $0, 1\n"		// if (fs1==fs2) v = 1
		"0:\n"
		".set pop\n"
		: "=r"(v)
		: "f"(fs1), "f"(fs2)
	);
	return (v);
}

float pspFpuSignFloat(float fs)
{
	float fv;
	asm (
		".set push\n"
		".set noreorder\n"
		"mfc1 $8, %1\n"			// t0 = fs
		"lui $10, 0x3F80\n"		// t2 = 0x3F800000(1.0f)
		"srl $9, $8, 23\n"		// t1 = t0>>23
		"srl $8, $8, 31\n"		// t0 = t0>>31
		"andi $9, $9, 0x00FF\n"		// t1 = t1 & 0x00FF
		"sll $8, $8, 31\n"		// t0 = t0<<31 = (fs>=0) ? 0 : 0x80000000
		"movz $10, $0, $9\n"		// t2 = (t1==0) ? 0 : t2
		"or $10, $10, $8\n"		// t2 = t2 | t0
		"mtc1 $10, %0\n"		// fv = t2
		".set pop\n"
		: "=f"(fv)
		: "f"(fs)
		: "$8", "$9", "$10"
	);
	return (fv);
}

int pspFpuSignInt(float fs)
{
	int v;
	asm (
		".set push\n"
		".set noreorder\n"
		"mfc1 %0, %1\n"			// v = fs
		"lui $8, 0x7F80\n"		// t0 = 0x7F800000(binary representaion 1.0 * 2^(255-127))
		"and $8, $8, %0\n"		// t0 = at & v
		"sra %0, %0, 30\n"		// v  = fs>>30 = (fs>=0) ? 0or1 : -1or-2
		"or %0, %0, 1\n"		// v  = v | 1  = (fs>=0) ? 1 : -1
		"movz %0, $0, $8\n"		// v  = (t0==0) ? 0 : v
		".set pop\n"
		: "=r"(v)
		: "f"(fs)
		: "$8"
	);
	return (v);
}

float pspFpuPositiveZero(void)
{
	float v;
	asm (
		"mtc1 $0, %0\n"			// v = 0.0f
		: "=f"(v)
	);
	return (v);
}

float pspFpuNegativeZero(void)
{
	float v;
	asm (
		".set push\n"
		".set noreorder\n"
		"lui $8, 0x8000\n"		// t0 = 0x80000000
		"mtc1 $8, %0\n"			// v = -0.0f
		".set pop\n"
		: "=f"(v)
		:
		: "$8"
	);
	return (v);
}

int pspFpuIsZero(float f)
{
	int v;
	asm (
		".set push\n"
		".set noreorder\n"
		"mfc1 $8, %1\n"			// t0 = f
		"sra %0, $8, 30\n"		// v  = t0>>30
		"sll $8, $8, 1\n"		// t0 = t0<<1
		"ori %0, %0, 0x0001\n"		// v  = v | 1 = (f>=0) ? +1 : -1
		"movn %0, $0, $8\n"		// v  = (t0!=0) ? 0 : v
		".set pop\n"
		: "=r"(v)
		: "f"(f)
		: "$8"
	);
	return (v);
}

int pspFpuIsPositiveZero(float f)
{
	int v;
	asm (
		".set push\n"
		".set noreorder\n"
		"mfc1 %0, %1\n"			// v  = f
		"sltiu %0, %0, 1\n"		// v  = (v < 1)
		".set pop\n"
		: "=r"(v)
		: "f"(f)
	);
	return (v);
}

int pspFpuIsNegativeZero(float f)
{
	int v;
	asm (
		".set push\n"
		".set noreorder\n"
		"mfc1 %0, %1\n"			// v  = f
		"lui $8, 0x8000\n"		// t0 = 0x80000000
		"xor %0, %0, $8\n"		// v  = v ^ t0
		"sltiu %0, %0, 1\n"		// v  = (v < 1)
		".set pop\n"
		: "=r"(v)
		: "f"(f)
		: "$8"
	);
	return (v);
}

int pspFpuIsDenormal(float f)
{
	int v;
	asm (
		".set push\n"
		".set noreorder\n"
		"mfc1 $8, %1\n"			// t0 = f
		"lui $9, 0x7F80\n"		// t1 = 0x7F800000
		"or %0, $8, $9\n"		// v  = t0 | t1 = t0 | 0x7F800000
		"and $9, $8, $9\n"		// t1 = t0 & t1 = t0 & 0x7F800000
		"sra %0, %0, 30\n"		// v  = v>>30   = (t0>=0) ? +1 : -1
		"sll $8, $8, 9\n"		// t0 = t0<<9
		"movn %0, $0, $9\n"		// v  = (t1!=0) ? 0 : v		if (exp!=0) is not denormal number
		"movz %0, $0, $8\n"		// v  = (t0==0) ? 0 : v		if (frac==0) is not decnormal number
		".set pop\n"
		: "=r"(v)
		: "f"(f)
		: "$8", "$9"
	);
	return (v);
}

int   pspFpuIsZeroOrDenormal(float f)
{
	int v;
	asm (
		".set push\n"
		".set noreorder\n"
		"mfc1 $8, %1\n"			// t0 = f
		"lui $9, 0x7F80\n"		// t1 = 0x7F800000
		"or %0, $8, $9\n"		// v  = t0 | t1 = t0 | 0x7F800000
		"and $9, $8, $9\n"		// t1 = t0 & t1 = t0 & 0x7F800000
		"sra %0, %0, 30\n"		// v  = v>>30   = (t0>=0) ? +1 : -1
		"movn %0, $0, $9\n"		// v  = (t1!=0) ? 0 : v		if (exp!=0) is not denormal number
		".set pop\n"
		: "=r"(v)
		: "f"(f)
		: "$8", "$9"
	);
	return (v);
}

float pspFpuPositiveInf(void)
{
	float v;
	asm (
		".set push\n"
		".set noreorder\n"
		"lui $8, 0x7F80\n"		// t0 = 0x7F800000
		"mtc1 $8, %0\n"			// v  = t0 = +Infinity
		".set pop\n"
		: "=f"(v)
		:
		: "$8"
	);
	return (v);
}

float pspFpuNegativeInf(void)
{
	float v;
	asm (
		".set push\n"
		".set noreorder\n"
		"lui $8, 0xFF80\n"		// t0 = 0xFF800000
		"mtc1 $8, %0\n"			// v  = t0 = -Infinity
		".set pop\n"
		: "=f"(v)
	);
	return (v);
}

int pspFpuIsInf(float f)
{
	int v;
	asm (
		".set push\n"
		".set noreorder\n"
		"mfc1 $8, %1\n"			// t0 = f
		"sll $9, $8, 1\n"		// t1 = t0<<1
		"sra %0, $8, 30\n"		// v  = t0>>30
		"srl $9, $9, 24\n"		// t1 = t1>>24
		"sll $8, $8, 9\n"		// t0 = t0<<9
		"ori %0, %0, 0x0001\n"		// v  = v | 0x00000001 = (f>=0) ? +1 : -1
		"sltiu $9, $9, 0x00FF\n"	// t1 = (t1<0xFF)
		"movn %0, $0, $8\n"		// v  = (t0!=0) ? 0 : v		if (frac!=0) is not Infinity
		"movn %0, $0, $9\n"		// v  = (t1!=0) ? 0 : v		if (exp!=0xFF) is not Infinity
		".set pop\n"
		: "=r"(v)
		: "f"(f)
		: "$8", "$9"
	);
	return (v);
}

float pspFpuPositiveNaN(void)
{
	float v;
	asm (
		".set push\n"
		".set noreorder\n"
		"lui $8, 0x7F80\n"
		"ori $8, $8, 0x0001\n"		// t0 = 0x7F800001
		"mtc1 $8, %0\n"			// v = t0 = +SNaN(0x000001)
		".set pop\n"
		: "=f"(v)
		:
		: "$8"
	);
	return (v);
}

float pspFpuNegativeNaN(void)
{
	float v;
	asm (
		".set push\n"
		".set noreorder\n"
		"lui $8, 0xFF80\n"
		"ori $8, $8, 0x0001\n"		// t0 = 0xFF800001
		"mtc1 $8, %0\n"			// v = t0 = -SNaN(0x000001)
		".set pop\n"
		: "=f"(v)
		:
		: "$8"
	);
	return (v);
}

float pspFpuPositiveQNaN(void)
{
	float v;
	asm (
		".set push\n"
		".set noreorder\n"
		"lui $8, 0x7FC0\n"		// t0 = 0x7FC00000
		"mtc1 $8, %0\n"			// v = t0 = +QNaN
		".set pop\n"
		: "=f"(v)
		:
		: "$8"
	);
	return (v);
}

float pspFpuNegativeQNaN(void)
{
	float v;
	asm (
		".set push\n"
		".set noreorder\n"
		"lui $8, 0xFFC0\n"		// t0 = 0xFFC00000
		"mtc1 $8, %0\n"			// v = t0 = -QNaN
		".set pop\n"
		: "=f"(v)
		:
		: "$8"
	);
	return (v);
}

float pspFpuPositiveSNaN(unsigned int uiSignal)
{
	float v;
	asm (
		".set push\n"
		".set noreorder\n"
		"addiu $9, $0, 1\n"		// t1 = 0x00000001
		"ext $8, %1, 0, 22\n"		// t0 = uiSignal & 0x003FFFFF
		"movn $9, $8, $8\n"		// t1 = (t0!=0) ? t0 : t1
		"lui $8, 0x7F80\n"		// t0 = 0x7F800000
		"or $9, $9, $8\n"		// t1 = t1 | t0
		"mtc1 $9, %0\n"			// v  = t1
		".set pop\n"
		: "=f"(v)
		: "r"(uiSignal)
		: "$8", "$9"
	);
	return (v);
}

float pspFpuNegativeSNaN(unsigned int uiSignal)
{
	float v;
	asm (
		".set push\n"
		".set noreorder\n"
		"addiu $9, $0, 1\n"		// t1 = 0x00000001
		"ext $8, %1, 0, 22\n"		// t0 = uiSignal & 0x003FFFFF
		"movn $9, $8, $8\n"		// t1 = (t0!=0) ? t0 : t1
		"lui $8, 0xFF80\n"		// t0 = 0xFF800000
		"or $9, $9, $8\n"		// t1 = t1 | t0
		"mtc1 $9, %0\n"			// v  = t1
		".set pop\n"
		: "=f"(v)
		: "r"(uiSignal)
		: "$8", "$9"
	);
	return (v);
}

int pspFpuIsNaN(float f)
{
	int v;
	asm (
		".set push\n"
		".set noreorder\n"
		"lui %0, 0x807F\n"		//
		"mfc1 $8, %1\n"			// t0 = f
		"ori %0, %0, 0xFFFF\n"		// v  = 0x807FFFFF
		"sll $9, $8, 1\n"		// t1 = t0<<1
		"and %0, %0, $8\n"		// v  = v & t0
		"srl $9, $9, 24\n"		// t1 = t1>>24
		"sll $8, $8, 9\n"		// t0 = t0<<9
		"sltiu $9, $9, 0x00FF\n"	// t1 = (t1<0xFF)
		"movz %0, $0, $8\n"		// v  = (t0==0) ? 0 : v		if (frac==0) is not NaN
		"movn %0, $0, $9\n"		// v  = (t1!=0) ? 0 : v		if (exp!=0xFF) is not NAN
		".set pop\n"
		: "=r"(v)
		: "f"(f)
		: "$8", "$9"
	);
	return (v);
}

int pspFpuIsInfOrNaN(float f)
{
	int v;
	asm (
		".set push\n"
		".set noreorder\n"
		"mfc1 %0, %1\n"			// v  = f
		"sll $8, %0, 1\n"		// t0 = v<<1
		"sra %0, %0, 30\n"		// v  = v>>30
		"srl $8, $8, 24\n"		// t0 = t0>>24
		"ori %0, %0, 0x0001\n"		// v  = v | 0x00000001 = (f>=0) ? +1 : -1
		"sltiu $8, $8, 0x00FF\n"	// t0 = (t0<0xFF)
		"movn %0, $0, $8\n"		// v  = (t0!=0) ? 0 : v		if (exp!=0xFF) is neither NAN nor Infinity
		".set pop\n"
		: "=r"(v)
		: "f"(f)
		: "$8"
	);
	return (v);
}

float pspFpuNormalizePhase(float fs)
{
	const float f2pi = PSP_MATH_TWOPI;
	float fd;

	asm (
		".set push\n"
		".set noreorder\n"
		"mfc1 $9,  %1\n"		// t1 = f0
		"div.s $f0, $f0, %2\n"		// f0 = f0 / f2pi = fs / 2PI
		"round.w.s $f0, $f0\n"		// f0 = (int)(f0+0.5)
		"cvt.s.w $f0, $f0\n"		// f0 = float(f0)
		"mul.s $f0, $f0, %2\n"		// f0 = f0 * f2pi = fd * 2PI
		"sub.s %0,  %1,  $f0\n"		// fd = fs - f0   = fs - (fd * 2PI)
		".set pop\n"
		: "=f"(fd)
		: "f"(fs), "f"(f2pi)
		: "$f0", "$8", "$9"
	);
	return (fd);
}

float pspFpuLog(float x)
{
	union {
		float f;
		int i;
	} fi;
	int a, b, exponent;
	float y, z;
	fi.f = x;
	if (fi.i <= 0) {
		if ((fi.i & 0x7fffffff) == 0) {
			fi.i = 0xff800000; /* -INF */
			return fi.f;
		}
		fi.i = 0xff80ffff; /* Quiet NaN */
		return fi.f;
	}

	b = (fi.i & 0x007fffff);
	a = b - (1<<23);
	exponent = fi.i;
	if (b <= 0x3504F3) {
		a = b;
		b = b - (1 << 23);
		exponent -= (1<<23);
	}
	b = b - (1 << 23) + (1<<25);

	x = (float)(a) / (float)(b);
	z = (((exponent>>23)-126) * 0xB17218) * (float)(1.0/(1<<24));
	y = x * x;
	return z + x * (((logPoly[2] * y + logPoly[1]) * y) + logPoly[0]);
}

float pspFpuExp(float x)
{
	/*
	 * exp(x)=e^x=e^(y * log2)=2^Y
	 *  =2^z * 2^y
	 *  =2^z * (2^(y/2))^2
	 *  =2^z * (e^(f/2))^2
	 *  =2^z * (e^(f/4))^4
	 * where y=x/log 2
	 * z=nearest(y) , -0.5 <= f=y-z < 0.5
	 */
	union {
		float f;
		int i;
	} fi;
	float z, f;

	fi.f = x;
	fi.i &= 0x7fffffff;
	if (fi.i >= 0x42b00f34) {/* arround 88.03 */
		/* overflow */
		if (x != x) {
			return x; /* NaN */
		}
		if (fi.i < 0) {
			return 0.0; /* underflow */
		}
		fi.i = 0x7f800000;
		return fi.f; /* +INF */
	}

	f = fi.f * (float)PSP_MATH_LOG2E;

	z = __builtin_allegrex_round_w_s(f);
	f = f-z;
	fi.i = z;
	if (x < 0)
		fi.i = -fi.i;
	fi.i = (fi.i+127) << 23;

	/* use Pade aprox. */
	f = (6.0f + (float)(4.0*PSP_MATH_LN2 * 0.25)*f
	     + (float)(0.9996*PSP_MATH_LN2*0.25*PSP_MATH_LN2*0.25)*f*f)
	    / (6.0f - (float)(2.0*PSP_MATH_LN2 * 0.25)*f);
	f *= f;
	fi.f *= f*f;
	return fi.f;
}

static float _pspFpuSinMain(float x)
{
	float y = x*x;
	return x * (((triPoly[4] * y
				+ triPoly[3]) * y
				+ triPoly[2]) * y
				+ triPoly[1]);
}

static float _pspFpuCosMain(float x)
{
	float y = x*x;
	return ((triPoly[7] * y
			+ triPoly[6]) * y
			+ triPoly[5]) * y
			+ triPoly[1];
}

static float _pspFpuAtanMain(float x)
{
	float y = x*x;
	return x * (((triPoly[10] * y
				+ triPoly[9]) * y
				+ triPoly[8]) * y
				+ triPoly[1]);
}


float pspFpuSin(float x)
{
	float pi2;
	int sign = 1;

	/* NaN */
	if (x != x) {
		return x;
	}

	pi2 = triPoly[0];
	if (x < 0.0f) {
		sign = -1;
		x = -x;
	}

	if (x > pi2) {
		float y = x / pi2;
		x -= (float)((int)y) * pi2;
	}

	pi2 *= 0.5f;
	if (x > pi2) {
		x -= pi2;
		sign = -sign;
	}

	if (x > pi2*0.5f) {
		x = pi2 - x;
	}
	if (x > (float)(PSP_MATH_PI * (0.5 - COS_SIN_DIV))) {
		return _pspFpuCosMain(pi2*0.5f - x) * sign;
	}

	return _pspFpuSinMain(x) * sign;
}


float pspFpuCos(float x)
{
	float pi2;
	int sign = 1;

	/* NaN */
	if (x != x) {
		return x;
	}

	pi2 = triPoly[0];
	if (x < 0.0f) {
		x = -x;
	}

	if (x > pi2) {
		float y = x / pi2;
		x -= (float)((int)y) * pi2;
	}

	pi2 *= 0.5f; // pi2 = PI
	if (x > pi2) {
		x -= pi2;
		sign = -1;
	}

	if (x > pi2*0.5f) {
		sign = -sign;
		x = pi2 - x;
	}
	if (x > (float) (PSP_MATH_PI * COS_SIN_DIV)) {
		return _pspFpuSinMain(pi2*0.5f - x) * sign;
	}

	return _pspFpuCosMain(x) * sign;
}

static float _atanf(float x)
{
	if (x < 0.19890f) {
		return _pspFpuAtanMain(x);
	}
	if (x < 0.668106f) {
		return (float)(PSP_MATH_PI / 8)
			+ _pspFpuAtanMain((x - (float)(PSP_MATH_SQRT2 - 1)) / (1.0f + ((float)(PSP_MATH_SQRT2 - 1)*x)));
	}
	return ((float)PSP_MATH_PI / 4) + _pspFpuAtanMain((x - 1.0f) / (x + 1.0f));
}


float pspFpuAtan(float x)
{
	int sign = 1;

	/* NaN */
	if (x != x) {
		return x;
	}

	if (x < 0.0f) {
		x = -x;
		sign = -1;
	}
	if (x >= 1.0f) {
		/*J atan(x) = pi/2 - atan(1/x) */
		x = 1.0f / x;
		x = ((float)(PSP_MATH_PI / 2)) - _atanf(x);
	} else {
		x = _atanf(x);
	}
	return x * (float)sign;
}

float pspFpuAsin(float x)
{
	x = x*x;
	return pspFpuAtan(__builtin_allegrex_sqrt_s(x/(1.0f-x)));
}

float pspFpuAcos(float x)
{
	x = x*x;
	return pspFpuAtan(__builtin_allegrex_sqrt_s((1.0f-x)/x));
}
