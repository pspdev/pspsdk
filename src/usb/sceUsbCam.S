	.set noreorder

#include "pspimport.s"

#ifdef F_sceUsbCam_0000
	IMPORT_START	"sceUsbCam",0x40090000
#endif
#ifdef F_sceUsbCam_0001
	IMPORT_FUNC	"sceUsbCam",0x03ED7A82,sceUsbCamSetupMic
#endif
#ifdef F_sceUsbCam_0002
	IMPORT_FUNC	"sceUsbCam",0x08AEE98A,sceUsbCamSetMicGain
#endif
#ifdef F_sceUsbCam_0003
	IMPORT_FUNC	"sceUsbCam",0x09C26C7E,sceUsbCamSetContrast
#endif
#ifdef F_sceUsbCam_0004
	IMPORT_FUNC	"sceUsbCam",0x0A41A298,sceUsbCamSetupStillEx
#endif
#ifdef F_sceUsbCam_0005
	IMPORT_FUNC	"sceUsbCam",0x11A1F128,sceUsbCamGetAutoImageReverseState
#endif
#ifdef F_sceUsbCam_0006
	IMPORT_FUNC	"sceUsbCam",0x17F7B2FB,sceUsbCamSetupVideo
#endif
#ifdef F_sceUsbCam_0007
	IMPORT_FUNC	"sceUsbCam",0x1A46CFE7,sceUsbCamStillPollInputEnd
#endif
#ifdef F_sceUsbCam_0008
	IMPORT_FUNC	"sceUsbCam",0x1D686870,sceUsbCamSetEvLevel
#endif
#ifdef F_sceUsbCam_0009
	IMPORT_FUNC	"sceUsbCam",0x1E958148,sceUsbCam_1E958148
#endif
#ifdef F_sceUsbCam_0010
	IMPORT_FUNC	"sceUsbCam",0x2BCD50C0,sceUsbCamGetEvLevel
#endif
#ifdef F_sceUsbCam_0011
	IMPORT_FUNC	"sceUsbCam",0x2E930264,sceUsbCamSetupMicEx
#endif
#ifdef F_sceUsbCam_0012
	IMPORT_FUNC	"sceUsbCam",0x36636925,sceUsbCamReadMicBlocking
#endif
#ifdef F_sceUsbCam_0013
	IMPORT_FUNC	"sceUsbCam",0x383E9FA8,sceUsbCamGetSaturation
#endif
#ifdef F_sceUsbCam_0014
	IMPORT_FUNC	"sceUsbCam",0x3DC0088E,sceUsbCamReadMic
#endif
#ifdef F_sceUsbCam_0015
	IMPORT_FUNC	"sceUsbCam",0x3F0CF289,sceUsbCamSetupStill
#endif
#ifdef F_sceUsbCam_0016
	IMPORT_FUNC	"sceUsbCam",0x41E73E95,sceUsbCamPollReadVideoFrameEnd
#endif
#ifdef F_sceUsbCam_0017
	IMPORT_FUNC	"sceUsbCam",0x41EE8797,sceUsbCamUnregisterLensRotationCallback
#endif
#ifdef F_sceUsbCam_0018
	IMPORT_FUNC	"sceUsbCam",0x4C34F553,sceUsbCamGetLensDirection
#endif
#ifdef F_sceUsbCam_0019
	IMPORT_FUNC	"sceUsbCam",0x4F3D84D5,sceUsbCamSetBrightness
#endif
#ifdef F_sceUsbCam_0020
	IMPORT_FUNC	"sceUsbCam",0x5145868A,sceUsbCamStopMic
#endif
#ifdef F_sceUsbCam_0021
	IMPORT_FUNC	"sceUsbCam",0x574A8C3F,sceUsbCamStartVideo
#endif
#ifdef F_sceUsbCam_0022
	IMPORT_FUNC	"sceUsbCam",0x5778B452,sceUsbCamGetMicDataLength
#endif
#ifdef F_sceUsbCam_0023
	IMPORT_FUNC	"sceUsbCam",0x61BE5CAC,sceUsbCamStillInputBlocking
#endif
#ifdef F_sceUsbCam_0024
	IMPORT_FUNC	"sceUsbCam",0x622F83CC,sceUsbCamSetSharpness
#endif
#ifdef F_sceUsbCam_0025
	IMPORT_FUNC	"sceUsbCam",0x6784E6A8,sceUsbCamSetAntiFlicker
#endif
#ifdef F_sceUsbCam_0026
	IMPORT_FUNC	"sceUsbCam",0x6CF32CB9,sceUsbCamStopVideo
