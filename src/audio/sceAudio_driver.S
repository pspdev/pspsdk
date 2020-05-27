	.set noreorder

#include "pspimport.s"

#ifdef F_sceAudio_driver_0000
	IMPORT_START	"sceAudio_driver",0x00010000
#endif

#ifdef F_sceAudio_driver_0001
	IMPORT_FUNC	"sceAudio_driver",0x80F1F7E0,sceAudioInit
#endif

#ifdef F_sceAudio_driver_0002 
	IMPORT_FUNC	"sceAudio_driver",0x210567F7,sceAudioEnd
#endif

#ifdef F_sceAudio_driver_0003 
	IMPORT_FUNC	"sceAudio_driver",0xA2BEAA6C,sceAudioSetFrequency 
#endif

#ifdef F_sceAudio_driver_0004
	IMPORT_FUNC	"sceAudio_driver",0xB61595C0,sceAudioLoopbackTest 
#endif

#ifdef F_sceAudio_driver_0005
	IMPORT_FUNC	"sceAudio_driver",0x927AC32B,sceAudioSetVolumeOffset 
#endif

#ifdef F_sceAudio_driver_0006
	IMPORT_FUNC	"sceAudio_driver",0x8C1009B2,sceAudioOutput 
#endif

#ifdef F_sceAudio_driver_0007
	IMPORT_FUNC	"sceAudio_driver",0x136CAF51,sceAudioOutputBlocking 
#endif

#ifdef F_sceAudio_driver_0008
	IMPORT_FUNC	"sceAudio_driver",0xE2D56B2D,sceAudioOutputPanned 
#endif

#ifdef F_sceAudio_driver_0009
	IMPORT_FUNC	"sceAudio_driver",0x13F592BC,sceAudioOutputPannedBlocking 
#endif

#ifdef F_sceAudio_driver_0010
	IMPORT_FUNC	"sceAudio_driver",0x5EC81C55,sceAudioChReserve 
#endif

#ifdef F_sceAudio_driver_0011
	IMPORT_FUNC	"sceAudio_driver",0x41EFADE7,sceAudioOneshotOutput 
#endif

#ifdef F_sceAudio_driver_0012
	IMPORT_FUNC	"sceAudio_driver",0x6FC46853,sceAudioChRelease 
#endif

#ifdef F_sceAudio_driver_0013
	IMPORT_FUNC	"sceAudio_driver",0xB011922F,sceAudio_driver_B011922F 
#endif

#ifdef F_sceAudio_driver_0014
	IMPORT_FUNC	"sceAudio_driver",0xCB2E439E,sceAudioSetChannelDataLen 
#endif

#ifdef F_sceAudio_driver_0015
	IMPORT_FUNC	"sceAudio_driver",0x95FD0C2D,sceAudioChangeChannelConfig 
#endif

#ifdef F_sceAudio_driver_0016
	IMPORT_FUNC	"sceAudio_driver",0xB7E1D8E7,sceAudioChangeChannelVolume 
#endif

#ifdef F_sceAudio_driver_0017
	IMPORT_FUNC	"sceAudio_driver",0x38553111,sceAudio_driver_38553111 
#endif

#ifdef F_sceAudio_driver_0018
	IMPORT_FUNC	"sceAudio_driver",0x5C37C0AE,sceAudio_driver_5C37C0AE 
#endif

#ifdef F_sceAudio_driver_0019
	IMPORT_FUNC	"sceAudio_driver",0xE0727056,sceAudio_driver_E0727056 
#endif

#ifdef F_sceAudio_driver_0020
	IMPORT_FUNC	"sceAudio_driver",0x086E5895,sceAudioInputBlocking 
#endif

#ifdef F_sceAudio_driver_0021
	IMPORT_FUNC	"sceAudio_driver",0x6D4BEC68,sceAudioInput 
#endif

#ifdef F_sceAudio_driver_0022
	IMPORT_FUNC	"sceAudio_driver",0xA708C6A6,sceAudioGetInputLength 
#endif

#ifdef F_sceAudio_driver_0023
	IMPORT_FUNC	"sceAudio_driver",0x87B2E651,sceAudioWaitInputEnd 
#endif

#ifdef F_sceAudio_driver_0024
	IMPORT_FUNC	"sceAudio_driver",0x7DE61688,sceAudioInputInit 
#endif

#ifdef F_sceAudio_driver_0025
	IMPORT_FUNC	"sceAudio_driver",0xE926D3FB,sceAudioInputInitEx 
#endif

#ifdef F_sceAudio_driver_0026
	IMPORT_FUNC	"sceAudio_driver",0xA633048E,sceAudioPollInputEnd 
#endif

#ifdef F_sceAudio_driver_0027
	IMPORT_FUNC	"sceAudio_driver",0xE9D97901,sceAudioGetChannelRestLen 
#endif

