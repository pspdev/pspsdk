/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Regression tests for clearing offscreen draw buffers larger than the LCD.
 * The first two results are shown as textures on the LCD.
 * Detailed results are written to ms0:/pspsdk-gu-clear-results.txt.
 */

#include <pspuser.h>
#include <pspge.h>
#include <pspdebug.h>
#include <pspdisplay.h>
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
#define PREVIEW_SIZE 208
#define PREVIEW_Y 32
#define PREVIEW_LEFT_X 16
#define PREVIEW_RIGHT_X 256

/* Three non-overlapping VRAM buffers; the target also fits in 8888 format. */
#define DISPLAY_OFFSET 0x00000
#define DRAW_OFFSET 0x44000
#define TARGET_OFFSET 0x88000
#define RESULT_OFFSET 0x1f0000
#define GE_CLEAR_MODE_COMMAND 0xd3

/* Color values in the PSP's RGB565 and RGBA8888 memory layouts. */
#define TARGET_BLUE_565 0xf800
#define SCREEN_GREEN_565 0x07e0
#define CLEAR_RED_565 0x001f
#define CLEAR_GREEN_565 0x07e0
#define SCREEN_YELLOW_565 0x07ff
#define TARGET_BLUE_8888 0xffff0000
#define CLEAR_RED_8888 0x660000ff

enum {
    CLEAR_NORMAL,
    CLEAR_FAST,
    CLEAR_SPRITE,
    CLEAR_MODE_SPRITE,
    CLEAR_TWO_REGIONS,
    CLEAR_TWO_REGIONS_FAST
};

typedef struct {
    const char *name;
    int method;
    int x, y, w, h;
    int scissor_enabled;
    int use_draw_buffer;
    int format;
    int same_list_restore;
} ClearTest;

typedef struct {
    unsigned int target_errors;
    unsigned int screen_errors;
    unsigned int display_errors;
    int first_x, first_y, first_area;
    unsigned int first_expected, first_actual;
} Result;

typedef struct {
    unsigned int color;
    unsigned short x, y, z, pad;
} ClearVertex;

static unsigned int __attribute__((aligned(16))) display_list[1024];
static char result_log[8192];
static unsigned int result_log_size;
static unsigned int failures;

enum {
    PREVIEW_NORMAL,
    PREVIEW_FAST,
    PREVIEW_COUNT
};

/* Preserve the actual full-size RGB565 results before the next test resets VRAM. */
static uint16_t __attribute__((aligned(16))) previews[PREVIEW_COUNT][TARGET_HEIGHT * STRIDE];
static unsigned int preview_errors[PREVIEW_COUNT];

