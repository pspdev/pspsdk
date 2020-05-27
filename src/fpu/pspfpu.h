/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspfpu.h - Prototypes for the FPU library
 *
 * Copyright (c) 2009 JetCube
 * Copyright (c) 2006 TyRaNiD (James F.)
 *
 */
#ifndef __PSPFPU_H__
#define __PSPFPU_H__

#include <stdint.h>

/* Note the bit settings in here come from an NEC MIPSv4 document,
 * they seem sensible.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** Enumeration for FPU rounding modes */
enum PspFpuRoundMode
{
	/** Round to nearest representable value */
	PSP_FPU_RN = 0,
	/** Round towards zero */
	PSP_FPU_RZ = 1,
	/** Round towards plus infinity */
	PSP_FPU_RP = 2,
	/** Round towards minus infinity */
	PSP_FPU_RM = 3,
};

/** Mask value for rounding mode */
#define PSP_FPU_RM_MASK 0x03

/** Enumeration for FPU exceptions */
enum PspFpuExceptions
{
	/** Inexact operation exception */
	PSP_FPU_EXCEPTION_INEXACT   = 0x01,
	/** Underflow exception */
	PSP_FPU_EXCEPTION_UNDERFLOW = 0x02,
	/** Overflow exception */
	PSP_FPU_EXCEPTION_OVERFLOW  = 0x04,
	/** Division by zero exception */
	PSP_FPU_EXCEPTION_DIVBYZERO = 0x08,
	/** Invalid operation exception */
	PSP_FPU_EXCEPTION_INVALIDOP = 0x10,
	/** Unimplemented operation exception (only supported in the cause bits) */
	PSP_FPU_EXCEPTION_UNIMPOP   = 0x20,
	/** All exceptions */
	PSP_FPU_EXCEPTION_ALL       = 0x3F
};

/** Bit position of the flag bits */
#define PSP_FPU_FLAGS_POS   2
/** Bit position of the enable bits */
#define PSP_FPU_ENABLE_POS 7
/** Bit position of the cause bits */
#define PSP_FPU_CAUSE_POS  12
/** Bit position of the cc0 bit */
#define PSP_FPU_CC0_POS    23
/** Bit position of the fs bit */
#define PSP_FPU_FS_POS     24
/** Bit position of the cc1->7 bits */
#define PSP_FPU_CC17_POS   25

#define PSP_FPU_FLAGS_MASK  (0x1F << PSP_FPU_FLAGS_POS)
#define PSP_FPU_ENABLE_MASK (0x1F << PSP_FPU_ENABLE_POS)
#define PSP_FPU_CAUSE_MASK  (0x3F << PSP_FPU_CAUSE_POS)
#define PSP_FPU_CC0_MASK    (1 << PSP_FPU_CC0_POS)
#define PSP_FPU_FS_MASK     (1 << PSP_FPU_FS_POS)
#define PSP_FPU_CC17_MASK   (0x7F << PSP_FPU_CC17_POS)

/**
 * Get the current value of the control/status register
 *
 * @return The value of the control/status register
 */
uint32_t pspFpuGetFCR31(void);

/**
 * Set the current value of the control/status register
 *
 * @param var - The value to set.
 */
void pspFpuSetFCR31(uint32_t var);

/**
 * Set the current round mode
 *
 * @param mode - The rounding mode to set, one of ::PspFpuRoundMode
 */
void pspFpuSetRoundmode(enum PspFpuRoundMode mode);

/**
 * Get the current round mode
 *
 * @return The round mode, one of ::PspFpuRoundMode
 */
enum PspFpuRoundMode pspFpuGetRoundmode(void);

/**
 * Get the exception flags (set when an exception occurs but
 * the actual exception bit is not enabled)
 *
 * @return Bitmask of the flags, zero or more of ::PspFpuExceptions
 */
uint32_t pspFpuGetFlags(void);

/**
 * Clear the flags bits
 *
 * @param clear - Bitmask of the bits to clear, one or more of ::PspFpuExceptions
 */
void pspFpuClearFlags(uint32_t clear);

/**
 * Get the exception enable flags
 *
 * @return Bitmask of the flags, zero or more of ::PspFpuExceptions
 */
uint32_t pspFpuGetEnable(void);

/**
 * Set the enable flags bits
 *
 * @param enable - Bitmask of exceptions to enable, zero or more of ::PspFpuExceptions
 */
void pspFpuSetEnable(uint32_t enable);

/**
 * Get the cause bits (only useful if you installed your own exception handler)
 *
 * @return Bitmask of flags, zero or more of ::PspFpuExceptions
 */
uint32_t pspFpuGetCause(void);

