/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - A more advadced example for checking the GProf profiler.
 * This example demonstrates how to start and stop the profiler multiple times
 *
 * Copyright (c) 2024 Francisco Javier Trujillo Mata - fjtrujy@gmail.com
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

#include <pspmoduleinfo.h>
#include <pspthreadman.h>
#include <pspprof.h>

PSP_MODULE_INFO("GProf Custom Example", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

// Simulates a CPU-bound heavy operation by calculating large numbers of square roots
void heavy_operation_1() {
    double result = 0.0;
    for (long i = 1; i < 100000; i++) {
        result += sqrt((double)i);
    }
    printf("Result of heavy_operation_1: %f\n", result);
}

// Simulates a different CPU-bound heavy operation by calculating factorials
void heavy_operation_2() {
    unsigned long long result = 1;
    for (int i = 1; i < 20; i++) {
        result = 1;
        for (int j = 1; j <= i * 10000; j++) {
            result *= j;
            result %= 100000; // Prevent overflow by keeping the result manageable
        }
    }
    printf("Result of heavy_operation_2: %llu\n", result);
}

// Simulates a mixed heavy operation (CPU + IO-bound) by performing some calculations and sleeping
void heavy_operation_3() {
    double result = 1.0;
    for (long i = 1; i < 50000; i++) {
        result *= log((double)i);
        if (i % 10000 == 0) {
            printf("Heavy operation 3, part %ld: sleeping for 1 second...\n", i / 1000000);
            sleep(1); // Simulate some IO-bound activity
        }
    }
    printf("Result of heavy_operation_3: %f\n", result);
}

int main() {
    // Initial heavy operation (this part will be ignored in profiling)
    heavy_operation_1();

    // Stop profiling (ignore the above operation in gprof output)
    gprof_stop(NULL, false);

    // Start profiling again
    gprof_start();

    // Operations to be profiled
    heavy_operation_2();
    heavy_operation_3();

    // Stop profiling and save the output to a custom file
    gprof_stop("gmon_custom.out", true);

    return 0;
}