	.set noreorder

#include "pspimport.s"

#ifdef F_sceVaudio_0000
	IMPORT_START	"sceVaudio",0x40090000
#endif
#ifdef F_sceVaudio_0001
	IMPORT_FUNC		"sceVaudio",0x8986295E,sceVaudioOutputBlocking
#endif
#ifdef F_sceVaudio_0002
	IMPORT_FUNC		"sceVaudio",0x03B6807D,sceVaudioChReserve
#endif
#ifdef F_sceVaudio_0003
	IMPORT_FUNC		"sceVaudio",0x67585DFD,sceVaudioChRelease
#endif
#ifdef F_sceVaudio_0004
	IMPORT_FUNC		"sceVaudio",0x346fbe94,sceVaudioSetEffectType
#endif
#ifdef F_sceVaudio_0005
	IMPORT_FUNC		"sceVaudio",0xcbd4ac51,sceVaudioSetAlcMode
#endif
#ifdef F_sceVaudio_0006
	IMPORT_FUNC		"sceVaudio",0x504E4745,sceVaudio_504E4745
#endif
#ifdef F_sceVaudio_0007
	IMPORT_FUNC		"sceVaudio",0x27ACC20B,sceVaudioChReserveBuffering
#endif
#ifdef F_sceVaudio_0008
	IMPORT_FUNC		"sceVaudio",0xE8E78DC8,sceVaudio_E8E78DC8
#endif
