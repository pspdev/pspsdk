/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspusbcam.h - Prototypes for the sceUsbCam library
 *
 * Copyright (c) 2007 dot_blank
 *
 * $Id: pspusbcam.h 2433 2008-10-15 10:00:27Z iwn $
 */
#ifndef __PSPUSBCAM_H__
#define __PSPUSBCAM_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PSP_USBCAM_PID				    (0x282)
#define PSP_USBCAM_DRIVERNAME		  "USBCamDriver"
#define PSP_USBCAMMIC_DRIVERNAME	"USBCamMicDriver"

/** Resolutions for sceUsbCamSetupStill & 
                    sceUsbCamSetupVideo
 ** DO NOT use on sceUsbCamSetupStillEx & sceUsbCamSetupVideoEx */
enum PspUsbCamResolution
{
	PSP_USBCAM_RESOLUTION_160_120  = 0,
	PSP_USBCAM_RESOLUTION_176_144  = 1,
	PSP_USBCAM_RESOLUTION_320_240  = 2,
	PSP_USBCAM_RESOLUTION_352_288  = 3,
	PSP_USBCAM_RESOLUTION_640_480  = 4,
	PSP_USBCAM_RESOLUTION_1024_768 = 5,
	PSP_USBCAM_RESOLUTION_1280_960 = 6,
	PSP_USBCAM_RESOLUTION_480_272  = 7,
	PSP_USBCAM_RESOLUTION_360_272  = 8,
};

/** Resolutions for sceUsbCamSetupStillEx & 
                    sceUsbCamSetupVideoEx
 ** DO NOT use on sceUsbCamSetupStill & sceUsbCamSetupVideo */
enum PspUsbCamResolutionEx
{
	PSP_USBCAM_RESOLUTION_EX_160_120  = 0,
	PSP_USBCAM_RESOLUTION_EX_176_144  = 1,
	PSP_USBCAM_RESOLUTION_EX_320_240  = 2,
	PSP_USBCAM_RESOLUTION_EX_352_288  = 3,
	PSP_USBCAM_RESOLUTION_EX_360_272  = 4,
	PSP_USBCAM_RESOLUTION_EX_480_272  = 5,
	PSP_USBCAM_RESOLUTION_EX_640_480  = 6,
	PSP_USBCAM_RESOLUTION_EX_1024_768 = 7,
	PSP_USBCAM_RESOLUTION_EX_1280_960 = 8,
};

/** Flags for reverse effects. */
enum PspUsbCamReverseFlags
{
	PSP_USBCAM_FLIP = 1,
	PSP_USBCAM_MIRROR = 0x100,
};

/** Delay to take pictures */
enum PspUsbCamDelay
{
	PSP_USBCAM_NODELAY = 0,
	PSP_USBCAM_DELAY_10SEC = 1,
	PSP_USBCAM_DELAY_20SEC = 2,
	PSP_USBCAM_DELAY_30SEC = 3,
};

/** Usbcam framerates */
enum PspUsbCamFrameRate
{
	PSP_USBCAM_FRAMERATE_3_75_FPS = 0, /* 3.75 fps */
	PSP_USBCAM_FRAMERATE_5_FPS = 1, 
	PSP_USBCAM_FRAMERATE_7_5_FPS = 2, /* 7.5 fps */
	PSP_USBCAM_FRAMERATE_10_FPS = 3, 
	PSP_USBCAM_FRAMERATE_15_FPS = 4, 
	PSP_USBCAM_FRAMERATE_20_FPS = 5, 
	PSP_USBCAM_FRAMERATE_30_FPS = 6,
	PSP_USBCAM_FRAMERATE_60_FPS = 7,
};

/** White balance values */
enum PspUsbCamWB
{
	PSP_USBCAM_WB_AUTO = 0,
	PSP_USBCAM_WB_DAYLIGHT = 1,
	PSP_USBCAM_WB_FLUORESCENT = 2,
	PSP_USBCAM_WB_INCADESCENT = 3,
};

/** Effect modes */
enum PspUsbCamEffectMode
{
	PSP_USBCAM_EFFECTMODE_NORMAL = 0,
	PSP_USBCAM_EFFECTMODE_NEGATIVE = 1,
	PSP_USBCAM_EFFECTMODE_BLACKWHITE = 2,
	PSP_USBCAM_EFFECTMODE_SEPIA = 3,
	PSP_USBCAM_EFFECTMODE_BLUE = 4,
	PSP_USBCAM_EFFECTMODE_RED = 5,
	PSP_USBCAM_EFFECTMODE_GREEN = 6,
};

