#define zero	$0	/* wired zero */
#define at	$1	/* assembler temp */
#define v0	$2	/* return value */
#define v1	$3
#define a0	$4	/* argument registers */
#define a1	$5
#define a2	$6
#define a3	$7
#define t0	$8	/* caller saved */
#define t1	$9
#define t2	$10
#define t3	$11
#define t4	$12
#define t5	$13
#define t6	$14
#define t7	$15
#define s0	$16	/* callee saved */
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24	/* code generator */
#define t9	$25
#define k0	$26	/* kernel temporary */
#define k1	$27
#define gp	$28	/* global pointer */
#define sp	$29	/* stack pointer */
#define fp	$30	/* frame pointer */
#define ra	$31	/* return address */

#define fv0	$f0
#define fv1	$f1
#define ft0	$f2
#define ft1	$f3
#define ft2	$f4
#define ft3	$f5
#define ft4	$f6
#define ft5	$f7
#define ft6	$f8
#define ft7	$f9
#define ft8	$f10
#define ft9	$f11
#define fa0	$f12
#define fa1	$f13
#define fa2	$f14
#define fa3	$f15
#define fa4	$f16
#define fa5	$f17
#define fa6	$f18
#define fa7	$f19
#define fs0	$f20
#define fs1	$f21
#define fs2	$f22
#define fs3	$f23
#define fs4	$f24
#define fs5	$f25
#define fs6	$f26
#define fs7	$f27
#define fs8	$f28
#define fs9	$f29
#define fs10	$f30
#define fs11	$f31

.set	noreorder
.set	noat

.text
.align	4

.global	pspFpuFloatToDouble
.global	pspFpuDoubleToFloat

/**
 * convert float to double
 * double pspFpuFloatToDouble(float a);
 *
 * input: fa0
 * output: v0,v1
 * clobber: t0,t1
 */
.ent	pspFpuFloatToDouble
pspFpuFloatToDouble:
	mfc1	t0, fa0				/* t0 = fa0 */
	ext	t1, t0, 23, 8			/* t1 = (t0 >> 23) & 0xFF */
	beq	t1, zero, ftod_denormal		/* if (t1==0) goto ftod_denormal */
	addiu	v0, t1, (-0x7F+0x3FF)		/* v0 = t1 - 0x7F + 0x3FF */
	xori	t1, t1, 0xFF			/* t1 = t1 ^ 0xFF */
	li	v1, 0x7FF			/* v1 = 0x7FF */
	movz	v0, v1, t1			/* v0 = (t1==0) ? v1 : v0 */
	ext	v1, t0,  3, 20			/* v1 = (t0 >> 3 ) & 0x00FFFFF */
	ins	v1, v0, 20, 11			/* v1 = (v1 & 0x800FFFFF) | ((v0<<20) & 0x7FF00000) */
	sll	v0, t0, 29			/* v0 = (t0 << 29) */
	srl	t0, t0, 31			/* t0 = (t0 >> 31) & 1 */
	jr	ra				/* return */
	ins	v1, t0, 31, 1			/* v1 = (v1 & 0x7FFFFFFF) | ((t0<<31) & 0x80000000) */

ftod_denormal:
	sll	v0, t0, 9			/* v0 = t0 << 9 */
	beql	v0, zero, ftod_zero		/* if (v0==0) goto ftod_zero */
	move	v1, zero			/* v1 = 0 */
	li	v1, 0x380			/* v1 = 0x380 */
	clz	t1, v0				/* t1 = clz(v0) */
	subu	v0, v1, t1			/* v0 = v1 - v0 = 0x380 - clz(t1) */
	sllv	t1, t0, t1			/* t1 = t0 << t1 */
	ext	v1, t1,  2, 20			/* v1 = (t1 >> 2 ) & 0x00FFFFF */
	ins	v1, v0, 20, 11			/* v1 = (v1 & 0x800FFFFF) | ((v0<<20) & 0x7FF00000) */
	sll	v0, t1, 30			/* v0 = (t1 << 30) */
ftod_zero:
	srl	t0, t0, 31			/* t0 = (t0 >> 31) & 1 */
	jr	ra				/* return */
	ins	v1, t0, 31, 1			/* v1 = (v1 & 0x7FFFFFFF) | ((t0<<31) & 0x80000000) */
.end	pspFpuFloatToDouble

/**
 * convert double to float
 * float pspFpuDoubleToFloat(double a);
 * input: a0,a1
 * output: fv0
 * clobber: t0,t1,t2,v0
 */
