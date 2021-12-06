
.global __lib_ent_top
.global __lib_ent_bottom
.global __lib_stub_top
.global __lib_stub_bottom

.set push
.section .lib.ent.top, "a", @progbits
.align 2
.word 0
__lib_ent_top:
.section .lib.ent.btm, "a", @progbits
.align 2
__lib_ent_bottom:
.word 0
.section .lib.stub.top, "a", @progbits
.align 2
.word 0
__lib_stub_top:
.section .lib.stub.btm, "a", @progbits
.align 2
__lib_stub_bottom:
.word 0
.set pop
.text

