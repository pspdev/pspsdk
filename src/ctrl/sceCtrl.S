	.set noreorder

#include "pspimport.s"

#ifdef F_sceCtrl_0000
	IMPORT_START	"sceCtrl",0x40010000
#endif
#ifdef F_sceCtrl_0001
	IMPORT_FUNC	"sceCtrl",0x6A2774F3,sceCtrlSetSamplingCycle
#endif
#ifdef F_sceCtrl_0002
	IMPORT_FUNC	"sceCtrl",0x02BAAD91,sceCtrlGetSamplingCycle
#endif
#ifdef F_sceCtrl_0003
	IMPORT_FUNC	"sceCtrl",0x1F4011E6,sceCtrlSetSamplingMode
#endif
#ifdef F_sceCtrl_0004
	IMPORT_FUNC	"sceCtrl",0xDA6B76A1,sceCtrlGetSamplingMode
#endif
#ifdef F_sceCtrl_0005
	IMPORT_FUNC	"sceCtrl",0x3A622550,sceCtrlPeekBufferPositive
#endif
#ifdef F_sceCtrl_0006
	IMPORT_FUNC	"sceCtrl",0xC152080A,sceCtrlPeekBufferNegative
#endif
#ifdef F_sceCtrl_0007
	IMPORT_FUNC	"sceCtrl",0x1F803938,sceCtrlReadBufferPositive
#endif
#ifdef F_sceCtrl_0008
	IMPORT_FUNC	"sceCtrl",0x60B81F86,sceCtrlReadBufferNegative
#endif
#ifdef F_sceCtrl_0009
	IMPORT_FUNC	"sceCtrl",0xB1D0E5CD,sceCtrlPeekLatch
#endif
#ifdef F_sceCtrl_0010
	IMPORT_FUNC	"sceCtrl",0x0B588501,sceCtrlReadLatch
#endif
#ifdef F_sceCtrl_0011
	IMPORT_FUNC	"sceCtrl",0x348D99D4,sceCtrl_348D99D4
#endif
#ifdef F_sceCtrl_0012
	IMPORT_FUNC	"sceCtrl",0xAF5960F3,sceCtrl_AF5960F3
#endif
#ifdef F_sceCtrl_0013
	IMPORT_FUNC	"sceCtrl",0xA68FD260,sceCtrlClearRapidFire
#endif
#ifdef F_sceCtrl_0014
	IMPORT_FUNC	"sceCtrl",0x6841BE1A,sceCtrlSetRapidFire
#endif
#ifdef F_sceCtrl_0015
	IMPORT_FUNC	"sceCtrl",0xA7144800,sceCtrlSetIdleCancelThreshold
#endif
#ifdef F_sceCtrl_0016
	IMPORT_FUNC	"sceCtrl",0x687660FA,sceCtrlGetIdleCancelThreshold
#endif
