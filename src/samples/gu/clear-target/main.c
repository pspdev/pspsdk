/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Regression test for clearing an offscreen draw buffer larger than the LCD.
 * Results are written to ms0:/pspsdk-gu-clear-results.txt.
 */

#include <pspuser.h>
#include <pspge.h>
#include <pspgu.h>
#include <pspiofilemgr.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>

PSP_MODULE_INFO("GU Offscreen Clear Test", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define STRIDE 512
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define TARGET_WIDTH 512
#define TARGET_HEIGHT 512

/* 512 * 272 * 2 = 0x44000 bytes; each GE buffer is 8 KiB aligned. */
#define DISPLAY_OFFSET 0x00000
#define DRAW_OFFSET 0x44000
#define TARGET_OFFSET 0x88000
#define RESULT_OFFSET 0x1f0000
#define GE_CLEAR_MODE_COMMAND 0xd3

/* RGB565 values, in the PSP's R:G:B bit order. */
#define INITIAL_TARGET 0xf800 /* blue */
#define INITIAL_SCREEN 0x07e0 /* green */
#define CLEARED_COLOR 0x001f /* red */
#define SCREEN_COLOR 0x07ff /* yellow */

static unsigned int __attribute__((aligned(16))) display_list[1024];
static char result_log[1024];
static unsigned int result_log_size;
static unsigned int result_count;
static unsigned int failures;

typedef struct
{
    unsigned int color;
    unsigned short x, y, z, pad;
} ClearVertex;

static volatile uint16_t *edram(void)
{
    return (volatile uint16_t *)((uintptr_t)sceGeEdramGetAddr() | 0x40000000u);
}

static void fill_pixels(unsigned int offset, int height, uint16_t value)
{
    volatile uint16_t *pixels = (volatile uint16_t *)((uintptr_t)edram() + offset);
    int i;

    for (i = 0; i < STRIDE * height; ++i)
        pixels[i] = value;
}

static uint16_t pixel(unsigned int offset, int x, int y)
{
    return edram()[(offset / 2) + y * STRIDE + x];
}

static void report(const char *name, int full_clear_expected)
{
    char line[256];
    uint16_t values[] = {
        pixel(TARGET_OFFSET, 1, 1),
        pixel(TARGET_OFFSET, 479, 271),
        pixel(TARGET_OFFSET, 480, 271),
        pixel(TARGET_OFFSET, 479, 272),
        pixel(TARGET_OFFSET, 480, 272),
        pixel(TARGET_OFFSET, 511, 511),
        pixel(DRAW_OFFSET, 1, 1),
        pixel(DISPLAY_OFFSET, 1, 1)
    };
    unsigned int i;
    int pass = values[6] == SCREEN_COLOR && values[7] == INITIAL_SCREEN;

    for (i = 0; i < 6; ++i) {
        uint16_t expected = (full_clear_expected || i < 2) ? CLEARED_COLOR : INITIAL_TARGET;
        if (values[i] != expected)
            pass = 0;
    }
    if (!pass)
        ++failures;

    int count = snprintf(line, sizeof(line),
        "%-24s %s RT=(%04x %04x %04x %04x %04x %04x) "
        "SCREEN=%04x DISPLAY=%04x\n",
        name, pass ? "PASS" : "FAIL", values[0], values[1], values[2], values[3],
        values[4], values[5], values[6], values[7]);

    for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
        edram()[RESULT_OFFSET / 2 + result_count * 8 + i] = values[i];
    ++result_count;

    if (count > 0 && count < (int)sizeof(line) &&
        result_log_size + (unsigned int)count <= sizeof(result_log)) {
        memcpy(result_log + result_log_size, line, count);
        result_log_size += count;
    }
}

static void draw_clear_sprite(int clear_mode)
{
    ClearVertex *verts = (ClearVertex *)sceGuGetMemory(2 * sizeof(*verts));

    if (!verts)
        return;

    memset(verts, 0, 2 * sizeof(*verts));
    verts[0].color = GU_RGBA(255, 0, 0, 255);
    verts[1].color = verts[0].color;
    verts[1].x = TARGET_WIDTH;
    verts[1].y = TARGET_HEIGHT;

    if (clear_mode)
        sceGuSendCommandi(GE_CLEAR_MODE_COMMAND, (GU_COLOR_BUFFER_BIT << 8) | 1);

    sceGuDrawArray(GU_SPRITES,
        GU_COLOR_8888 | GU_VERTEX_16BIT | GU_TRANSFORM_2D,
        2, NULL, verts);

    if (clear_mode)
        sceGuSendCommandi(GE_CLEAR_MODE_COMMAND, 0);
}

static void run_test(const char *name, int mode, int full_api, int disable_scissor)
{
    fill_pixels(TARGET_OFFSET, TARGET_HEIGHT, INITIAL_TARGET);
    fill_pixels(DRAW_OFFSET, SCREEN_HEIGHT, INITIAL_SCREEN);
    fill_pixels(DISPLAY_OFFSET, SCREEN_HEIGHT, INITIAL_SCREEN);

    sceGuStart(GU_DIRECT, display_list);
    if (full_api)
        sceGuDrawBuffer(GU_PSM_5650, (void *)TARGET_OFFSET, STRIDE);
    else
        sceGuDrawBufferList(GU_PSM_5650, (void *)TARGET_OFFSET, STRIDE);

    sceGuScissor(0, 0, TARGET_WIDTH, TARGET_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    if (disable_scissor)
        sceGuDisable(GU_SCISSOR_TEST);

    sceGuDisable(GU_TEXTURE_2D);
    sceGuDisable(GU_BLEND);
    sceGuClearColor(GU_RGBA(255, 0, 0, 255));

    switch (mode) {
    case 0: sceGuClear(GU_COLOR_BUFFER_BIT); break;
    case 1: sceGuClear(GU_COLOR_BUFFER_BIT | GU_FAST_CLEAR_BIT); break;
    case 2: draw_clear_sprite(0); break;
    case 3: draw_clear_sprite(1); break;
    }

    /* Restore the screen buffer and clear it with a different color. */
    if (full_api)
        sceGuDrawBuffer(GU_PSM_5650, (void *)DRAW_OFFSET, STRIDE);
    else
        sceGuDrawBufferList(GU_PSM_5650, (void *)DRAW_OFFSET, STRIDE);

    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuClearColor(GU_RGBA(255, 255, 0, 255));
    sceGuClear(GU_COLOR_BUFFER_BIT);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

    report(name, !disable_scissor);
}

int main(void)
{
    SceUID log_fd;

    sceGuInit();

    sceGuStart(GU_DIRECT, display_list);
    sceGuDrawBuffer(GU_PSM_5650, (void *)DRAW_OFFSET, STRIDE);
    sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, (void *)DISPLAY_OFFSET, STRIDE);
    sceGuOffset(2048 - SCREEN_WIDTH / 2, 2048 - SCREEN_HEIGHT / 2);
    sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuDisable(GU_DEPTH_TEST);
    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

    run_test("sceGuClear + scissor512", 0, 0, 0);
    run_test("sceGuClear FAST + sc512", 1, 0, 0);
    run_test("plain sprite + sc512", 2, 0, 0);
    run_test("clear-mode sprite + sc512", 3, 0, 0);
    run_test("clear-mode + DrawBuffer", 3, 1, 0);
    run_test("clear-mode scissor OFF", 3, 0, 1);
    run_test("sceGuClear scissor OFF", 0, 0, 1);

    edram()[RESULT_OFFSET / 2 + result_count * 8] = failures ? 0xdead : 0xbeef;

    result_log_size += snprintf(result_log + result_log_size,
        sizeof(result_log) - result_log_size,
        "Result: %s (%u failed)\n", failures ? "FAIL" : "PASS", failures);

    log_fd = sceIoOpen("ms0:/pspsdk-gu-clear-results.txt",
        PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0666);
    if (log_fd >= 0) {
        sceIoWrite(log_fd, result_log, result_log_size);
        sceIoClose(log_fd);
    }

    /* Stay under PSPLink so the host can inspect the log and reset safely. */
    sceKernelSleepThread();
    return 0;
}
