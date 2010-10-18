	.set noreorder

#include "pspimport.s"

// Build List
// sceCtrl_driver_0000.o sceCtrl_driver_0001.o sceCtrl_driver_0002.o sceCtrl_driver_0003.o sceCtrl_driver_0004.o sceCtrl_driver_0005.o sceCtrl_driver_0006.o sceCtrl_driver_0007.o sceCtrl_driver_0008.o sceCtrl_driver_0009.o sceCtrl_driver_0010.o sceCtrl_driver_0011.o sceCtrl_driver_0012.o sceCtrl_driver_0013.o sceCtrl_driver_0014.o sceCtrl_driver_0015.o sceCtrl_driver_0016.o sceCtrl_driver_0017.o sceCtrl_driver_0018.o sceCtrl_driver_0019.o sceCtrl_driver_0020.o sceCtrl_driver_0021.o sceCtrl_driver_0022.o sceCtrl_driver_0023.o 

#ifdef F_sceCtrl_driver_0000
	IMPORT_START	"sceCtrl_driver",0x00010000
#endif
#ifdef F_sceCtrl_driver_0001
	IMPORT_FUNC	"sceCtrl_driver",0x3E65A0EA,sceCtrlInit
#endif
#ifdef F_sceCtrl_driver_0002
	IMPORT_FUNC	"sceCtrl_driver",0xE03956E9,sceCtrlEnd
#endif
#ifdef F_sceCtrl_driver_0003
	IMPORT_FUNC	"sceCtrl_driver",0xC3F607F3,sceCtrlSuspend
#endif
#ifdef F_sceCtrl_driver_0004
	IMPORT_FUNC	"sceCtrl_driver",0xC245B57B,sceCtrlResume
#endif
#ifdef F_sceCtrl_driver_0005
	IMPORT_FUNC	"sceCtrl_driver",0x6A2774F3,sceCtrlSetSamplingCycle
#endif
#ifdef F_sceCtrl_driver_0006
	IMPORT_FUNC	"sceCtrl_driver",0x02BAAD91,sceCtrlGetSamplingCycle
#endif
#ifdef F_sceCtrl_driver_0007
	IMPORT_FUNC	"sceCtrl_driver",0x1F4011E6,sceCtrlSetSamplingMode
#endif
#ifdef F_sceCtrl_driver_0008
	IMPORT_FUNC	"sceCtrl_driver",0xDA6B76A1,sceCtrlGetSamplingMode
#endif
#ifdef F_sceCtrl_driver_0009
	IMPORT_FUNC	"sceCtrl_driver",0x3A622550,sceCtrlPeekBufferPositive
#endif
#ifdef F_sceCtrl_driver_0010
	IMPORT_FUNC	"sceCtrl_driver",0xC152080A,sceCtrlPeekBufferNegative
#endif
#ifdef F_sceCtrl_driver_0011
	IMPORT_FUNC	"sceCtrl_driver",0x1F803938,sceCtrlReadBufferPositive
#endif
#ifdef F_sceCtrl_driver_0012
	IMPORT_FUNC	"sceCtrl_driver",0x60B81F86,sceCtrlReadBufferNegative
#endif
#ifdef F_sceCtrl_driver_0013
	IMPORT_FUNC	"sceCtrl_driver",0xB1D0E5CD,sceCtrlPeekLatch
#endif
#ifdef F_sceCtrl_driver_0014
	IMPORT_FUNC	"sceCtrl_driver",0x0B588501,sceCtrlReadLatch
#endif
#ifdef F_sceCtrl_driver_0015
	IMPORT_FUNC	"sceCtrl_driver",0xA88E8D22,sceCtrlSetIdleCancelKey
#endif
#ifdef F_sceCtrl_driver_0016
	IMPORT_FUNC	"sceCtrl_driver",0xB7CEAED4,sceCtrlGetIdleCancelKey
#endif
#ifdef F_sceCtrl_driver_0017
	IMPORT_FUNC	"sceCtrl_driver",0x348D99D4,sceCtrl_driver_348D99D4
#endif
#ifdef F_sceCtrl_driver_0018
	IMPORT_FUNC	"sceCtrl_driver",0xAF5960F3,sceCtrl_driver_AF5960F3
#endif
#ifdef F_sceCtrl_driver_0019
	IMPORT_FUNC	"sceCtrl_driver",0xA68FD260,sceCtrlClearRapidFire
#endif
#ifdef F_sceCtrl_driver_0020
	IMPORT_FUNC	"sceCtrl_driver",0x6841BE1A,sceCtrlSetRapidFire
#endif
#ifdef F_sceCtrl_driver_0021
	IMPORT_FUNC	"sceCtrl_driver",0x7CA723DC,sceCtrl_driver_7CA723DC
#endif
#ifdef F_sceCtrl_driver_0022
	IMPORT_FUNC	"sceCtrl_driver",0x5E77BC8A,sceCtrl_driver_5E77BC8A
#endif
#ifdef F_sceCtrl_driver_0023
	IMPORT_FUNC	"sceCtrl_driver",0x5C56C779,sceCtrl_driver_5C56C779
#endif
#ifdef F_sceCtrl_driver_0024
	IMPORT_FUNC	"sceCtrl_driver",0xA7144800,sceCtrlSetIdleCancelThreshold
#endif
#ifdef F_sceCtrl_driver_0025
	IMPORT_FUNC	"sceCtrl_driver",0x687660FA,sceCtrlGetIdleCancelThreshold
#endif