/** Exposure levels */
enum PspUsbCamEVLevel
{
	PSP_USBCAM_EVLEVEL_2_0_POSITIVE = 0, // +2.0
	PSP_USBCAM_EVLEVEL_1_7_POSITIVE = 1, // +1.7
	PSP_USBCAM_EVLEVEL_1_5_POSITIVE = 2, // +1.5
	PSP_USBCAM_EVLEVEL_1_3_POSITIVE = 3, // +1.3
	PSP_USBCAM_EVLEVEL_1_0_POSITIVE = 4, // +1.0
	PSP_USBCAM_EVLEVEL_0_7_POSITIVE = 5, // +0.7
	PSP_USBCAM_EVLEVEL_0_5_POSITIVE = 6, // +0.5
	PSP_USBCAM_EVLEVEL_0_3_POSITIVE = 7, // +0.3
	PSP_USBCAM_EVLEVEL_0_0 = 8, // 0.0
	PSP_USBCAM_EVLEVEL_0_3_NEGATIVE = 9, // -0.3
	PSP_USBCAM_EVLEVEL_0_5_NEGATIVE = 10, // -0.5
	PSP_USBCAM_EVLEVEL_0_7_NEGATIVE = 11, // -0.7
	PSP_USBCAM_EVLEVEL_1_0_NEGATIVE = 12, // -1.0
	PSP_USBCAM_EVLEVEL_1_3_NEGATIVE = 13, // -1.3
	PSP_USBCAM_EVLEVEL_1_5_NEGATIVE = 14, // -1.5
	PSP_USBCAM_EVLEVEL_1_7_NEGATIVE = 15, // -1.7
	PSP_USBCAM_EVLEVEL_2_0_NEGATIVE = 16, // -2.0
};



/** Structure for sceUsbCamSetupStill */
typedef struct PspUsbCamSetupStillParam {
/** Size of the ::PspUsbCamSetupStillParam structure */
	int size;
/** Resolution. One of ::PspUsbCamResolution */
	int resolution;
/** Size of the jpeg image */
	int	jpegsize;
/** Reverse effect to apply. Zero or more of ::PspUsbCamReverseFlags */
	int reverseflags;
/** Delay to apply to take the picture. One of ::PspUsbCamDelay */
	int delay;
/** JPEG compression level, a value from 1-63. 
    1 -> less compression, better quality; 63 -> max compression, worse quality */
	int complevel;
} PspUsbCamSetupStillParam;

/** Structure for sceUsbCamSetupStillEx */
typedef struct PspUsbCamSetupStillExParam {
/** Size of the ::PspUsbCamSetupStillExParam structure */
	int size;
/** Unknown, set it to 9 at the moment. */
	u32 unk;
/** Resolution. One of ::PspUsbCamResolutionEx */
	int resolution;
/** Size of the jpeg image */
	int jpegsize;
/** JPEG compression level, a value from 1-63. 
    1 -> less compression, better quality; 63 -> max compression, worse quality */
	int complevel;
/** Unknown, set it to 0 at the moment */
	u32 unk2;
/** Unknown, set it to 1 at the moment */
	u32 unk3;
/** Flag that indicates whether to flip the image */
	int flip;
/** Flag that indicates whether to mirror the image */
	int mirror;
/** Delay to apply to take the picture. One of ::PspUsbCamDelay */
	int delay;
/** Unknown, set it to 0 at the moment */
	u32 unk4[5];
} PspUsbCamSetupStillExParam;

typedef struct PspUsbCamSetupVideoParam {
/** Size of the ::PspUsbCamSetupVideoParam structure */
	int size;
/** Resolution. One of ::PspUsbCamResolution */
	int resolution;
/** Framerate. One of ::PspUsbCamFrameRate */
	int framerate;
/** White balance. One of ::PspUsbCamWB */
	int wb;
/** Saturarion (0-255) */
	int saturation;
/** Brightness (0-255) */
	int brightness;
/** Contrast (0-255) */
	int contrast;
/** Sharpness (0-255) */
	int sharpness;
/** Effect mode. One of ::PspUsbCamEffectMode */
	int effectmode;
/** Size of jpeg video frame */
	int framesize;
/** Unknown. Set it to 0 at the moment. */
	u32 unk;
/** Exposure value. One of ::PspUsbCamEVLevel */
	int evlevel;
} PspUsbCamSetupVideoParam;

