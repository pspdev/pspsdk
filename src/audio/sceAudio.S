	.set noreorder

#include "pspimport.s"

#ifdef F_sceAudio_0000
	IMPORT_START	"sceAudio",0x40010000
#endif
#ifdef F_sceAudio_0001
	IMPORT_FUNC	"sceAudio",0x8C1009B2,sceAudioOutput
#endif
#ifdef F_sceAudio_0002
	IMPORT_FUNC	"sceAudio",0x136CAF51,sceAudioOutputBlocking
#endif
#ifdef F_sceAudio_0003
	IMPORT_FUNC	"sceAudio",0xE2D56B2D,sceAudioOutputPanned
#endif
#ifdef F_sceAudio_0004
	IMPORT_FUNC	"sceAudio",0x13F592BC,sceAudioOutputPannedBlocking
#endif
#ifdef F_sceAudio_0005
	IMPORT_FUNC	"sceAudio",0x5EC81C55,sceAudioChReserve
#endif
#ifdef F_sceAudio_0006
	IMPORT_FUNC	"sceAudio",0x41EFADE7,sceAudioOneshotOutput
#endif
#ifdef F_sceAudio_0007
	IMPORT_FUNC	"sceAudio",0x6FC46853,sceAudioChRelease
#endif
#ifdef F_sceAudio_0008
	IMPORT_FUNC	"sceAudio",0xE9D97901,sceAudioGetChannelRestLen
#endif
#ifdef F_sceAudio_0009
	IMPORT_FUNC	"sceAudio",0xCB2E439E,sceAudioSetChannelDataLen
#endif
#ifdef F_sceAudio_0010
	IMPORT_FUNC	"sceAudio",0x95FD0C2D,sceAudioChangeChannelConfig
#endif
#ifdef F_sceAudio_0011
	IMPORT_FUNC	"sceAudio",0xB7E1D8E7,sceAudioChangeChannelVolume
#endif
#ifdef F_sceAudio_0012
	IMPORT_FUNC	"sceAudio",0x38553111,sceAudioSRCChReserve
#endif
#ifdef F_sceAudio_0013
	IMPORT_FUNC	"sceAudio",0x5C37C0AE,sceAudioSRCChRelease
#endif
#ifdef F_sceAudio_0014
	IMPORT_FUNC	"sceAudio",0xE0727056,sceAudioSRCOutputBlocking
#endif
#ifdef F_sceAudio_0015
	IMPORT_FUNC	"sceAudio",0x086E5895,sceAudioInputBlocking
#endif
#ifdef F_sceAudio_0016
	IMPORT_FUNC	"sceAudio",0x6D4BEC68,sceAudioInput
#endif
#ifdef F_sceAudio_0017
	IMPORT_FUNC	"sceAudio",0xA708C6A6,sceAudioGetInputLength
#endif
#ifdef F_sceAudio_0018
	IMPORT_FUNC	"sceAudio",0x87B2E651,sceAudioWaitInputEnd
#endif
#ifdef F_sceAudio_0019
	IMPORT_FUNC	"sceAudio",0x7DE61688,sceAudioInputInit
#endif
#ifdef F_sceAudio_0020
	IMPORT_FUNC	"sceAudio",0xA633048E,sceAudioPollInputEnd
#endif
#ifdef F_sceAudio_0021
	IMPORT_FUNC	"sceAudio",0xB011922F,sceAudioGetChannelRestLength
#endif
#ifdef F_sceAudio_0022
	IMPORT_FUNC	"sceAudio",0xE926D3FB,sceAudioInputInitEx
#endif
#ifdef F_sceAudio_0023
	IMPORT_FUNC	"sceAudio",0x01562BA3,sceAudioOutput2Reserve
#endif
#ifdef F_sceAudio_0024
	IMPORT_FUNC	"sceAudio",0x2D53F36E,sceAudioOutput2OutputBlocking
#endif
#ifdef F_sceAudio_0025
	IMPORT_FUNC	"sceAudio",0x43196845,sceAudioOutput2Release
#endif
#ifdef F_sceAudio_0026
	IMPORT_FUNC	"sceAudio",0x63F2889C,sceAudioOutput2ChangeLength
#endif
#ifdef F_sceAudio_0027
	IMPORT_FUNC	"sceAudio",0x647CEF33,sceAudioOutput2GetRestSample
#endif

