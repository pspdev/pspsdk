	.set noreorder

	.global me_run
	.global me_end

	.ent me_run

me_run:
	li $2, 0xbfc00060
	li $3, 0
loop:
	addiu $3, $3, 1
	sw $3, 0($2)
	b loop
	nop
me_end:

	.end me_run