.ent	pspFpuDoubleToFloat
pspFpuDoubleToFloat:
	ext	t0, a1, 20, 11		/* t0 = (a1>>20) & 0x000007FF */
	beq	t0, zero, dtof_zero	/* if (t0==0) goto dtof_zero */
	xori	t1, t0, 0x7FF		/* t1 = t0 ^ 0x7FF */
	beq	t1, zero, dtof_naninf	/* if (t1==0) goto dtof_naninf */
	addiu	t1, t0, (+0x7F-0x3FF)	/* t1 = t0 + 0x7F - 0x3FF */
	blez	t1, dtof_denormal	/* if (t1<=0) goto dtof_denormal */
	addiu	t2, t1, -0xFE		/* t2 = t1 - 0xFE */
	bgtz	t2, dtof_inf		/* if (t2 > 0) goto dtof_inf */
	move	v0, zero		/* v0 = 0 */

	srl	v0, a0, 29			/* v0 = (a0>>29) & 0x00000007 */
	ins	v0, a1, 3, 20			/* v0 = (v0 & 0xFF800007) | ((a1 & 0FFFFF)<<3) */
	beq	t2, zero, dtof_inf_normal	/* if (t2==0) goto dtof_inf_normal */
dtof_normal:
	srl	t2, a1, 31		/* t2 = (a1>>31) & 1 */
	ins	v0, t2, 31, 1		/* v0 = (v0 & 0x7FFFFFFF) | (t2 << 31) */
	ins	v0, t1, 23, 8		/* v0 = (v0 & 0x8007FFFF) | (t1 << 23) */
	jr	ra			/* return */
	mtc1	v0, fv0			/* fv0 = v0 */
dtof_denormal:
	sll	t0, a1, 12		/* t0 = a1 << 12 */
	srl	v0, t0, 10		/* v0 = t0 >> 10 */
	srl	t0, a0, 30		/* t0 = t0 >> 30 */
	or	v0, v0, t0		/* v0 = v0 | t0 */
	li	t0, 0x00400000		/* t0 = 0x00400000 */
	or	v0, v0, t0		/* v0 = v0 | t0 */
	subu	t0, zero, t1		/* t0 = zero - t1 */
	sltiu	t1, t0, 22		/* t1 = (t0 < 22) */
	beq	t1, zero, dtof_min	/* if (t1==0) goto dtof_min */
	srlv	v0, v0, t0		/* v0 = v0 >> t0 */
	srl	t2, a1, 31		/* t2 = (a1>>31) & 1 */
	ins	v0, t2, 31, 1		/* v0 = (v0 & 0x7FFFFFFF) | (t2 << 31) */
	jr	ra			/* return */
	mtc1	v0, fv0			/* fv0 = v0 */
dtof_zero:
	sll	t0, a1, 12		/* t0 = a1 << 12 */
	or	t0, t0, a0		/* t0 = t0 | a0 */
dtof_min:
	li	v0, 0x00000001		/* v0 = 0x00000001 */
	movz	v0, zero, t0		/* v0 = (t0==0) ? zero : v0 */
	srl	t0, a1, 31		/* t0 = (a1 >> 31) & 1 */
	ins	v0, t0, 31, 1		/* v0 = (v0 & 0x7FFFFFFF) | ((t0<<31) & 0x80000000) */
	jr	ra			/* return */
	mtc1	v0, fv0			/* fv0 = v0 */
dtof_inf_normal:
	nor	t0, zero, a1		/* t0 = ~a1 */
	sll	t0, t0, 12		/* t0 = t0 << 12 */
	bne	t0, zero, dtof_normal	/* if (t0!=0) goto dtof_normal */
	srl	t0, a0, 28		/* t0 = a0 >> 28 */
	sltiu	t0, t0, 0xF		/* t0 = (t0 < 0xF) */
	bne	t0, zero, dtof_normal	/* if (t0!=0) goto dtof_normal */
	nop				/* waste delay slot */
	j	dtof_inf		/* goto dtof_inf */
	move	v0, zero		/* v0 = 0 */
dtof_naninf:
	sll	t0, a1, 12		/* t0 = a1 << 12 */
	or	t1, t0, a0		/* t1 = t0 | a0 */
	srl	v0, t0, 9		/* v0 = t0 >> 9 */
	srl	t0, a0, 29		/* t0 = t0 >> 29 */
	or	v0, v0, t0		/* v0 = v0 | t0 */
	sltiu	t0, v0, 1		/* t0 = (v0 < 1) */
	or	v0, v0, t0		/* v0 = v0 | t0 */
	movz	v0, zero, t1		/* v0 = (t1==0) ? zero : v0 */
dtof_inf:
	li	t0, 0x7F800000		/* t0 = 0x7F800000 */
	or	v0, v0, t0		/* v0 = v0 | t0 */
	srl	t0, a1, 31		/* t0 = (a1 >> 31) & 1 */
	ins	v0, t0, 31, 1		/* v0 = (v0 & 0x7FFFFFFF) | ((t0<<31) & 0x80000000) */
	jr	ra			/* return */
	mtc1	v0, fv0			/* fv0 = v0 */
.end	pspFpuDoubleToFloat
