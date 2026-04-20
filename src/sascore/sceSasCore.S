	.set noreorder

#include "pspimport.s"

#ifdef F_sceSasCore_0000
	IMPORT_START	"sceSasCore",0x40090011
#endif
#ifdef F___sceSasInit_0001
	IMPORT_FUNC	"sceSasCore",0x42778A9F,__sceSasInit
#endif
#ifdef F___sceSasCore_0002
	IMPORT_FUNC	"sceSasCore",0xA3589D81,__sceSasCore
#endif
#ifdef F___sceSasCoreWithMix_0003
	IMPORT_FUNC	"sceSasCore",0x50A14DFC,__sceSasCoreWithMix
#endif
#ifdef F___sceSasGetEndFlag_0004
	IMPORT_FUNC	"sceSasCore",0x68A46B95,__sceSasGetEndFlag
#endif
#ifdef F___sceSasSetVolume_0005
	IMPORT_FUNC	"sceSasCore",0x440CA7D8,__sceSasSetVolume
#endif
#ifdef F___sceSasSetPitch_0006
	IMPORT_FUNC	"sceSasCore",0xAD84D37F,__sceSasSetPitch
#endif
#ifdef F___sceSasSetVoice_0007
	IMPORT_FUNC	"sceSasCore",0x99944089,__sceSasSetVoice
#endif
#ifdef F___sceSasSetNoise_0008
	IMPORT_FUNC	"sceSasCore",0xB7660A23,__sceSasSetNoise
#endif
#ifdef F___sceSasSetADSR_0009
	IMPORT_FUNC	"sceSasCore",0x019B25EB,__sceSasSetADSR
#endif
#ifdef F___sceSasSetADSRmode_0010
	IMPORT_FUNC	"sceSasCore",0x9EC3676A,__sceSasSetADSRmode
#endif
#ifdef F___sceSasSetSL_0011
	IMPORT_FUNC	"sceSasCore",0x5F9529F6,__sceSasSetSL
#endif
#ifdef F___sceSasGetEnvelopeHeight_0012
	IMPORT_FUNC	"sceSasCore",0x74AE582A,__sceSasGetEnvelopeHeight
#endif
#ifdef F___sceSasSetSimpleADSR_0013
	IMPORT_FUNC	"sceSasCore",0xCBCD4F79,__sceSasSetSimpleADSR
#endif
#ifdef F___sceSasSetKeyOff_0014
	IMPORT_FUNC	"sceSasCore",0xA0CF2FA4,__sceSasSetKeyOff
#endif
#ifdef F___sceSasSetKeyOn_0015
	IMPORT_FUNC	"sceSasCore",0x76F01ACA,__sceSasSetKeyOn
#endif
#ifdef F___sceSasRevVON_0016
	IMPORT_FUNC	"sceSasCore",0xF983B186,__sceSasRevVON
#endif
#ifdef F___sceSasRevEVOL_0017
	IMPORT_FUNC	"sceSasCore",0xD5A229C9,__sceSasRevEVOL
#endif
#ifdef F___sceSasRevType_0018
	IMPORT_FUNC	"sceSasCore",0x33D4AB37,__sceSasRevType
#endif
#ifdef F___sceSasRevParam_0019
	IMPORT_FUNC	"sceSasCore",0x267A6DD2,__sceSasRevParam
#endif
#ifdef F___sceSasGetPauseFlag_0020
	IMPORT_FUNC	"sceSasCore",0x2C8E6AB3,__sceSasGetPauseFlag
#endif
#ifdef F___sceSasSetPause_0021
	IMPORT_FUNC	"sceSasCore",0x787D04D5,__sceSasSetPause
#endif
#ifdef F___sceSasSetTrianglarWave_0022
	IMPORT_FUNC_WITH_ALIAS	"sceSasCore",0xA232CBE6,__sceSasSetTrianglarWave,__sceSasSetTriangularWave
#endif
#ifdef F___sceSasSetSteepWave_0023
	IMPORT_FUNC	"sceSasCore",0xD5EBBBCD,__sceSasSetSteepWave
#endif
#ifdef F___sceSasGetGrain_0024
	IMPORT_FUNC	"sceSasCore",0xBD11B7C2,__sceSasGetGrain
#endif
#ifdef F___sceSasSetGrain_0025
	IMPORT_FUNC	"sceSasCore",0xD1E0A01E,__sceSasSetGrain
#endif
#ifdef F___sceSasGetOutputmode_0026
	IMPORT_FUNC	"sceSasCore",0xE175EF66,__sceSasGetOutputmode
#endif
#ifdef F___sceSasSetOutputmode_0027
	IMPORT_FUNC	"sceSasCore",0xE855BF76,__sceSasSetOutputmode
#endif
#ifdef F___sceSasGetAllEnvelopeHeights_0028
	IMPORT_FUNC	"sceSasCore",0x07F58C24,__sceSasGetAllEnvelopeHeights
#endif
#ifdef F___sceSasSetVoicePCM_0029
	IMPORT_FUNC	"sceSasCore",0xE1CD9561,__sceSasSetVoicePCM
#endif
#ifdef F___sceSasSetVoiceATRAC3_0030
	IMPORT_FUNC	"sceSasCore",0x4AA9EAD6,__sceSasSetVoiceATRAC3
#endif
#ifdef F___sceSasConcatenateATRAC3_0031
	IMPORT_FUNC	"sceSasCore",0x7497EA85,__sceSasConcatenateATRAC3
#endif
#ifdef F___sceSasUnsetATRAC3_0032
	IMPORT_FUNC	"sceSasCore",0xF6107F00,__sceSasUnsetATRAC3
#endif
