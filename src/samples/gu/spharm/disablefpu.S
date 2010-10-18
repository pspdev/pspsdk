/*
#
#	This disables FPU exceptions
#
#	extern void _DisableFPUExceptions(void);
*/

#include <as_reg_compat.h>

    .set push 
    .set noreorder 
    .globl _DisableFPUExceptions
    .ent _DisableFPUExceptions
_DisableFPUExceptions: 
    cfc1    $2, $31 
    lui     $8, 0x80 
    and     $8, $2, $8     # Mask off all bits except for 23 of FCR 
    ctc1    $8, $31 
    jr      $31 
    nop 
    .end _DisableFPUExceptions
    .set pop 