typedef struct PspUsbCamSetupVideoExParam {
/** Size of the ::PspUsbCamSetupVideoParam structure */
	int size;
/* Unknown. Set it to 9 at the moment. */
	u32 unk;
/** Resolution. One of ::PspUsbCamResolutionEx */
	int resolution;
/** Framerate. One of ::PspUsbCamFrameRate */
	int framerate;
/** Unknown. Set it to 2 at the moment */
	u32 unk2;
/** Unknown. Set it to 3 at the moment */
	u32 unk3;
/** White balance. One of ::PspUsbCamWB */
	int wb;
/** Saturarion (0-255) */
	int saturation;
/** Brightness (0-255) */
	int brightness;
/** Contrast (0-255) */
	int contrast;
/** Sharpness (0-255) */
	int sharpness;
/** Unknown. Set it to 0 at the moment */
	u32 unk4;
/** Unknown. Set it to 1 at the moment */
	u32 unk5;
/** Unknown. Set it to 0 at the moment */
	u32 unk6[3];
/** Effect mode. One of ::PspUsbCamEffectMode */
	int effectmode;
/** Unknown. Set it to 1 at the moment */
	u32 unk7;
/** Unknown. Set it to 10 at the moment */
	u32 unk8;
/** Unknown. Set it to 2 at the moment */
	u32 unk9;
/** Unknown. Set it to 500 at the moment */
	u32 unk10;
/** Unknown. Set it to 1000 at the moment */
	u32 unk11;
/** Size of jpeg video frame */
	int framesize;
/** Unknown. Set it to 0 at the moment */
	u32 unk12;
/** Exposure value. One of ::PspUsbCamEVLevel */
	int evlevel;
} PspUsbCamSetupVideoExParam;

/**
 * Setups the parameters to take a still image.
 *
 * @param param - pointer to a ::PspUsbCamSetupStillParam 
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamSetupStill(PspUsbCamSetupStillParam *param);

/**
 * Setups the parameters to take a still image (with more options)
 *
 * @param param - pointer to a ::PspUsbCamSetupStillParamEx 
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamSetupStillEx(PspUsbCamSetupStillExParam *param);

/**
 * Gets a still image. The function doesn't return until the image 
 * has been acquired.
 *
 * @param buf - The buffer that receives the image jpeg data
 * @param size - The size of the buffer.
 *
 * @return size of acquired image on success, < 0 on error
*/
int sceUsbCamStillInputBlocking(u8 *buf, SceSize size);

/**
 * Gets a still image. The function returns inmediately, and
 * the completion has to be handled by calling ::sceUsbCamStillWaitInputEnd
 * or ::sceUsbCamStillPollInputEnd.
 *
 * @param buf - The buffer that receives the image jpeg data
 * @param size - The size of the buffer.
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamStillInput(u8 *buf, SceSize size);

/** 
 * Waits untils still input has been finished.
 *
 * @return the size of the acquired image on sucess, < 0 on error
*/
int sceUsbCamStillWaitInputEnd(void);

/**
 * Polls the status of still input completion.
 *
 * @return the size of the acquired image if still input has ended, 
 * 0 if the input has not ended, < 0 on error.
*/
int sceUsbCamStillPollInputEnd(void);

/** 
 * Cancels the still input.
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamStillCancelInput(void);

/**
 * Gets the size of the acquired still image.
 *
 * @return the size of the acquired image on success, < 0 on error
*/
int sceUsbCamStillGetInputLength(void);

/**
 * Set ups the parameters for video capture.
 *
 * @param param - Pointer to a ::PspUsbCamSetupVideoParam structure.
 * @param workarea - Pointer to a buffer used as work area by the driver.
 * @param wasize - Size of the work area.
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamSetupVideo(PspUsbCamSetupVideoParam *param, void *workarea, int wasize);

/**
 * Set ups the parameters for video capture (with more options)
 *
 * @param param - Pointer to a ::PspUsbCamSetupVideoExParam structure.
 * @param workarea - Pointer to a buffer used as work area by the driver.
 * @param wasize - Size of the work area.
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamSetupVideoEx(PspUsbCamSetupVideoExParam *param, void *workarea, int wasize);

/**
 * Starts video input from the camera.
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamStartVideo(void);

/**
 * Stops video input from the camera.
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamStopVideo(void);

/**
 * Reads a video frame. The function doesn't return until the frame 
 * has been acquired.
 *
 * @param buf - The buffer that receives the frame jpeg data
 * @param size - The size of the buffer.
 *
 * @return size of acquired frame on success, < 0 on error
*/
int sceUsbCamReadVideoFrameBlocking(u8 *buf, SceSize size);

