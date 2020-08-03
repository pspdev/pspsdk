#pragma once

#undef __linux__

#undef __UINTPTR_TYPE__
#define __UINTPTR_TYPE__ unsigned int

#if !defined(__ASM__) && !defined(__ASSEMBLY__) && !defined(__ASSEMBLER__)
extern float __builtin_allegrex_ceil_w_s(float);
extern float __builtin_allegrex_floor_w_s(float);
extern float __builtin_allegrex_trunc_w_s(float);
extern float __builtin_allegrex_round_w_s(float);
extern float __builtin_allegrex_sqrt_s(float);
extern int __builtin_allegrex_clz(int);
#endif
