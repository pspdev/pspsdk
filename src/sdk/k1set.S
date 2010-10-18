
	.set noreorder
	.set noat

	.global pspSdkSetK1
	.ent    pspSdkSetK1

pspSdkSetK1:
	move $v0, $k1
	jr	 $ra
	move $k1, $a0

	.end pspSdkSetK1

	.global pspSdkGetK1
	.ent    pspSdkGetK1

pspSdkGetK1:
	jr   $ra
	move $v0, $k1

	.end    pspSdkGetK1
