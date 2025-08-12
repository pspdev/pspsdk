/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * PixelMask sample - Demonstrates sceGuPixelMask channel write-masking
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <pspctrl.h>
#include <pspgu.h>
#include <psprtc.h>

#include "../common/callbacks.h"

PSP_MODULE_INFO("PixelMask Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[1024];

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

#define COLOR_BLACK 0x00000000

typedef struct PixelMaskMode
{
    const char *description;
    unsigned int mask;
} PixelMaskMode;

#define TEXTURE_FORMAT GU_PSM_8888
// In mask 0xAABBGGRR: 1-bits prevent writes to that bit, 0-bits allow writes.
// Keep AA=0x00 so alpha writes remain enabled for all modes in this sample.
static const PixelMaskMode modes[] = {
    {"Mask 0x00000000: All channels writable", 0x00000000},
    {"Mask 0x0000FFFF: Only Blue (+Alpha) writable", 0x0000FFFF},  // R=0xFF, G=0xFF, B=0x00, A=0x00
    {"Mask 0x00FF00FF: Only Green (+Alpha) writable", 0x00FF00FF}, // R=0xFF, G=0x00, B=0xFF, A=0x00
    {"Mask 0x00FFFF00: Only Red (+Alpha) writable", 0x00FFFF00},   // R=0x00, G=0xFF, B=0xFF, A=0x00
};

// GU_PSM_8888, 8x8. Where the 2 first columns are red and the 2 last columns are green.
static uint32_t __attribute__((aligned(16))) pixels[64] = {
    0xFF0000FF, 0xFF0000FF, 0xFF00FF00, 0xFF00FF00, 0xFFFF0000, 0xFFFF0000, 0xFFFFFFFF, 0xFFFFFFF,
    0xFF0000FF, 0xFF0000FF, 0xFF00FF00, 0xFF00FF00, 0xFFFF0000, 0xFFFF0000, 0xFFFFFFFF, 0xFFFFFFF,
    0xFF0000FF, 0xFF0000FF, 0xFF00FF00, 0xFF00FF00, 0xFFFF0000, 0xFFFF0000, 0xFFFFFFFF, 0xFFFFFFF,
    0xFF0000FF, 0xFF0000FF, 0xFF00FF00, 0xFF00FF00, 0xFFFF0000, 0xFFFF0000, 0xFFFFFFFF, 0xFFFFFFF,
    0xFF0000FF, 0xFF0000FF, 0xFF00FF00, 0xFF00FF00, 0xFFFF0000, 0xFFFF0000, 0xFFFFFFFF, 0xFFFFFFF,
    0xFF0000FF, 0xFF0000FF, 0xFF00FF00, 0xFF00FF00, 0xFFFF0000, 0xFFFF0000, 0xFFFFFFFF, 0xFFFFFFF,
    0xFF0000FF, 0xFF0000FF, 0xFF00FF00, 0xFF00FF00, 0xFFFF0000, 0xFFFF0000, 0xFFFFFFFF, 0xFFFFFFF,
    0xFF0000FF, 0xFF0000FF, 0xFF00FF00, 0xFF00FF00, 0xFFFF0000, 0xFFFF0000, 0xFFFFFFFF, 0xFFFFFFF,
};

struct Vertex
{
    short u, v;
    short x, y, z;
};

void blit()
{
    struct Vertex *vertices = (struct Vertex *)sceGuGetMemory(2 * sizeof(struct Vertex));

    vertices[0].u = 0;
    vertices[0].v = 0;
    vertices[0].x = 0;
    vertices[0].y = 0;
    vertices[0].z = 0;

    vertices[1].u = 8;
    vertices[1].v = 8;
    vertices[1].x = SCR_WIDTH;
    vertices[1].y = SCR_HEIGHT;
    vertices[1].z = 0;

    sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_16BIT | GU_TRANSFORM_2D, 2, 0, vertices);
}

int main(int argc, char *argv[])
{
    int mode_index = 0;
    int frame_counter = 0;
    int drawFormat = GU_PSM_5650;

    pspDebugScreenInit();
    setupCallbacks();

    // Setup GU

    void *fbp0 = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, drawFormat);
    void *fbp1 = guGetStaticVramBuffer(BUF_WIDTH, SCR_HEIGHT, drawFormat);

    sceGuInit();

    sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(drawFormat, fbp0, BUF_WIDTH);
    sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, fbp1, BUF_WIDTH);
    sceGuOffset(2048 - (SCR_WIDTH / 2), 2048 - (SCR_HEIGHT / 2));
    sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
    sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

    sceGuTexMode(TEXTURE_FORMAT, 0, 0, 0);
    sceGuTexImage(0, 8, 8, 8, pixels);
    sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA); // don't get influenced by any vertex colors
    sceGuTexFilter(GU_NEAREST, GU_NEAREST);    // point-filtered sampling

    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

    sceKernelDcacheWritebackAll();

    pspDebugScreenInitEx(fbp0, drawFormat, 1);

    while (running())
    {
        sceGuStart(GU_DIRECT, list);

        sceGuClearColor(COLOR_BLACK);
        sceGuClear(GU_COLOR_BUFFER_BIT);

        // Apply current pixel mask and draw color bars
        sceGuPixelMask(modes[mode_index].mask);
        blit();
        sceGuPixelMask(0);

        sceGuFinish();
        sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

        // HUD text
        pspDebugScreenSetOffset((int)fbp0);
        pspDebugScreenSetXY(0, 0);
        pspDebugScreenPrintf("sceGuPixelMask demo\n");
        pspDebugScreenPrintf("%s\n", modes[mode_index].description);

        sceDisplayWaitVblankStart();
        fbp0 = sceGuSwapBuffers();

        // Rotate mode every ~2 seconds (assuming ~60 FPS)
        frame_counter++;
        if (frame_counter >= 120)
        {
            frame_counter = 0;
            mode_index = (mode_index + 1) % (sizeof(modes) / sizeof(modes[0]));
        }
    }

    sceGuTerm();

    sceKernelExitGame();
    return 0;
}
