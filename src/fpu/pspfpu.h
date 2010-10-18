/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspfpu.h - Prototypes for the FPU library
 *
 * Copyright (c) 2006 TyRaNiD (James F.) 
 *
 * $Id: pspfpu.h 1782 2006-02-04 12:57:05Z tyranid $
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
enum FpuRoundMode
{
	/** Round to nearest representable value */
	FPU_RN = 0,
	/** Round towards zero */
	FPU_RZ = 1,
	/** Round towards plus infinity */
	FPU_RP = 2,
	/** Round towards minus infinity */ 
	FPU_RM = 3,
};

/** Mask value for rounding mode */
#define FPU_RM_MASK 0x03 

/** Enumeration for FPU exceptions */
enum FpuExceptions
{
	/** Inexact operation exception */
	FPU_EXCEPTION_INEXACT   = 0x01,
	/** Underflow exception */
	FPU_EXCEPTION_UNDERFLOW = 0x02,
	/** Overflow exception */
	FPU_EXCEPTION_OVERFLOW  = 0x04,
	/** Division by zero exception */
	FPU_EXCEPTION_DIVBYZERO = 0x08,
	/** Invalid operation exception */
	FPU_EXCEPTION_INVALIDOP = 0x10,
	/** Unimplemented operation exception (only supported in the cause bits) */
	FPU_EXCEPTION_UNIMPOP   = 0x20,
	/** All exceptions */
	FPU_EXCEPTION_ALL       = 0x3F
};

/** Bit position of the flag bits */
#define FPU_FLAGS_POS   2
/** Bit position of the enable bits */
#define FPU_ENABLE_POS 7
/** Bit position of the cause bits */
#define FPU_CAUSE_POS  12
/** Bit position of the cc0 bit */
#define FPU_CC0_POS    23
/** Bit position of the fs bit */
#define FPU_FS_POS     24
/** Bit position of the cc1->7 bits */
#define FPU_CC17_POS   25

#define FPU_FLAGS_MASK  (0x1F << FPU_FLAGS_POS)
#define FPU_ENABLE_MASK (0x1F << FPU_ENABLE_POS)
#define FPU_CAUSE_MASK  (0x3F << FPU_CAUSE_POS)
#define FPU_CC0_MASK    (1 << FPU_CC0_POS)
#define FPU_FS_MASK     (1 << FPU_FS_POS)
#define FPU_CC17_MASK   (0x7F << FPU_CC17_POS)

/**
 * Get the current value of the control/status register
 *
 * @return The value of the control/status register
 */
uint32_t pspfpu_get_fcr31(void);

/**
 * Set the current value of the control/status register
 *
 * @param var - The value to set.
 */
void pspfpu_set_fcr31(uint32_t var);

/**
 * Set the current round mode
 *
 * @param mode - The rounding mode to set, one of ::FpuRoundMode
 */
void pspfpu_set_roundmode(enum FpuRoundMode mode);

/**
 * Get the current round mode
 *
 * @return The round mode, one of ::FpuRoundMode
 */
enum FpuRoundMode pspfpu_get_roundmode(void);

/**
 * Get the exception flags (set when an exception occurs but
 * the actual exception bit is not enabled)
 *
 * @return Bitmask of the flags, zero or more of ::FpuExceptions
 */
uint32_t pspfpu_get_flags(void);

/** 
 * Clear the flags bits
 *
 * @param clear - Bitmask of the bits to clear, one or more of ::FpuExceptions
 */
void pspfpu_clear_flags(uint32_t clear);

/**
 * Get the exception enable flags
 *
 * @return Bitmask of the flags, zero or more of ::FpuExceptions
 */
uint32_t pspfpu_get_enable(void);

/** 
 * Set the enable flags bits
 *
 * @param enable - Bitmask of exceptions to enable, zero or more of ::FpuExceptions
 */
void pspfpu_set_enable(uint32_t enable);

/**
 * Get the cause bits (only useful if you installed your own exception handler)
 *
 * @return Bitmask of flags, zero or more of ::FpuExceptions
 */
uint32_t pspfpu_get_cause(void);

/**
 * Clear the cause bits
 *
 * @param clear - Bitmask of the bits to clear, one or more of ::FpuExceptions
 *
 */
void pspfpu_clear_cause(uint32_t clear);

/**
 * Get the current value of the FS bit (if FS is 0 then an exception occurs with
 * denormalized values, if 1 then they are rewritten as 0.
 *
 * @return The current state of the FS bit (0 or 1)
 */
uint32_t pspfpu_get_fs(void);

/**
 * Set the FS bit
 *
 * @param fs - 0 or 1 to unset or set fs
 */
void pspfpu_set_fs(uint32_t fs);

/**
 * Get the condition flags (8 bits)
 *
 * @return The current condition flags
 */
uint32_t pspfpu_get_condbits(void);

/**
 * Clear the condition bits
 *
 * @param clear - Bitmask of the bits to clear
 */
void pspfpu_clear_condbits(uint32_t clear);

#ifdef __cplusplus
}
#endif

#endif	/* __PSPFPU_H__ */