static const ClearTest tests[] = {
    /* Existing baseline cases. */
    [PREVIEW_NORMAL] = {"normal full 565 list",        CLEAR_NORMAL,           0,   0, 512, 512, 1, 0, GU_PSM_5650, 1},
    [PREVIEW_FAST] = {"fast full 565 list",          CLEAR_FAST,             0,   0, 512, 512, 1, 0, GU_PSM_5650, 1},
    {"plain sprite full",          CLEAR_SPRITE,           0,   0, 512, 512, 1, 0, GU_PSM_5650, 1},
    {"clear sprite full",          CLEAR_MODE_SPRITE,      0,   0, 512, 512, 1, 0, GU_PSM_5650, 1},
    {"clear sprite DrawBuffer",    CLEAR_MODE_SPRITE,      0,   0, 512, 512, 1, 1, GU_PSM_5650, 1},
    {"clear sprite no scissor",    CLEAR_MODE_SPRITE,      0,   0, 512, 512, 0, 0, GU_PSM_5650, 1},
    {"normal no scissor",          CLEAR_NORMAL,           0,   0, 512, 512, 0, 0, GU_PSM_5650, 1},
    {"normal no scissor offset",   CLEAR_NORMAL,          64,  32, 256, 128, 0, 0, GU_PSM_5650, 0},
    {"fast no scissor offset",     CLEAR_FAST,            64,  32, 256, 128, 0, 0, GU_PSM_5650, 0},

    /* Check nonzero origins, exclusive ends, and pixels outside the region. */
    {"normal partial 64,32",       CLEAR_NORMAL,          64,  32, 256, 128, 1, 0, GU_PSM_5650, 0},
    {"fast partial 64,32",         CLEAR_FAST,            64,  32, 256, 128, 1, 0, GU_PSM_5650, 0},
    {"normal lower right",        CLEAR_NORMAL,         400, 240, 112, 272, 1, 0, GU_PSM_5650, 0},
    {"fast lower right",          CLEAR_FAST,           400, 240, 112, 272, 1, 0, GU_PSM_5650, 0},
    {"normal one pixel",          CLEAR_NORMAL,         480, 272,   1,   1, 1, 0, GU_PSM_5650, 0},
    {"fast one pixel",            CLEAR_FAST,           480, 272,   1,   1, 1, 0, GU_PSM_5650, 0},
    {"normal odd boundary",       CLEAR_NORMAL,         479, 271,  33,   2, 1, 0, GU_PSM_5650, 0},
    {"fast odd boundary",         CLEAR_FAST,           479, 271,  33,   2, 1, 0, GU_PSM_5650, 0},
    {"normal partial DrawBuffer", CLEAR_NORMAL,          64,  32, 256, 128, 1, 1, GU_PSM_5650, 0},
    {"fast partial DrawBuffer",   CLEAR_FAST,            64,  32, 256, 128, 1, 1, GU_PSM_5650, 0},

    /* A second scissor + clear in the same list must not reuse old bounds. */
    {"two regions normal",        CLEAR_TWO_REGIONS,      0,   0, 512, 512, 1, 0, GU_PSM_5650, 0},
    {"two regions fast",          CLEAR_TWO_REGIONS_FAST, 0,   0, 512, 512, 1, 0, GU_PSM_5650, 0},

    /* Color and stencil clear with a different pixel size and block width. */
    {"normal full 8888",          CLEAR_NORMAL,           0,   0, 512, 512, 1, 1, GU_PSM_8888, 0},
    {"fast full 8888",            CLEAR_FAST,             0,   0, 512, 512, 1, 1, GU_PSM_8888, 0},
    {"normal partial 8888",       CLEAR_NORMAL,          64,  32, 256, 128, 1, 1, GU_PSM_8888, 0},
    {"fast partial 8888",         CLEAR_FAST,            64,  32, 256, 128, 1, 1, GU_PSM_8888, 0},

    /* Switching back to a 16-bit target must not retain 32-bit clear state. */
    {"normal 565 after 8888",     CLEAR_NORMAL,         400, 240, 112, 272, 1, 0, GU_PSM_5650, 0}
};

static volatile uint16_t *edram16(void)
{
    return (volatile uint16_t *)((uintptr_t)sceGeEdramGetAddr() | 0x40000000u);
}

static volatile uint32_t *edram32(void)
{
    return (volatile uint32_t *)edram16();
}

static void fill_buffers(int format)
{
    unsigned int i;

    if (format == GU_PSM_8888) {
        volatile uint32_t *target = (volatile uint32_t *)((uintptr_t)edram32() + TARGET_OFFSET);
        for (i = 0; i < STRIDE * TARGET_HEIGHT; ++i)
            target[i] = TARGET_BLUE_8888;
    } else {
        volatile uint16_t *target = (volatile uint16_t *)((uintptr_t)edram16() + TARGET_OFFSET);
        for (i = 0; i < STRIDE * TARGET_HEIGHT; ++i)
            target[i] = TARGET_BLUE_565;
    }

    for (i = 0; i < STRIDE * SCREEN_HEIGHT; ++i) {
        edram16()[DRAW_OFFSET / 2 + i] = SCREEN_GREEN_565;
        edram16()[DISPLAY_OFFSET / 2 + i] = SCREEN_GREEN_565;
    }
}

