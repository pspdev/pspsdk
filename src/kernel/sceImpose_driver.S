	.set noreorder

#include "pspimport.s"

#ifdef F_sceImpose_driver_0000
	IMPORT_START	"sceImpose_driver",0x00010011
#endif
#ifdef F_sceImpose_driver_0001
	IMPORT_FUNC	"sceImpose_driver",0x0F341BE4,sceImposeGetHomePopup
#endif
#ifdef F_sceImpose_driver_0002
	IMPORT_FUNC	"sceImpose_driver",0x116CFF64,sceImposeCheckVideoOut
#endif
#ifdef F_sceImpose_driver_0003
	IMPORT_FUNC	"sceImpose_driver",0x116DDED6,sceImposeSetVideoOutMode
#endif
#ifdef F_sceImpose_driver_0004
	IMPORT_FUNC	"sceImpose_driver",0x1AEED8FE,sceImposeSuspend
#endif
#ifdef F_sceImpose_driver_0005
	IMPORT_FUNC	"sceImpose_driver",0x1B6E3400,sceImposeGetStatus
#endif
#ifdef F_sceImpose_driver_0006
	IMPORT_FUNC	"sceImpose_driver",0x24FD7BCF,sceImposeGetLanguageMode
#endif
#ifdef F_sceImpose_driver_0007
	IMPORT_FUNC	"sceImpose_driver",0x36AA6E91,sceImposeSetLanguageMode
#endif
#ifdef F_sceImpose_driver_0008
	IMPORT_FUNC	"sceImpose_driver",0x381BD9E7,sceImposeHomeButton
#endif
#ifdef F_sceImpose_driver_0009
	IMPORT_FUNC	"sceImpose_driver",0x531C9778,sceImposeGetParam
#endif
#ifdef F_sceImpose_driver_0010
	IMPORT_FUNC	"sceImpose_driver",0x5595A71A,sceImposeSetHomePopup
#endif
#ifdef F_sceImpose_driver_0011
	IMPORT_FUNC	"sceImpose_driver",0x7084E72C,sceImpose_driver_7084E72C
#endif
#ifdef F_sceImpose_driver_0012
	IMPORT_FUNC	"sceImpose_driver",0x72189C48,sceImposeSetUMDPopup
#endif
#ifdef F_sceImpose_driver_0013
	IMPORT_FUNC	"sceImpose_driver",0x810FB7FB,sceImposeSetParam
#endif
#ifdef F_sceImpose_driver_0014
	IMPORT_FUNC	"sceImpose_driver",0x86924032,sceImposeResume
#endif
#ifdef F_sceImpose_driver_0015
	IMPORT_FUNC	"sceImpose_driver",0x8C943191,sceImposeGetBatteryIconStatus
#endif
#ifdef F_sceImpose_driver_0016
	IMPORT_FUNC	"sceImpose_driver",0x8F6E3518,sceImposeGetBacklightOffTime
#endif
#ifdef F_sceImpose_driver_0017
	IMPORT_FUNC	"sceImpose_driver",0x967F6D4A,sceImposeSetBacklightOffTime
#endif
#ifdef F_sceImpose_driver_0018
	IMPORT_FUNC	"sceImpose_driver",0x9C8C6C81,sceImposeSetStatus
#endif
#ifdef F_sceImpose_driver_0019
	IMPORT_FUNC	"sceImpose_driver",0x9DBCE0C4,sceImpose_driver_9DBCE0C4
#endif
#ifdef F_sceImpose_driver_0020
	IMPORT_FUNC	"sceImpose_driver",0xB415FC59,sceImposeChanges
#endif
#ifdef F_sceImpose_driver_0021
	IMPORT_FUNC	"sceImpose_driver",0xBDBC42A6,sceImposeInit
#endif
#ifdef F_sceImpose_driver_0022
	IMPORT_FUNC	"sceImpose_driver",0xC7E36CC7,sceImposeEnd
#endif
#ifdef F_sceImpose_driver_0023
	IMPORT_FUNC	"sceImpose_driver",0xE0887BC8,sceImposeGetUMDPopup
#endif
