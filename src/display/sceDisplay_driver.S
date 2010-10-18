	.set noreorder

#include "pspimport.s"

#ifdef F_sceDisplay_driver_0000
	IMPORT_START	"sceDisplay_driver",0x00010000
#endif
#ifdef F_sceDisplay_driver_0001
	IMPORT_FUNC	"sceDisplay_driver",0x206276C2,sceDisplayInit
#endif
#ifdef F_sceDisplay_driver_0002
	IMPORT_FUNC	"sceDisplay_driver",0x7A10289D,sceDisplayEnd
#endif
#ifdef F_sceDisplay_driver_0003
	IMPORT_FUNC	"sceDisplay_driver",0x0E20F177,sceDisplaySetMode
#endif
#ifdef F_sceDisplay_driver_0004
	IMPORT_FUNC	"sceDisplay_driver",0xDEA197D4,sceDisplayGetMode
#endif
#ifdef F_sceDisplay_driver_0005
	IMPORT_FUNC	"sceDisplay_driver",0xDBA6C4C4,sceDisplayGetFramePerSec
#endif
#ifdef F_sceDisplay_driver_0006
	IMPORT_FUNC	"sceDisplay_driver",0x432D133F,sceDisplayEnable
#endif
#ifdef F_sceDisplay_driver_0007
	IMPORT_FUNC	"sceDisplay_driver",0x681EE6A7,sceDisplayDisable
#endif
#ifdef F_sceDisplay_driver_0008
	IMPORT_FUNC	"sceDisplay_driver",0x7ED59BC4,sceDisplaySetHoldMode
#endif
#ifdef F_sceDisplay_driver_0009
	IMPORT_FUNC	"sceDisplay_driver",0xA544C486,sceDisplaySetResumeMode
#endif
#ifdef F_sceDisplay_driver_0010
	IMPORT_FUNC	"sceDisplay_driver",0x63E22A26,sceDisplay_driver_63E22A26
#endif
#ifdef F_sceDisplay_driver_0011
	IMPORT_FUNC	"sceDisplay_driver",0x5B5AEFAD,sceDisplay_driver_5B5AEFAD
#endif
#ifdef F_sceDisplay_driver_0012
	IMPORT_FUNC	"sceDisplay_driver",0x289D82FE,sceDisplaySetFrameBuf
#endif
#ifdef F_sceDisplay_driver_0013
	IMPORT_FUNC	"sceDisplay_driver",0xEEDA2E54,sceDisplayGetFrameBuf
#endif
#ifdef F_sceDisplay_driver_0014
	IMPORT_FUNC	"sceDisplay_driver",0xB4F378FA,sceDisplayIsForeground
#endif
#ifdef F_sceDisplay_driver_0015
	IMPORT_FUNC	"sceDisplay_driver",0xAC14F1FF,sceDisplayGetForegroundLevel
#endif
#ifdef F_sceDisplay_driver_0016
	IMPORT_FUNC	"sceDisplay_driver",0x9E3C6DC6,sceDisplaySetBrightness
#endif
#ifdef F_sceDisplay_driver_0017
	IMPORT_FUNC	"sceDisplay_driver",0x31C4BAA8,sceDisplayGetBrightness
#endif
#ifdef F_sceDisplay_driver_0018
	IMPORT_FUNC	"sceDisplay_driver",0x9C6EAAD7,sceDisplayGetVcount
#endif
#ifdef F_sceDisplay_driver_0019
	IMPORT_FUNC	"sceDisplay_driver",0x4D4E10EC,sceDisplayIsVblank
#endif
#ifdef F_sceDisplay_driver_0020
	IMPORT_FUNC	"sceDisplay_driver",0x69B53541,sceDisplayGetVblankRest
#endif
#ifdef F_sceDisplay_driver_0021
	IMPORT_FUNC	"sceDisplay_driver",0x36CDFADE,sceDisplayWaitVblank
#endif
#ifdef F_sceDisplay_driver_0022
	IMPORT_FUNC	"sceDisplay_driver",0x8EB9EC49,sceDisplayWaitVblankCB
#endif
#ifdef F_sceDisplay_driver_0023
	IMPORT_FUNC	"sceDisplay_driver",0x984C27E7,sceDisplayWaitVblankStart
#endif
#ifdef F_sceDisplay_driver_0024
	IMPORT_FUNC	"sceDisplay_driver",0x46F186C3,sceDisplayWaitVblankStartCB
#endif
#ifdef F_sceDisplay_driver_0025
	IMPORT_FUNC	"sceDisplay_driver",0x773DD3A3,sceDisplayGetCurrentHcount
#endif
#ifdef F_sceDisplay_driver_0026
	IMPORT_FUNC	"sceDisplay_driver",0x210EAB3A,sceDisplayGetAccumulatedHcount
#endif
