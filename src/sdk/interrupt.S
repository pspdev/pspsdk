
	.set noreorder
	.set noat

	.global pspSdkDisableInterrupts
	.ent    pspSdkDisableInterrupts

pspSdkDisableInterrupts:
	mfic	$v0, $0
	mtic	$0, $0
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	jr		$ra
	nop

	.end pspSdkDisableInterrupts

	.global pspSdkEnableInterrupts
	.ent    pspSdkEnableInterrupts

pspSdkEnableInterrupts:
	mtic	$a0, $0
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	jr		$ra
	nop

	.end pspSdkEnableInterrupts
