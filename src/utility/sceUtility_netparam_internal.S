	.set noreorder

#include "pspimport.s"

#ifdef F_sceUtility_netparam_internal_0000
	IMPORT_START	"sceUtility_netparam_internal",0x40010000
#endif
#ifdef F_sceUtility_netparam_internal_0001
	IMPORT_FUNC	"sceUtility_netparam_internal",0x072DEBF2,sceUtilityCreateNetParam
#endif
#ifdef F_sceUtility_netparam_internal_0002
	IMPORT_FUNC	"sceUtility_netparam_internal",0x9CE50172,sceUtilityDeleteNetParam
#endif
#ifdef F_sceUtility_netparam_internal_0003
	IMPORT_FUNC	"sceUtility_netparam_internal",0xFB0C4840,sceUtilityCopyNetParam
#endif
#ifdef F_sceUtility_netparam_internal_0004
	IMPORT_FUNC	"sceUtility_netparam_internal",0xFC4516F3,sceUtilitySetNetParam
#endif
