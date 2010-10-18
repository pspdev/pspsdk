	.set noreorder

#include "pspimport.s"

#ifdef F_sceAtrac3plus_0000
	IMPORT_START	"sceAtrac3plus",0x00090000
#endif
#ifdef F_sceAtrac3plus_0001
	IMPORT_FUNC	"sceAtrac3plus",0xD1F59FDB,sceAtracStartEntry
#endif
#ifdef F_sceAtrac3plus_0002
	IMPORT_FUNC	"sceAtrac3plus",0xD5C28CC0,sceAtracEndEntry
#endif
#ifdef F_sceAtrac3plus_0003
	IMPORT_FUNC	"sceAtrac3plus",0x780F88D1,sceAtracGetAtracID
#endif
#ifdef F_sceAtrac3plus_0004
	IMPORT_FUNC	"sceAtrac3plus",0x61EB33F5,sceAtracReleaseAtracID
#endif
#ifdef F_sceAtrac3plus_0005
	IMPORT_FUNC	"sceAtrac3plus",0x0E2A73AB,sceAtracSetData
#endif
#ifdef F_sceAtrac3plus_0006
	IMPORT_FUNC	"sceAtrac3plus",0x3F6E26B5,sceAtracSetHalfwayBuffer
#endif
#ifdef F_sceAtrac3plus_0007
	IMPORT_FUNC	"sceAtrac3plus",0x7A20E7AF,sceAtracSetDataAndGetID
#endif
#ifdef F_sceAtrac3plus_0008
	IMPORT_FUNC	"sceAtrac3plus",0x0FAE370E,sceAtracSetHalfwayBufferAndGetID
#endif
#ifdef F_sceAtrac3plus_0009
	IMPORT_FUNC	"sceAtrac3plus",0x6A8C3CD5,sceAtracDecodeData
#endif
#ifdef F_sceAtrac3plus_0010
	IMPORT_FUNC	"sceAtrac3plus",0x9AE849A7,sceAtracGetRemainFrame
#endif
#ifdef F_sceAtrac3plus_0011
	IMPORT_FUNC	"sceAtrac3plus",0x5D268707,sceAtracGetStreamDataInfo
#endif
#ifdef F_sceAtrac3plus_0012
	IMPORT_FUNC	"sceAtrac3plus",0x7DB31251,sceAtracAddStreamData
#endif
#ifdef F_sceAtrac3plus_0013
	IMPORT_FUNC	"sceAtrac3plus",0x83E85EA0,sceAtracGetSecondBufferInfo
#endif
#ifdef F_sceAtrac3plus_0014
	IMPORT_FUNC	"sceAtrac3plus",0x83BF7AFD,sceAtracSetSecondBuffer
#endif
#ifdef F_sceAtrac3plus_0015
	IMPORT_FUNC	"sceAtrac3plus",0xE23E3A35,sceAtracGetNextDecodePosition
#endif
#ifdef F_sceAtrac3plus_0016
	IMPORT_FUNC	"sceAtrac3plus",0xA2BBA8BE,sceAtracGetSoundSample
#endif
#ifdef F_sceAtrac3plus_0017
	IMPORT_FUNC	"sceAtrac3plus",0x31668BAA,sceAtracGetChannel
#endif
#ifdef F_sceAtrac3plus_0018
	IMPORT_FUNC	"sceAtrac3plus",0xD6A5F2F7,sceAtracGetMaxSample
#endif
#ifdef F_sceAtrac3plus_0019
	IMPORT_FUNC	"sceAtrac3plus",0x36FAABFB,sceAtracGetNextSample
#endif
#ifdef F_sceAtrac3plus_0020
	IMPORT_FUNC	"sceAtrac3plus",0xA554A158,sceAtracGetBitrate
#endif
#ifdef F_sceAtrac3plus_0021
	IMPORT_FUNC	"sceAtrac3plus",0xFAA4F89B,sceAtracGetLoopStatus
#endif
#ifdef F_sceAtrac3plus_0022
	IMPORT_FUNC	"sceAtrac3plus",0x868120B5,sceAtracSetLoopNum
#endif
#ifdef F_sceAtrac3plus_0023
	IMPORT_FUNC	"sceAtrac3plus",0xCA3CA3D2,sceAtracGetBufferInfoForReseting
#endif
#ifdef F_sceAtrac3plus_0024
	IMPORT_FUNC	"sceAtrac3plus",0x644E5607,sceAtracResetPlayPosition
#endif
#ifdef F_sceAtrac3plus_0025
	IMPORT_FUNC	"sceAtrac3plus",0xE88F759B,sceAtracGetInternalErrorInfo
#endif
