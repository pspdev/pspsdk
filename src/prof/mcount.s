	.set noreorder
	.set noat

	.global _mcount
	.ent _mcount 

_mcount:


# Generated code already substracts 8 bytes
# We store our ra, at and a0-a3
        addu $29, $29, -40
        sd   $31, 0($29)       # store ra
        sd   $1,  8($29)       # at = ra of caller
        sd   $4,  16($29)
        sd   $5,  24($29)
        sd   $6,  32($29)
        sd   $7,  40($29)

# Call internal C handler
        move $4, $1
        move $5, $31
        jal  __mcount
        nop

# Restore registers
        ld   $31, 0($29)
        ld   $1,  8($29)
        ld   $4, 16($29)
        ld   $5, 24($29)
        ld   $6, 32($29)
        ld   $7, 40($29)
        addu $29, $29, 48      # generated code substracts 8 bytes
        j    $31
        move $31, $1           # restore caller's ra

        .end _mcount

		.set reorder
		.set at