static unsigned int target_pixel(int format, int x, int y)
{
    unsigned int index = y * STRIDE + x;

    if (format == GU_PSM_8888)
        return edram32()[TARGET_OFFSET / 4 + index];
    return edram16()[TARGET_OFFSET / 2 + index];
}

static void check_pixel(Result *r, int area, int x, int y,
                        unsigned int expected, unsigned int actual)
{
    if (expected == actual)
        return;

    if (area == 0)
        ++r->target_errors;
    else if (area == 1)
        ++r->screen_errors;
    else
        ++r->display_errors;

    if (r->first_area == -1) {
        r->first_area = area;
        r->first_x = x;
        r->first_y = y;
        r->first_expected = expected;
        r->first_actual = actual;
    }
}

static int inside_rect(int x, int y, int rx, int ry, int rw, int rh)
{
    return x >= rx && x < rx + rw && y >= ry && y < ry + rh;
}

static void check_target(const ClearTest *t, Result *r)
{
    int x, y;

    for (y = 0; y < TARGET_HEIGHT; ++y) {
        for (x = 0; x < TARGET_WIDTH; ++x) {
            unsigned int expected;
            int inside;

            if (t->method == CLEAR_TWO_REGIONS || t->method == CLEAR_TWO_REGIONS_FAST) {
                if (inside_rect(x, y, 0, 0, 64, 64))
                    expected = CLEAR_RED_565;
                else if (inside_rect(x, y, 448, 448, 64, 64))
                    expected = CLEAR_GREEN_565;
                else
                    expected = TARGET_BLUE_565;
            } else {
                if (t->scissor_enabled)
                    inside = inside_rect(x, y, t->x, t->y, t->w, t->h);
                else
                    inside = inside_rect(x, y, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

                if (t->format == GU_PSM_8888)
                    expected = inside ? CLEAR_RED_8888 : TARGET_BLUE_8888;
                else
                    expected = inside ? CLEAR_RED_565 : TARGET_BLUE_565;
            }

            check_pixel(r, 0, x, y, expected, target_pixel(t->format, x, y));
        }
    }
}

static void check_buffers(Result *r, int restored)
{
    int x, y;

    for (y = 0; y < SCREEN_HEIGHT; ++y) {
        for (x = 0; x < STRIDE; ++x) {
            unsigned int expected = restored && x < SCREEN_WIDTH
                ? SCREEN_YELLOW_565 : SCREEN_GREEN_565;
            check_pixel(r, 1, x, y, expected, edram16()[DRAW_OFFSET / 2 + y * STRIDE + x]);
            check_pixel(r, 2, x, y, SCREEN_GREEN_565,
                        edram16()[DISPLAY_OFFSET / 2 + y * STRIDE + x]);
        }
    }
}

static void draw_sprite(int clear_mode)
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

static void perform_clear(int method, int flags)
{
    switch (method) {
    case CLEAR_NORMAL:
    case CLEAR_TWO_REGIONS:
        sceGuClear(flags);
        break;
    case CLEAR_FAST:
    case CLEAR_TWO_REGIONS_FAST:
        sceGuClear(flags | GU_FAST_CLEAR_BIT);
        break;
    case CLEAR_SPRITE:
        draw_sprite(0);
        break;
    case CLEAR_MODE_SPRITE:
        draw_sprite(1);
        break;
    }
}

static void restore_screen(void)
{
    /* Use the full API to restore stored pixel-format and buffer metadata. */
    sceGuDrawBuffer(GU_PSM_5650, (void *)DRAW_OFFSET, STRIDE);
    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuClearColor(GU_RGBA(255, 255, 0, 255));
    sceGuClear(GU_COLOR_BUFFER_BIT);
}

static void report(const ClearTest *t, const Result *r)
{
    char line[320];
    int ok = !r->target_errors && !r->screen_errors && !r->display_errors;
    int len;

    if (!ok)
        ++failures;

    if (ok) {
        len = snprintf(line, sizeof(line), "%-28s PASS\n", t->name);
    } else {
        len = snprintf(line, sizeof(line),
            "%-28s FAIL RT=%u SCREEN=%u DISPLAY=%u first=%d:(%d,%d) expected=%08x actual=%08x\n",
            t->name, r->target_errors, r->screen_errors, r->display_errors,
            r->first_area, r->first_x, r->first_y, r->first_expected, r->first_actual);
    }

    if (len > 0 && len < (int)sizeof(line) &&
        result_log_size + (unsigned int)len < sizeof(result_log)) {
        memcpy(result_log + result_log_size, line, len);
        result_log_size += len;
    }
}

static Result run_test(const ClearTest *t)
{
    Result r = {0};
    int flags = GU_COLOR_BUFFER_BIT;

    r.first_area = -1;
    r.first_x = -1;
    r.first_y = -1;

    fill_buffers(t->format);

    sceGuStart(GU_DIRECT, display_list);
    if (t->use_draw_buffer)
        sceGuDrawBuffer(t->format, (void *)TARGET_OFFSET, STRIDE);
    else
        sceGuDrawBufferList(t->format, (void *)TARGET_OFFSET, STRIDE);

    sceGuScissor(t->x, t->y, t->w, t->h);
    sceGuEnable(GU_SCISSOR_TEST);
    if (!t->scissor_enabled)
        sceGuDisable(GU_SCISSOR_TEST);

    sceGuDisable(GU_TEXTURE_2D);
    sceGuDisable(GU_BLEND);
    sceGuDisable(GU_DEPTH_TEST);
    sceGuClearColor(GU_RGBA(255, 0, 0, 255));

    if (t->format == GU_PSM_8888) {
        sceGuClearStencil(0x66);
        flags |= GU_STENCIL_BUFFER_BIT;
    }

    if (t->method == CLEAR_TWO_REGIONS || t->method == CLEAR_TWO_REGIONS_FAST) {
        sceGuScissor(0, 0, 64, 64);
        perform_clear(t->method, flags);
        sceGuScissor(448, 448, 64, 64);
        sceGuClearColor(GU_RGBA(0, 255, 0, 255));
        perform_clear(t->method, flags);
    } else {
        perform_clear(t->method, flags);
    }

    if (t->same_list_restore)
        restore_screen();

    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

    check_target(t, &r);
    if (!t->same_list_restore) {
        /* Catch any offscreen clear that accidentally wrote to the LCD buffers. */
        check_buffers(&r, 0);
        sceGuStart(GU_DIRECT, display_list);
        restore_screen();
        sceGuFinish();
        sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);
    }
    check_buffers(&r, 1);
    report(t, &r);
    return r;
}

