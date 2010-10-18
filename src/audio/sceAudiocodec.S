	.set noreorder

#include "pspimport.s"

#ifdef F_sceAudiocodec_0000
	IMPORT_START	"sceAudiocodec",0x40090000
#endif
#ifdef F_sceAudiocodec_0001
	IMPORT_FUNC	"sceAudiocodec",0x9D3F790C,sceAudiocodecCheckNeedMem
#endif
#ifdef F_sceAudiocodec_0002
	IMPORT_FUNC	"sceAudiocodec",0x5B37EB1D,sceAudiocodecInit
#endif
#ifdef F_sceAudiocodec_0003
	IMPORT_FUNC	"sceAudiocodec",0x70A703F8,sceAudiocodecDecode
#endif
#ifdef F_sceAudiocodec_0004
	IMPORT_FUNC	"sceAudiocodec",0x8ACA11D5,sceAudiocodecGetInfo
#endif
#ifdef F_sceAudiocodec_0005
	IMPORT_FUNC	"sceAudiocodec",0x6CD2A861,sceAudiocodec_6CD2A861
#endif
#ifdef F_sceAudiocodec_0006
	IMPORT_FUNC	"sceAudiocodec",0x59176A0F,sceAudiocodec_59176A0F
#endif
#ifdef F_sceAudiocodec_0007
	IMPORT_FUNC	"sceAudiocodec",0x3A20A200,sceAudiocodecGetEDRAM
#endif
#ifdef F_sceAudiocodec_0008
	IMPORT_FUNC	"sceAudiocodec",0x29681260,sceAudiocodecReleaseEDRAM
#endif