/**
 * Reads a video frame. The function returns inmediately, and
 * the completion has to be handled by calling ::sceUsbCamWaitReadVideoFrameEnd
 * or ::sceUsbCamPollReadVideoFrameEnd.
 *
 * @param buf - The buffer that receives the frame jpeg data
 * @param size - The size of the buffer.
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamReadVideoFrame(u8 *buf, SceSize size);

/** 
 * Waits untils the current frame has been read.
 *
 * @return the size of the acquired frame on sucess, < 0 on error
*/
int sceUsbCamWaitReadVideoFrameEnd(void);

/**
 * Polls the status of video frame read completion.
 *
 * @return the size of the acquired frame if it has been read, 
 * 0 if the frame has not yet been read, < 0 on error.
*/
int sceUsbCamPollReadVideoFrameEnd(void);

/**
 * Gets the size of the acquired frame.
 *
 * @return the size of the acquired frame on success, < 0 on error
*/
int sceUsbCamGetReadVideoFrameSize(void);

/**
 * Sets the saturation 
 *
 * @param saturation - The saturation (0-255)
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamSetSaturation(int saturation);

/**
 * Sets the brightness
 *
 * @param brightness - The brightness (0-255)
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamSetBrightness(int brightness);

/**
 * Sets the contrast
 *
 * @param contrast - The contrast (0-255)
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamSetContrast(int contrast);

/**
 * Sets the sharpness
 *
 * @param sharpness - The sharpness (0-255)
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamSetSharpness(int sharpness);

/**
 * Sets the image effect mode
 *
 * @param effectmode - The effect mode, one of ::PspUsbCamEffectMode
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamSetImageEffectMode(int effectmode);

/**
 * Sets the exposure level
 *
 * @param ev - The exposure level, one of ::PspUsbCamEVLevel
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamSetEvLevel(int ev);

/**
 * Sets the reverse mode
 *
 * @param reverseflags - The reverse flags, zero or more of ::PspUsbCamReverseFlags
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamSetReverseMode(int reverseflags);

/**
 * Sets the zoom.
 *
 * @param zoom - The zoom level starting by 10. (10 = 1X, 11 = 1.1X, etc)
 *
 * @returns 0 on success, < 0 on error
*/
int sceUsbCamSetZoom(int zoom);

/**
 * Gets the current saturation
 *
 * @param saturation - pointer to a variable that receives the current saturation
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamGetSaturation(int *saturation);

/**
 * Gets the current brightness
 *
 * @param brightness - pointer to a variable that receives the current brightness
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamGetBrightness(int *brightness);

/**
 * Gets the current contrast
 *
 * @param contrast - pointer to a variable that receives the current contrast
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamGetContrast(int *contrast);

/**
 * Gets the current sharpness
 *
 * @param brightness - pointer to a variable that receives the current sharpness
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamGetSharpness(int *sharpness);

/**
 * Gets the current image efect mode
 *
 * @param effectmode - pointer to a variable that receives the current effect mode
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamGetImageEffectMode(int *effectmode);

/**
 * Gets the current exposure level.
 *
 * @param ev - pointer to a variable that receives the current exposure level
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamGetEvLevel(int *ev);

/**
 * Gets the current reverse mode.
 *
 * @param reverseflags - pointer to a variable that receives the current reverse mode flags
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamGetReverseMode(int *reverseflags);

/**
 * Gets the current zoom.
 *
 * @param zoom - pointer to a variable that receives the current zoom
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamGetZoom(int *zoom);

/**
 * Sets if the image should be automatically reversed, depending of the position
 * of the camera.
 *
 * @param on - 1 to set the automatical reversal of the image, 0 to set it off
 *
 * @return 0 on success, < 0 on error
*/
int sceUsbCamAutoImageReverseSW(int on);

/**
 * Gets the state of the autoreversal of the image.
 *
 * @return 1 if it is set to automatic, 0 otherwise
*/
int sceUsbCamGetAutoImageReverseState(void);

/**
 * Gets the direction of the camera lens
 *
 * @return 1 if the camera is "looking to you", 0 if the camera
 * is "looking to the other side".
*/
int sceUsbCamGetLensDirection(void);

#ifdef __cplusplus
}
#endif

#endif 