static void capture_preview(unsigned int index, const Result *r)
{
    unsigned int i;
    const volatile uint16_t *target = edram16() + TARGET_OFFSET / 2;

    for (i = 0; i < TARGET_HEIGHT * STRIDE; ++i)
        previews[index][i] = target[i];

    sceKernelDcacheWritebackRange(previews[index], sizeof(previews[index]));
    preview_errors[index] = r->target_errors;
}

static void draw_preview(unsigned int index, int x)
{
    struct Vertex {
        unsigned short u, v;
        short x, y, z;
    };
    struct Vertex *verts = sceGuGetMemory(2 * sizeof(*verts));

    if (!verts)
        return;

    verts[0] = (struct Vertex){0, 0, x, PREVIEW_Y, 0};
    verts[1] = (struct Vertex){TARGET_WIDTH, TARGET_HEIGHT,
                              x + PREVIEW_SIZE, PREVIEW_Y + PREVIEW_SIZE, 0};

    sceGuTexImage(0, TARGET_WIDTH, TARGET_HEIGHT, STRIDE, previews[index]);
    sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_VERTEX_16BIT | GU_TRANSFORM_2D,
                   2, NULL, verts);
}

static void show_results(void)
{
    /* The regression checks are complete; only now reuse the LCD framebuffer. */
    pspDebugScreenSetBackColor(0xff202020);
    pspDebugScreenInitEx(NULL, PSP_DISPLAY_PIXEL_FORMAT_565, 0);

    sceGuStart(GU_DIRECT, display_list);
    sceGuDrawBuffer(GU_PSM_5650, (void *)DISPLAY_OFFSET, STRIDE);
    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuTexMode(GU_PSM_5650, 0, 0, GU_FALSE);
    sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
    sceGuTexFilter(GU_NEAREST, GU_NEAREST);
    sceGuTexWrap(GU_CLAMP, GU_CLAMP);
    sceGuTexScale(1.0f, 1.0f);
    sceGuTexOffset(0.0f, 0.0f);
    draw_preview(PREVIEW_NORMAL, PREVIEW_LEFT_X);
    draw_preview(PREVIEW_FAST, PREVIEW_RIGHT_X);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);

    pspDebugScreenSetXY(2, 0);
    pspDebugScreenPrintf("512x512 offscreen clear (actual render targets)");
    pspDebugScreenSetXY(2, 2);
    pspDebugScreenPrintf("Normal sceGuClear");
    pspDebugScreenSetXY(36, 2);
    pspDebugScreenPrintf("GU_FAST_CLEAR_BIT");
    pspDebugScreenSetXY(2, 3);
    pspDebugScreenPrintf("Blue = uncleared; red = cleared. Both should be solid red.");
    pspDebugScreenSetXY(2, 30);
    pspDebugScreenPrintf("%s: %u wrong pixels", preview_errors[PREVIEW_NORMAL] ? "FAIL" : "PASS",
                         preview_errors[PREVIEW_NORMAL]);
    pspDebugScreenSetXY(36, 30);
    pspDebugScreenPrintf("%s: %u wrong pixels", preview_errors[PREVIEW_FAST] ? "FAIL" : "PASS",
                         preview_errors[PREVIEW_FAST]);
    pspDebugScreenSetXY(2, 32);
    pspDebugScreenPrintf("%s: %u/%u regression tests passed", failures ? "FAIL" : "PASS",
                         (unsigned int)(sizeof(tests) / sizeof(tests[0])) - failures,
                         (unsigned int)(sizeof(tests) / sizeof(tests[0])));
    pspDebugScreenSetXY(2, 33);
    pspDebugScreenPrintf("Log: ms0:/pspsdk-gu-clear-results.txt");

    sceGuDisplay(GU_TRUE);
}

int main(void)
{
    unsigned int i;
    SceUID log_fd;

    sceGuInit();
    edram16()[RESULT_OFFSET / 2] = 0;

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

    for (i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i) {
        Result result = run_test(&tests[i]);
        if (i < PREVIEW_COUNT)
            capture_preview(i, &result);
    }

    edram16()[RESULT_OFFSET / 2] = failures ? 0xdead : 0xbeef;

    result_log_size += snprintf(result_log + result_log_size,
        sizeof(result_log) - result_log_size,
        "Result: %s (%u/%u passed)\n",
        failures ? "FAIL" : "PASS",
        (unsigned int)(sizeof(tests) / sizeof(tests[0])) - failures,
        (unsigned int)(sizeof(tests) / sizeof(tests[0])));

    log_fd = sceIoOpen("ms0:/pspsdk-gu-clear-results.txt",
        PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0666);
    if (log_fd >= 0) {
        sceIoWrite(log_fd, result_log, result_log_size);
        sceIoClose(log_fd);
    }

    show_results();

    /* Do not exit PSPLink; keep the results visible and the report available. */
    sceKernelSleepThread();
    return 0;
}