#endif
#ifdef F_sceUsbCam_0027
	IMPORT_FUNC	"sceUsbCam",0x6E205974,sceUsbCamSetSaturation
#endif
#ifdef F_sceUsbCam_0028
	IMPORT_FUNC	"sceUsbCam",0x70F522C5,sceUsbCamGetBrightness
#endif
#ifdef F_sceUsbCam_0029
	IMPORT_FUNC	"sceUsbCam",0x7563AFA1,sceUsbCamStillWaitInputEnd
#endif
#ifdef F_sceUsbCam_0030
	IMPORT_FUNC	"sceUsbCam",0x7DAC0C71,sceUsbCamReadVideoFrameBlocking
#endif
#ifdef F_sceUsbCam_0031
	IMPORT_FUNC	"sceUsbCam",0x82A64030,sceUsbCamStartMic
#endif
#ifdef F_sceUsbCam_0032
	IMPORT_FUNC	"sceUsbCam",0x951BEDF5,sceUsbCamSetReverseMode
#endif
#ifdef F_sceUsbCam_0033
	IMPORT_FUNC	"sceUsbCam",0x95F8901E,sceUsbCam_95F8901E
#endif
#ifdef F_sceUsbCam_0034
	IMPORT_FUNC	"sceUsbCam",0x994471E0,sceUsbCamGetImageEffectMode
#endif
#ifdef F_sceUsbCam_0035
	IMPORT_FUNC	"sceUsbCam",0x99D86281,sceUsbCamReadVideoFrame
#endif
#ifdef F_sceUsbCam_0036
	IMPORT_FUNC	"sceUsbCam",0x9E8AAF8D,sceUsbCamGetZoom
#endif
#ifdef F_sceUsbCam_0037
	IMPORT_FUNC	"sceUsbCam",0xA063A957,sceUsbCamGetContrast
#endif
#ifdef F_sceUsbCam_0038
	IMPORT_FUNC	"sceUsbCam",0xA720937C,sceUsbCamStillCancelInput
#endif
#ifdef F_sceUsbCam_0039
	IMPORT_FUNC	"sceUsbCam",0xAA7D94BA,sceUsbCamGetAntiFlicker
#endif
#ifdef F_sceUsbCam_0040
	IMPORT_FUNC	"sceUsbCam",0xB048A67D,sceUsbCamWaitReadMicEnd
#endif
#ifdef F_sceUsbCam_0041
	IMPORT_FUNC	"sceUsbCam",0xC484901F,sceUsbCamSetZoom
#endif
#ifdef F_sceUsbCam_0042
	IMPORT_FUNC	"sceUsbCam",0xC72ED6D3,sceUsbCam_C72ED6D3
#endif
#ifdef F_sceUsbCam_0043
	IMPORT_FUNC	"sceUsbCam",0xCFE9E999,sceUsbCamSetupVideoEx
#endif
#ifdef F_sceUsbCam_0044
	IMPORT_FUNC	"sceUsbCam",0xD293A100,sceUsbCamRegisterLensRotationCallback
#endif
#ifdef F_sceUsbCam_0045
	IMPORT_FUNC	"sceUsbCam",0xD4876173,sceUsbCamSetImageEffectMode
#endif
#ifdef F_sceUsbCam_0046
	IMPORT_FUNC	"sceUsbCam",0xD5279339,sceUsbCamGetReverseMode
#endif
#ifdef F_sceUsbCam_0047
	IMPORT_FUNC	"sceUsbCam",0xD865997B,sceUsbCam_D865997B
#endif
#ifdef F_sceUsbCam_0048
	IMPORT_FUNC	"sceUsbCam",0xDF9D0C92,sceUsbCamGetReadVideoFrameSize
#endif
#ifdef F_sceUsbCam_0049
	IMPORT_FUNC	"sceUsbCam",0xE5959C36,sceUsbCamStillGetInputLength
#endif
#ifdef F_sceUsbCam_0050
	IMPORT_FUNC	"sceUsbCam",0xF8847F60,sceUsbCamPollReadMicEnd
#endif
#ifdef F_sceUsbCam_0051
	IMPORT_FUNC	"sceUsbCam",0xF90B2293,sceUsbCamWaitReadVideoFrameEnd
#endif
#ifdef F_sceUsbCam_0052
	IMPORT_FUNC	"sceUsbCam",0xF93C4669,sceUsbCamAutoImageReverseSW
#endif
#ifdef F_sceUsbCam_0053
	IMPORT_FUNC	"sceUsbCam",0xFB0A6C5D,sceUsbCamStillInput
#endif
#ifdef F_sceUsbCam_0054
	IMPORT_FUNC	"sceUsbCam",0xFDB68C23,sceUsbCamGetSharpness
#endif
