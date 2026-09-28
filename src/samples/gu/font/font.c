/*
* PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2026 Zuzanna Petryk (zzanp@disroot.org)
 *
 * Simple example for drawing coloured text with GU and sceLibFont
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspiofilemgr.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspfont.h>

PSP_MODULE_INFO("sceLibFont sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4)
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)

static unsigned int __attribute__((aligned(16))) list[262144];

static unsigned short __attribute__((aligned(16))) clut[16] = {
    0x0fff, 0x1fff, 0x2fff, 0x3fff, 0x4fff, 0x5fff, 0x6fff, 0x7fff,
    0x8fff, 0x9fff, 0xafff, 0xbfff, 0xcfff, 0xdfff, 0xefff, 0xffff,
};

typedef struct
{
    float u, v;
    unsigned int color;
    short x, y, z;
    short pad;
} Vertex;

static void* fontAlloc(void* data, unsigned int size) { return memalign(16, size); }
static void fontFree(void* data, void* pointer) { free(pointer); }

int main(void)
{
    int errorCode;

    sceGuInit();
    sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(GU_PSM_8888, NULL, 512);
    sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT, (void*)FRAME_SIZE, 512);
    sceGuDepthBuffer((void*)(FRAME_SIZE * 2), 512);
    sceGuOffset(2048 - (SCR_WIDTH / 2), 2048 - (SCR_HEIGHT / 2));
    sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
    sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuEnable(GU_BLEND);
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);
    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

    SceFontLibData libData = {0};
    libData.maxFonts = 4;
    libData.alloc = fontAlloc;
    libData.free = fontFree;

    SceFontStyle targetStyle = {0};
    targetStyle.family = SCE_FONT_FAMILY_DEFAULT;

    void* libHandle = sceFontNewLib(&libData, &errorCode);
    int fontIdx = sceFontFindOptimumFont(libHandle, &targetStyle, &errorCode);
    void* fontHandle = sceFontOpen(libHandle, fontIdx, 0, &errorCode);

    unsigned char* imageTex = (unsigned char*)memalign(16, 65536);
    memset(imageTex, 0, 65536);

    SceFontImageBuffer imageBufferInfo;
    imageBufferInfo.pixelFormat = SCE_FONT_PIXEL_FORMAT_L4;
    imageBufferInfo.x = 0;
    imageBufferInfo.y = 0;
    imageBufferInfo.size.width = 512;
    imageBufferInfo.size.height = 256;
    imageBufferInfo.bytesPerLine = 256;
    imageBufferInfo.unknown = 0;
    imageBufferInfo.data = imageTex;

    char* hello = "Hello from pspdev";
    int helloLen = strlen(hello);

    unsigned int colors[] = {
        0xFF0000FF,
        0xFF00FF00,
        0xFFFF0000,
        0xFF00FFFF
    };

    SceFontInfo fontInfo;
    sceFontGetFontInfo(fontHandle, &fontInfo);
    int lineHeight = (fontInfo.maxFixed.top - fontInfo.maxFixed.bottom + 256) >> 6;

    int widths[4] = {0, 0, 0, 0};

    for (int i = 0; i < 4; i++)
    {
        int cx = 0;

        for (int j = 0; j < helloLen; j++)
        {
            SceFontCharacterInfo charInfo;
            if (sceFontGetCharInfo(fontHandle, (unsigned short)hello[j], &charInfo) == 0)
            {
                imageBufferInfo.x = cx + charInfo.data.shiftX;
                imageBufferInfo.y = i * (fontInfo.maxFixed.top - fontInfo.maxFixed.bottom + 256) + fontInfo.maxFixed.top
                    - charInfo.data.shiftY;

                sceFontGetCharGlyphImage(fontHandle, (unsigned short)hello[j], &imageBufferInfo);
                cx += charInfo.data.hShift;
            }
        }
        widths[i] = cx >> 6;
    }

    sceKernelDcacheWritebackAll();
    sceFontClose(fontHandle);
    sceFontDoneLib(libHandle);

    while (1)
    {
        sceGuStart(GU_DIRECT, list);
        sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

        sceGuClutMode(GU_PSM_4444, 0, 0xFF, 0);
        sceGuClutLoad(1, clut);
        sceGuTexMode(GU_PSM_T4, 0, 0, 0);
        sceGuTexImage(0, 512, 256, 512, imageTex);
        sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
        sceGuTexFilter(GU_LINEAR, GU_LINEAR);

        Vertex* vertices = (Vertex*)sceGuGetMemory(sizeof(Vertex) * 8);

        for (int i = 0; i < 4; i++)
        {
            vertices[i * 2].u = 0;
            vertices[i * 2].v = i * lineHeight;
            vertices[i * 2].color = colors[i];
            vertices[i * 2].x = 0;
            vertices[i * 2].y = i * (lineHeight + 6);
            vertices[i * 2].z = 0;

            vertices[i * 2 + 1].u = widths[i];
            vertices[i * 2 + 1].v = (i + 1) * lineHeight;
            vertices[i * 2 + 1].color = colors[i];
            vertices[i * 2 + 1].x = widths[i];
            vertices[i * 2 + 1].y = i * (lineHeight + 6) + lineHeight;
            vertices[i * 2 + 1].z = 0;

            sceGuDrawArray(GU_SPRITES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_16BIT | GU_TRANSFORM_2D, 2, NULL,
                           &vertices[i * 2]);
        }

        sceGuFinish();
        sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    sceGuTerm();
    free(imageTex);
    sceKernelExitGame();
    return 0;
}
