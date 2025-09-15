/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspdisplay.h - Prototypes for the sceDisplay library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2007 Alexander Berl <raphael@fx-world.org>
 *
 */
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#ifdef __cplusplus
extern "C" {
#endif

/** Framebuffer pixel formats. */
enum PspDisplayPixelFormats {
	/** 16-bit RGB 5:6:5. */
	PSP_DISPLAY_PIXEL_FORMAT_565 = 0,
	/** 16-bit RGBA 5:5:5:1. */
	PSP_DISPLAY_PIXEL_FORMAT_5551,
	/* 16-bit RGBA 4:4:4:4. */
	PSP_DISPLAY_PIXEL_FORMAT_4444,
	/* 32-bit RGBA 8:8:8:8. */
	PSP_DISPLAY_PIXEL_FORMAT_8888
};

enum PspDisplaySetBufSync {
	/** Buffer change effective next hsync */
	PSP_DISPLAY_SETBUF_NEXTHSYNC = 0,
	/** Buffer change effective next vsync */
	PSP_DISPLAY_SETBUF_NEXTVSYNC = 1
};

/** Values for retro compatibility */
#define PSP_DISPLAY_SETBUF_IMMEDIATE PSP_DISPLAY_SETBUF_NEXTHSYNC
#define PSP_DISPLAY_SETBUF_NEXTFRAME PSP_DISPLAY_SETBUF_NEXTVSYNC

enum PspDisplayMode
{
	/** LCD MAX 480x272 at 59.94005995 Hz */
	PSP_DISPLAY_MODE_LCD = 0,
	/** VESA VGA MAX 640x480 at 59.94047618Hz */
	PSP_DISPLAY_MODE_VESA1A = 0x1A,
	/** PSEUDO VGA MAX 640x480 at 59.94005995Hz*/
	PSP_DISPLAY_MODE_PSEUDO_VGA = 0x60
};
enum PspDisplayErrorCodes
{
   SCE_DISPLAY_ERROR_OK    = 0,
   SCE_DISPLAY_ERROR_POINTER    = 0x80000103,
   SCE_DISPLAY_ERROR_ARGUMENT   = 0x80000107
};


/**
 * Set display mode
 *
 * @par Example1:
 * @code
 * int mode = PSP_DISPLAY_MODE_LCD;
 * int width = 480;
 * int height = 272;
 * sceDisplaySetMode(mode, width, height);
 * @endcode
 *
 * @param mode - One of ::PspDisplayMode
 * @param width - Width of screen in pixels.
 * @param height - Height of screen in pixels.
 *
 * @return when error, a negative value is returned.
 */
int sceDisplaySetMode(int mode, int width, int height);

/**
 * Get display mode
 *
 * @param pmode - Pointer to an integer to receive the current mode.
 * @param pwidth - Pointer to an integer to receive the current width.
 * @param pheight - Pointer to an integer to receive the current height,
 *
 * @return 0 on success
 */
int sceDisplayGetMode(int *pmode, int *pwidth, int *pheight);

/**
 * Display set framebuf
 *
 * @param topaddr - address of start of framebuffer
 * @param bufferwidth - buffer width (must be power of 2)
 * @param pixelformat - One of ::PspDisplayPixelFormats.
 * @param sync - One of ::PspDisplaySetBufSync
 *
 * @return 0 on success
 */
int sceDisplaySetFrameBuf(void *topaddr, int bufferwidth, int pixelformat, int sync);

/**
 * Get Display Framebuffer information
 *
 * @param topaddr - pointer to void* to receive address of start of framebuffer
 * @param bufferwidth - pointer to int to receive buffer width (must be power of 2)
 * @param pixelformat - pointer to int to receive one of ::PspDisplayPixelFormats.
 * @param sync - One of ::PspDisplaySetBufSync
 *
 * @return 0 on success
 */
int sceDisplayGetFrameBuf(void **topaddr, int *bufferwidth, int *pixelformat, int sync);

/**
 * Number of vertical blank pulses up to now
 */
unsigned int sceDisplayGetVcount(void);

/**
 * Wait for vertical blank start
 */
int sceDisplayWaitVblankStart(void);

/**
 * Wait for vertical blank start with callback
 */
int sceDisplayWaitVblankStartCB(void);

/**
 * Wait for vertical blank
 */
int sceDisplayWaitVblank(void);

/**
 * Wait for vertical blank with callback
 */
int sceDisplayWaitVblankCB(void);

/**
 * Get accumlated HSYNC count
 */
int sceDisplayGetAccumulatedHcount(void);

/**
 * Get current HSYNC count
 */
int sceDisplayGetCurrentHcount(void);

/**
 * Get number of frames per second
 */
float sceDisplayGetFramePerSec(void);

/**
 * Get whether or not frame buffer is being displayed
 */
int sceDisplayIsForeground(void);

/**
 * Test whether VBLANK is active
 */
int sceDisplayIsVblank(void);

/**
 * Get current display brightness
 *
 * @param level - Pointer to int to receive the current brightness level (0-100)
 * @param unk1 - Pointer to int, receives unknown, it's 1 or 0
 *
 * @return 0 on success
 */
int sceDisplayGetBrightness(int *level, int *unk1);

/**
 * Get resume mode
 *
 * @warning This function can crash your app or worst(unexpected forced turn off your PSP)
 *
 * @param resume_mode - Pointer to int to receive the current resume mode
 *
 * @return ???
 */
int sceDisplayGetResumeMode(int *resume_mode);

/**
 * Get the time remaining until the next vertical blank
 *
 * @note start with sceDisplayWaitVblankStart() to take effect
 *
 * @return time remaining(in microsecond? or millisecond?)
 *
 * @return < 0 on error
 */
int sceDisplayGetVblankRest(void);

/**
 * Test whether VSYNC is active
 */
int sceDisplayIsVsync(void);

/**
 * Wait for vertical blank start after specified number of vertical periods
 *
 * @param vblank_count - Number of vertical periods before waiting for vertical blank start
 *
 * @return 0 on success
 */
int sceDisplayWaitVblankStartMulti(unsigned int vblank_count);

/**
 * Wait for vertical blank start with callback after specified number of vertical periods
 *
 * @param vblank_count - Number of vertical periods before waiting for vertical blank start
 *
 * @return 0 on success
 */
int sceDisplayWaitVblankStartMultiCB(unsigned int vblank_count);

/**
 * Adjust the accumulated HSYNC count
 *
 * @param hcount - Set accumulated HSYNC count
 *
 * @return 0 on success
 */
int sceDisplayAdjustAccumulatedHcount(int hcount);

#ifdef __cplusplus
}
#endif

#endif
