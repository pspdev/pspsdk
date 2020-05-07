	.set noreorder

#include "pspimport.s"

// Build List
// sceMp3_0000.o sceMp3_0001.o sceMp3_0002.o sceMp3_0003.o sceMp3_0004.o sceMp3_0005.o sceMp3_0006.o sceMp3_0007.o sceMp3_0008.o sceMp3_0009.o sceMp3_0010.o sceMp3_0011.o sceMp3_0012.o sceMp3_0013.o sceMp3_0014.o sceMp3_0015.o sceMp3_0016.o sceMp3_0017.o sceMp3_0018.o sceMp3_0019.o 

#ifdef F_sceMp3_0000
	IMPORT_START	"sceMp3",0x00090011
#endif
#ifdef F_sceMp3_0001
	IMPORT_FUNC	"sceMp3",0x07EC321A,sceMp3ReserveMp3Handle
#endif
#ifdef F_sceMp3_0002
	IMPORT_FUNC	"sceMp3",0x0DB149F4,sceMp3NotifyAddStreamData
#endif
#ifdef F_sceMp3_0003
	IMPORT_FUNC	"sceMp3",0x2A368661,sceMp3ResetPlayPosition
#endif
#ifdef F_sceMp3_0004
	IMPORT_FUNC	"sceMp3",0x354D27EA,sceMp3GetSumDecodedSample
#endif
#ifdef F_sceMp3_0005
	IMPORT_FUNC	"sceMp3",0x35750070,sceMp3InitResource
#endif
#ifdef F_sceMp3_0006
	IMPORT_FUNC	"sceMp3",0x3C2FA058,sceMp3TermResource
#endif
#ifdef F_sceMp3_0007
	IMPORT_FUNC	"sceMp3",0x3CEF484F,sceMp3SetLoopNum
#endif
#ifdef F_sceMp3_0008
	IMPORT_FUNC	"sceMp3",0x44E07129,sceMp3Init
#endif
#ifdef F_sceMp3_0009
	IMPORT_FUNC	"sceMp3",0x732B042A,sceMp3_732B042A
#endif
#ifdef F_sceMp3_0010
	IMPORT_FUNC	"sceMp3",0x7F696782,sceMp3GetMp3ChannelNum
#endif
#ifdef F_sceMp3_0011
	IMPORT_FUNC	"sceMp3",0x87677E40,sceMp3GetBitRate
#endif
#ifdef F_sceMp3_0012
	IMPORT_FUNC	"sceMp3",0x87C263D1,sceMp3GetMaxOutputSample
#endif
#ifdef F_sceMp3_0013
	IMPORT_FUNC	"sceMp3",0x8AB81558,sceMp3_8AB81558
#endif
#ifdef F_sceMp3_0014
	IMPORT_FUNC	"sceMp3",0x8F450998,sceMp3GetSamplingRate
#endif
#ifdef F_sceMp3_0015
	IMPORT_FUNC	"sceMp3",0xA703FE0F,sceMp3GetInfoToAddStreamData
#endif
#ifdef F_sceMp3_0016
	IMPORT_FUNC	"sceMp3",0xD021C0FB,sceMp3Decode
#endif
#ifdef F_sceMp3_0017
	IMPORT_FUNC	"sceMp3",0xD0A56296,sceMp3CheckStreamDataNeeded
#endif
#ifdef F_sceMp3_0018
	IMPORT_FUNC	"sceMp3",0xD8F54A51,sceMp3GetLoopNum
#endif
#ifdef F_sceMp3_0019
	IMPORT_FUNC	"sceMp3",0xF5478233,sceMp3ReleaseMp3Handle
#endif
