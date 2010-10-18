	.set noreorder

#include "pspimport.s"

#ifdef F_sceWlanDrv_0000
	IMPORT_START	"sceWlanDrv",0x40010000
#endif
#ifdef F_sceWlanDrv_0001
	IMPORT_FUNC	"sceWlanDrv",0x93440B11,sceWlanDevIsPowerOn
#endif
#ifdef F_sceWlanDrv_0002
	IMPORT_FUNC	"sceWlanDrv",0xD7763699,sceWlanGetSwitchState
#endif
#ifdef F_sceWlanDrv_0003
	IMPORT_FUNC	"sceWlanDrv",0x0C622081,sceWlanGetEtherAddr
#endif