/**
 * Clear the cause bits
 *
 * @param clear - Bitmask of the bits to clear, one or more of ::PspFpuExceptions
 *
 */
void pspFpuClearCause(uint32_t clear);

/**
 * Get the current value of the FS bit (if FS is 0 then an exception occurs with
 * denormalized values, if 1 then they are rewritten as 0.
 *
 * @return The current state of the FS bit (0 or 1)
 */
uint32_t pspFpuGetFS(void);

/**
 * Set the FS bit
 *
 * @param fs - 0 or 1 to unset or set fs
 */
void pspFpuSetFS(uint32_t fs);

/**
 * Get the condition flags (8 bits)
 *
 * @return The current condition flags
 */
uint32_t pspFpuGetCondbits(void);

/**
 * Clear the condition bits
 *
 * @param clear - Bitmask of the bits to clear
 */
void pspFpuClearCondbits(uint32_t clear);

/**
 * returns absolute value
 */
float pspFpuAbs(float f);

/**
 * Round up
 */
int   pspFpuCeil(float f);

/**
 * Truncate
 */
int   pspFpuFloor(float f);

/**
 * select maximum value
 */
float pspFpuMax(float f1, float f2);

/**
 * select minimum value
 */
float pspFpuMin(float f1, float f2);

/**
 * Sign reversal
 */
float pspFpuNeg(float f);

/**
 * Round to nearest
 */
int pspFpuRound(float f);

/*
 * Reciprocal of square root
 */
float pspFpuRsqrt(float f);

/**
 * Square root
 */
float pspFpuSqrt(float f);

/**
 * Round towards zero
 */
int pspFpuTrunc(float f);

/**
 *
 */
float pspFpuFmod(float fs, float fd);

/**
 *
 */
float pspFpuFrac(float f);

/**
 *
 */
float pspFpuReinterpretFloat(uint32_t ui);

/**
 *
 */
uint32_t pspFpuReinterpretUint(float f);

/**
 *
 */
int pspFpuIsEqual(float f1, float f2);

/**
 *
 */
float pspFpuSignFloat(float f);

/**
 *
 */
int pspFpuSignInt(float f);

/**
 * Positive zero
 */
float pspFpuPositiveZero(void);

/**
 * Negative zero
 */
float pspFpuNegativeZero(void);

/**
 * Test for zero value
 */
int pspFpuIsZero(float f);

/**
 * Test for positive zero
 */
int pspFpuIsPositiveZero(float f);

/**
 * Test for negative zero
 */
int pspFpuIsNegativeZero(float f);

/**
 * Test for denormalized number
 */
int pspFpuIsDenormal(float f);

/**
 * Test for zero or denormalized number
 */
int pspFpuIsZeroOrDenormal(float f);

/**
 * Positive infinity
 */
float pspFpuPositiveInf(void);

/**
 * Negative infinity
 */
float pspFpuNegativeInf(void);

/**
 * Test for infinity
 */
int pspFpuIsInf(float f);

/**
 * NaN (positive SNaN)
 */
float pspFpuPositiveNaN(void);

/**
 * NaN (negative SNaN)
 */
float pspFpuNegativeNaN(void);

/**
 * Quiet NaN (positive QNaN)
 */
float pspFpuPositiveQNaN(void);

/**
 * Quiet NaN (positive QNaN)
 */
float pspFpuNegativeQNaN(void);

/**
 * Signaling NaN (positive SNaN)
 */
float pspFpuPositiveSNaN(unsigned int uiSignal);

/**
 * Signaling NaN (negative SNaN)
 */
float pspFpuNegativeSNaN(unsigned int uiSignal);

/**
 * Test for NaN
 */
int pspFpuIsNaN(float f);

/**
 * Test for infinity or NaN
 */
int pspFpuIsInfOrNaN(float f);

/**
 *
 */
float pspFpuNormalizePhase(float f);

/**
 * Sine
 */
float pspFpuSin(float x);

/**
 * Cosine
 */
float pspFpuCos(float x);

/**
 * Arc tangent
 */
float pspFpuAtan(float x);

/**
 * Natural Logarithm
 */
float pspFpuLog(float x);

/**
 * Exponential
 */
float pspFpuExp(float x);

/**
 * ArcSin
 */
float pspFpuAsin(float x);

/**
 * ArcCos
 */
float pspFpuAcos(float x);

/**
 * convert float to double
 */
double pspFpuFloatToDouble(float a);

/**
 * convert double to float
 */
float  pspFpuDoubleToFloat(double a);

#ifdef __cplusplus
}
#endif

#endif	/* __PSPFPU_H__ */
