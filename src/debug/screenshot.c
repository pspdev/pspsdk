/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  screenshot.c - Simple screen debug keyboard
 *
 * Copyright (c) 2025, Francisco Javier Trujillo Mata <fjtrujy@gmail.com>
 *
 */

#include "pspdebug.h"
#include "pspdisplay.h"
#include "pspuser.h"

#define PSP_SCREEN_HEIGHT 272

int bitmapWrite(void *frame_addr, int format, const char *file);

int pspScreenshotSave(const char *filename)
{
    void* buff;
	int bufferwidth, pixelformat;

    int ret = sceDisplayGetFrameBuf(&buff, &bufferwidth, &pixelformat, PSP_DISPLAY_SETBUF_NEXTHSYNC); 
    if (ret != 0 || buff == NULL || bufferwidth == 0) {
        return -1;
    }
    
    // write the screenshot to the file
    return bitmapWrite(buff, pixelformat, filename);
}