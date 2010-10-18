
.macro IMPORT_START module, flags_ver

	.set push
	.section .rodata.sceResident, "a"
	.word   0
__stub_modulestr_\module:
	.asciz  "\module"
	.align  2

	.section .lib.stub, "a", @progbits
	.global __stub_module_\module
__stub_module_\module:
	.word   __stub_modulestr_\module
	.word   \flags_ver
	.word   0x5
	.word   __executable_start
	.word   __executable_start

	.set pop
.endm

.macro IMPORT_FUNC module, funcid, funcname

	.set push
	.set noreorder

	.extern __stub_module_\module
	.section .sceStub.text, "ax", @progbits
	.globl  \funcname
	.type   \funcname, @function
	.ent    \funcname, 0
\funcname:
	.word   __stub_module_\module
	.word   \funcid
	.end    \funcname
	.size   \funcname, .-\funcname

	.section .rodata.sceNid, "a"
	.word   \funcid

	.set pop
.endm

.macro IMPORT_FUNC_WITH_ALIAS module, funcid, funcname, alias

	.set push
	.set noreorder

	.extern __stub_module_\module
	.section .sceStub.text, "ax", @progbits
	.globl  \alias
	.type   \alias, @function
\alias:
	.globl  \funcname
	.type   \funcname, @function
	.ent    \funcname, 0
\funcname:
	.word   __stub_module_\module
	.word   \funcid
	.end    \funcname
	.size   \funcname, .-\funcname

	.section .rodata.sceNid, "a"
	.word   \funcid

	.set pop
.endm
