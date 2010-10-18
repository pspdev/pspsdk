/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# $Id: setjmp.S 486 2005-07-05 05:05:45Z mrbrown $
# This is a simple version of setjmp and longjmp.
# Floating point support in.
*/

#include <as_reg_compat.h>

#define O_S0	0x00
#define O_S1	0x04
#define O_S2	0x08
#define O_S3	0x0c
#define O_S4	0x10
#define O_S5	0x14
#define O_S6	0x18
#define O_S7	0x1c
#define O_FP	0x20
#define O_SP	0x24
#define O_RA	0x28
#define O_F20   0x2c
#define O_F21   0x30
#define O_F22   0x34
#define O_F23   0x38
#define O_F24   0x3c
#define O_F25   0x40
#define O_F26   0x44
#define O_F27   0x48
#define O_F28   0x4c
#define O_F29   0x50
#define O_F30   0x54
#define O_F31   0x58

/* int setjmp (jmp_buf);  */
	.globl	setjmp
	.ent	setjmp
setjmp:
	.frame	$sp,0,$31
	
	sw	$s0, O_S0($a0)
	sw	$s1, O_S1($a0)
	sw	$s2, O_S2($a0)
	sw	$s3, O_S3($a0)
	sw	$s4, O_S4($a0)
	sw	$s5, O_S5($a0)
	sw	$s6, O_S6($a0)
	sw	$s7, O_S7($a0)
	sw	$fp, O_FP($a0)
	sw	$sp, O_SP($a0)
	sw	$ra, O_RA($a0)
	
	swc1    $f20, O_F20($a0)
	swc1    $f21, O_F21($a0)
	swc1    $f22, O_F22($a0)
	swc1    $f23, O_F23($a0)
	swc1    $f24, O_F24($a0)
	swc1    $f25, O_F25($a0)
	swc1    $f26, O_F26($a0)
	swc1    $f27, O_F27($a0)
	swc1    $f28, O_F28($a0)
	swc1    $f29, O_F29($a0)
	swc1    $f30, O_F30($a0)
	swc1    $f31, O_F31($a0)


	move	$v0, $0

	jr	$ra

	.end	setjmp

/* volatile void longjmp (jmp_buf, int);  */
	.globl	longjmp
	.ent	longjmp
longjmp:
	.frame	$sp,0,$31

	lw	$s0, O_S0($a0)
	lw	$s1, O_S1($a0)
	lw	$s2, O_S2($a0)
	lw	$s3, O_S3($a0)
	lw	$s4, O_S4($a0)
	lw	$s5, O_S5($a0)
	lw	$s6, O_S6($a0)
	lw	$s7, O_S7($a0)
	lw	$fp, O_FP($a0)
	lw	$sp, O_SP($a0)
	lw	$ra, O_RA($a0)
	
	lwc1    $f20, O_F20($a0)
	lwc1    $f21, O_F21($a0)
	lwc1    $f22, O_F22($a0)
	lwc1    $f23, O_F23($a0)
	lwc1    $f24, O_F24($a0)
	lwc1    $f25, O_F25($a0)
	lwc1    $f26, O_F26($a0)
	lwc1    $f27, O_F27($a0)
	lwc1    $f28, O_F28($a0)
	lwc1    $f29, O_F29($a0)
	lwc1    $f30, O_F30($a0)
	lwc1    $f31, O_F31($a0)

	bne	$a0, $0, 1f
	li	$a0, 1
1:
	move	$v0, $a0

	jr	$ra

	.end longjmp
