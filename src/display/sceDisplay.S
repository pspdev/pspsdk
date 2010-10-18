	.set noreorder

#include "pspimport.s"

#ifdef F_sceDisplay_0000
	IMPORT_START	"sceDisplay",0x40010000
#endif
#ifdef F_sceDisplay_0001
	IMPORT_FUNC	"sceDisplay",0x0E20F177,sceDisplaySetMode
#endif
#ifdef F_sceDisplay_0002
	IMPORT_FUNC	"sceDisplay",0xDEA197D4,sceDisplayGetMode
#endif
#ifdef F_sceDisplay_0003
	IMPORT_FUNC	"sceDisplay",0xDBA6C4C4,sceDisplayGetFramePerSec
#endif
#ifdef F_sceDisplay_0004
	IMPORT_FUNC	"sceDisplay",0x7ED59BC4,sceDisplaySetHoldMode
#endif
#ifdef F_sceDisplay_0005
	IMPORT_FUNC	"sceDisplay",0xA544C486,sceDisplaySetResumeMode
#endif
#ifdef F_sceDisplay_0006
	IMPORT_FUNC	"sceDisplay",0x289D82FE,sceDisplaySetFrameBuf
#endif
#ifdef F_sceDisplay_0007
	IMPORT_FUNC	"sceDisplay",0xEEDA2E54,sceDisplayGetFrameBuf
#endif
#ifdef F_sceDisplay_0008
	IMPORT_FUNC	"sceDisplay",0xB4F378FA,sceDisplayIsForeground
#endif
#ifdef F_sceDisplay_0009
	IMPORT_FUNC	"sceDisplay",0x31C4BAA8,sceDisplay_31C4BAA8
#endif
#ifdef F_sceDisplay_0010
	IMPORT_FUNC	"sceDisplay",0x9C6EAAD7,sceDisplayGetVcount
#endif
#ifdef F_sceDisplay_0011
	IMPORT_FUNC	"sceDisplay",0x4D4E10EC,sceDisplayIsVblank
#endif
#ifdef F_sceDisplay_0012
	IMPORT_FUNC	"sceDisplay",0x36CDFADE,sceDisplayWaitVblank
#endif
#ifdef F_sceDisplay_0013
	IMPORT_FUNC	"sceDisplay",0x8EB9EC49,sceDisplayWaitVblankCB
#endif
#ifdef F_sceDisplay_0014
	IMPORT_FUNC	"sceDisplay",0x984C27E7,sceDisplayWaitVblankStart
#endif
#ifdef F_sceDisplay_0015
	IMPORT_FUNC	"sceDisplay",0x46F186C3,sceDisplayWaitVblankStartCB
#endif
#ifdef F_sceDisplay_0016
	IMPORT_FUNC	"sceDisplay",0x773DD3A3,sceDisplayGetCurrentHcount
#endif
#ifdef F_sceDisplay_0017
	IMPORT_FUNC	"sceDisplay",0x210EAB3A,sceDisplayGetAccumulatedHcount
#endif
