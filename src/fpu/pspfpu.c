/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspfpu.h - PSP FPU library
 *
 * Copyright (c) 2006 TyRaNiD (James F.) 
 *
 * $Id: pspfpu.c 1781 2006-02-04 12:53:40Z tyranid $
 */
#include "pspfpu.h"

uint32_t pspfpu_get_fcr31(void)
{
	uint32_t ret;

	asm(
			"cfc1 %0, $31\n"
			: "=r"(ret)
	   );

	return ret;
}

void pspfpu_set_fcr31(uint32_t var)
{
	asm (
			"ctc1 %0, $31\n"
			: 
			: "r"(var)
		);
}

void pspfpu_set_roundmode(enum FpuRoundMode mode)
{
	uint32_t fcr;

	fcr = pspfpu_get_fcr31();
	fcr &= ~FPU_RM_MASK;
	fcr |= (mode & FPU_RM_MASK);
	pspfpu_set_fcr31(fcr);
}

enum FpuRoundMode pspfpu_get_roundmode(void)
{
	return pspfpu_get_fcr31() & FPU_RM_MASK;
}

uint32_t pspfpu_get_flags(void)
{
	uint32_t fcr;

	fcr = pspfpu_get_fcr31();
	
	return (fcr & FPU_FLAGS_MASK) >> FPU_FLAGS_POS;
}

void pspfpu_clear_flags(uint32_t clear)
{
	uint32_t fcr;

	clear &= 0x1F;
	fcr = pspfpu_get_fcr31();
	fcr &= ~(clear << FPU_FLAGS_POS);
	pspfpu_set_fcr31(fcr);
}

uint32_t pspfpu_get_enable(void)
{
	uint32_t fcr;

	fcr = pspfpu_get_fcr31();
	
	return (fcr & FPU_ENABLE_MASK) >> FPU_ENABLE_POS;
}

void pspfpu_set_enable(uint32_t enable)
{
	uint32_t fcr;

	enable &= 0x1F;
	fcr = pspfpu_get_fcr31() & ~FPU_ENABLE_MASK;
	fcr |= enable << FPU_ENABLE_POS;
	pspfpu_set_fcr31(fcr);
}

uint32_t pspfpu_get_cause(void)
{
	uint32_t fcr;

	fcr = pspfpu_get_fcr31();
	
	return (fcr & FPU_CAUSE_MASK) >> FPU_CAUSE_POS;
}

void pspfpu_clear_cause(uint32_t clear)
{
	uint32_t fcr;

	clear &= 0x3F;
	fcr = pspfpu_get_fcr31();
	fcr &= ~(clear << FPU_CAUSE_POS);
	pspfpu_set_fcr31(fcr);
}

uint32_t pspfpu_get_fs(void)
{
	uint32_t fcr;

	fcr = pspfpu_get_fcr31();
	
	return (fcr & FPU_FS_MASK) >> FPU_FS_POS;
}

void pspfpu_set_fs(uint32_t fs)
{
	uint32_t fcr;

	fcr = pspfpu_get_fcr31();
	fcr &= ~FPU_FS_MASK;

	fcr |= ((fs & 1) << FPU_FS_POS);

	pspfpu_set_fcr31(fcr);
}

uint32_t pspfpu_get_condbits(void)
{
	uint32_t fcr;
	uint32_t cond;

	fcr = pspfpu_get_fcr31();
	cond = (fcr & FPU_CC0_MASK) >> FPU_CC0_POS;
	cond |= (fcr & FPU_CC17_MASK) >> (FPU_CC17_POS-1);

	return cond;
}

void pspfpu_clear_condbits(uint32_t clear)
{
	uint32_t fcr;

	clear &= 0xFF;

	fcr = pspfpu_get_fcr31();
	fcr &= ~((clear & 1) << FPU_CC0_POS);
	fcr &= ~((clear & 0xFE) << (FPU_CC17_POS-1));

	pspfpu_set_fcr31(fcr);
}
