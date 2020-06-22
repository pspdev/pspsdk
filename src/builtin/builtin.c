// This file contains manually implemented GCC allegrex builtins for
// clang-compiled code.

#ifdef __clang__
float __builtin_allegrex_ceil_w_s(float f) {
    asm ("ceil.w.s %0, %0" : "+f"(f));
    return f;
}

float __builtin_allegrex_floor_w_s(float f) {
    asm ("floor.w.s %0, %0" : "+f"(f));
    return f;
}

float __builtin_allegrex_trunc_w_s(float f) {
    asm ("trunc.w.s %0, %0" : "+f"(f));
    return f;
}

float __builtin_allegrex_round_w_s(float f) {
    asm ("round.w.s %0, %0" : "+f"(f));
    return f;
}

float __builtin_allegrex_sqrt_s(float f) {
    asm ("sqrt.s %0, %0" : "+f"(f));
    return f;
}
#endif
