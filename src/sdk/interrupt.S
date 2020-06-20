
	.set noreorder
	.set noat

	.global pspSdkDisableInterrupts
	.ent    pspSdkDisableInterrupts

pspSdkDisableInterrupts:
    .word 0x70020024 // 	mfic	$v0, $0
    .word 0x70000026 // 	mtic	$0, $0
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
    .word 0x70040026 // 	mtic	$a0, $0
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
