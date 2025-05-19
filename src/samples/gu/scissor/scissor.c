/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2024 PSP Software Development Kit Contributors
 *
 * Scissor sample - Demonstrates scissor functionality with a scanning effect
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "../common/callbacks.h"

PSP_MODULE_INFO("Scissor Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define SCISSOR_SIZE (68)
#define MAX_X (412)  // Maximum x coordinate for our pattern

// Color definitions (RGBA format)
#define COLOR_RED    0xFF0000FF
#define COLOR_BLUE   0xFFFF0000

// Structure to hold scissor movement state
typedef struct {
    int x, y;           // Current position
    int target_x;       // Target x position
    int target_y;       // Target y position
    int reverse;        // Whether we're in reverse mode
} ScissorState;

// Initialize scissor state
static void init_scissor_state(ScissorState* state) {
    state->x = 0;
    state->y = 0;
    state->target_x = MAX_X;
    state->target_y = 0;
    state->reverse = 0;
}

// Update scissor position for the specific pattern
static void update_scissor(ScissorState* state) {
    // Move one pixel at a time towards target
    if (state->x < state->target_x) {
        state->x++;
    } else if (state->x > state->target_x) {
        state->x--;
    }
    
    if (state->y < state->target_y) {
        state->y++;
    } else if (state->y > state->target_y) {
        state->y--;
    }

    // If we've reached the target, set the next target
    if (state->x == state->target_x && state->y == state->target_y) {
        if (!state->reverse) {
            // Forward pattern
            if (state->x == 0 && state->y == 0) {
                state->target_x = MAX_X;
                state->target_y = 0;
            } else if (state->x == MAX_X && state->y == 0) {
                state->target_x = MAX_X;
                state->target_y = SCISSOR_SIZE;
            } else if (state->x == MAX_X && state->y == SCISSOR_SIZE) {
                state->target_x = 0;
                state->target_y = SCISSOR_SIZE;
            } else if (state->x == 0 && state->y == SCISSOR_SIZE) {
                state->target_x = 0;
                state->target_y = SCISSOR_SIZE * 2;
            } else if (state->x == 0 && state->y == SCISSOR_SIZE * 2) {
                state->target_x = MAX_X;
                state->target_y = SCISSOR_SIZE * 2;
            } else if (state->x == MAX_X && state->y == SCISSOR_SIZE * 2) {
                state->target_x = MAX_X;
                state->target_y = SCISSOR_SIZE * 3;
            } else if (state->x == MAX_X && state->y == SCISSOR_SIZE * 3) {
                state->target_x = 0;
                state->target_y = SCISSOR_SIZE * 3;
            } else if (state->x == 0 && state->y == SCISSOR_SIZE * 3) {
                // Start reverse pattern
                state->reverse = 1;
                state->target_x = MAX_X;
                state->target_y = SCISSOR_SIZE * 3;
            }
        } else {
            // Reverse pattern
            if (state->x == MAX_X && state->y == SCISSOR_SIZE * 3) {
                state->target_x = MAX_X;
                state->target_y = SCISSOR_SIZE * 2;
            } else if (state->x == MAX_X && state->y == SCISSOR_SIZE * 2) {
                state->target_x = 0;
                state->target_y = SCISSOR_SIZE * 2;
            } else if (state->x == 0 && state->y == SCISSOR_SIZE * 2) {
                state->target_x = 0;
                state->target_y = SCISSOR_SIZE;
            } else if (state->x == 0 && state->y == SCISSOR_SIZE) {
                state->target_x = MAX_X;
                state->target_y = SCISSOR_SIZE;
            } else if (state->x == MAX_X && state->y == SCISSOR_SIZE) {
                state->target_x = MAX_X;
                state->target_y = 0;
            } else if (state->x == MAX_X && state->y == 0) {
                state->target_x = 0;
                state->target_y = 0;
            } else if (state->x == 0 && state->y == 0) {
                // Start over
                state->reverse = 0;
                state->target_x = MAX_X;
                state->target_y = 0;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    pspDebugScreenInit();
    setupCallbacks();

    // Setup GU
    void* fbp0 = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, GU_PSM_8888);
    void* fbp1 = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, GU_PSM_8888);

    sceGuInit();
    sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(GU_PSM_8888, fbp0, BUF_WIDTH);
    sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, fbp1, BUF_WIDTH);
    sceGuOffset(2048 - (SCR_WIDTH/2), 2048 - (SCR_HEIGHT/2));
    sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
    sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

    // Initialize scissor state
    ScissorState scissor;
    init_scissor_state(&scissor);

    // Main loop
    while (running())
    {
        sceGuStart(GU_DIRECT, list);

        // Clear screen to red
        sceGuClearColor(COLOR_RED);
        sceGuClear(GU_COLOR_BUFFER_BIT);

        // Update scissor position
        update_scissor(&scissor);

        // Enable scissor test and set new scissor area
        sceGuEnable(GU_SCISSOR_TEST);
        sceGuScissor(scissor.x, scissor.y, SCISSOR_SIZE, SCISSOR_SIZE);
        // sceGuScissor(0, 0, SCISSOR_SIZE, SCISSOR_SIZE);

        // Draw blue rectangle in scissor area
        sceGuClearColor(COLOR_BLUE);
        sceGuClear(GU_COLOR_BUFFER_BIT);

        // Disable scissor test for next frame
        sceGuDisable(GU_SCISSOR_TEST);

        sceGuFinish();
        sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

        pspDebugScreenSetOffset((int)fbp0);
		pspDebugScreenSetXY(0,0);
		pspDebugScreenPrintf("Scissor: (%d, %d), (%d, %d)", 
            scissor.x, scissor.y, 
            scissor.x + SCISSOR_SIZE, scissor.y + SCISSOR_SIZE);

		sceDisplayWaitVblankStart();
		fbp0 = sceGuSwapBuffers();
    }

    sceGuTerm();
    return 0;
} 