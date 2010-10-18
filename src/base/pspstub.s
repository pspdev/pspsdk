# common.s - GAS macros for creating import libraries.
#
# Use STUB_START to declare the start of an import library.  The module parameter
# is the name of the library to import, flags_ver is both the import flags and library
# version, and stub_len is both the number of stubs to import and the size of the
# stub itself (in 32-bit words).
# Use the STUB_FUNC macro for each stub you want to import.  The funcid parameter is
# the 32-bit SHA1-derived NID value, and the funcname is the name you want to call
# the imported function.
# Use STUB_END to declare the end of your import library.

.macro STUB_START module, flags_ver, stub_len

	.set push
	.section .rodata.sceResident, "a"
	.word   0
__stub_modulestr_\module:
	.asciz  "\module"
	.align  2

	.section .lib.stub, "a", @progbits
	.word   __stub_modulestr_\module
	.word   \flags_ver
	.word   \stub_len
	.word   __stub_idtable_\module
	.word   __stub_text_\module

	.section .rodata.sceNid, "a"
__stub_idtable_\module:

	.section .sceStub.text, "ax", @progbits
__stub_text_\module:

	.set pop
.endm

.macro STUB_FUNC funcid, funcname

	.set push
	.set noreorder

	.section .sceStub.text, "ax", @progbits
	.globl  \funcname
	.type   \funcname, @function
	.ent    \funcname, 0
\funcname:
	jr	$ra
	nop
	.end    \funcname
	.size   \funcname, .-\funcname

	.section .rodata.sceNid
	.word   \funcid

	.set pop
.endm

.macro STUB_FUNC_WITH_ALIAS funcid, funcname, alias

	.set push
	.set noreorder

	.section .sceStub.text, "ax", @progbits
	.globl  \alias
	.type   \alias, @function
\alias:
	.globl  \funcname
	.type   \funcname, @function
	.ent    \funcname, 0
\funcname:
	jr	$ra
	nop
	.end    \funcname
	.size   \funcname, .-\funcname

	.section .rodata.sceNid
	.word   \funcid

	.set pop
.endm

.macro STUB_END
.endm
