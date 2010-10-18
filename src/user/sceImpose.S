	.set noreorder

#include "pspimport.s"

#ifdef F_sceImpose_0000
	IMPORT_START	"sceImpose",0x40010011
#endif
#ifdef F_sceImpose_0001
	IMPORT_FUNC	"sceImpose",0x0F341BE4,sceImposeGetHomePopup
#endif
#ifdef F_sceImpose_0002
	IMPORT_FUNC	"sceImpose",0x24FD7BCF,sceImposeGetLanguageMode
#endif
#ifdef F_sceImpose_0003
	IMPORT_FUNC	"sceImpose",0x36AA6E91,sceImposeSetLanguageMode
#endif
#ifdef F_sceImpose_0004
	IMPORT_FUNC	"sceImpose",0x381BD9E7,sceImposeHomeButton
#endif
#ifdef F_sceImpose_0005
	IMPORT_FUNC	"sceImpose",0x5595A71A,sceImposeSetHomePopup
#endif
#ifdef F_sceImpose_0006
	IMPORT_FUNC	"sceImpose",0x72189C48,sceImposeSetUMDPopup
#endif
#ifdef F_sceImpose_0007
	IMPORT_FUNC	"sceImpose",0x8C943191,sceImposeBatteryIconStatus
#endif
#ifdef F_sceImpose_0008
	IMPORT_FUNC	"sceImpose",0x8F6E3518,sceImposeGetBacklightOffTime
#endif
#ifdef F_sceImpose_0009
	IMPORT_FUNC	"sceImpose",0x967F6D4A,sceImposeSetBacklightOffTime
#endif
#ifdef F_sceImpose_0010
	IMPORT_FUNC	"sceImpose",0x9BA61B49,sceImpose_9BA61B49
#endif
#ifdef F_sceImpose_0011
	IMPORT_FUNC	"sceImpose",0xA9884B00,sceImpose_A9884B00
#endif
#ifdef F_sceImpose_0012
	IMPORT_FUNC	"sceImpose",0xBB3F5DEC,sceImpose_BB3F5DEC
#endif
#ifdef F_sceImpose_0013
	IMPORT_FUNC	"sceImpose",0xE0887BC8,sceImposeGetUMDPopup
#endif
#ifdef F_sceImpose_0014
	IMPORT_FUNC	"sceImpose",0xFCD44963,sceImpose_FCD44963
#endif
#ifdef F_sceImpose_0015
	IMPORT_FUNC	"sceImpose",0xFF1A2F07,sceImpose_FF1A2F07
#endif
