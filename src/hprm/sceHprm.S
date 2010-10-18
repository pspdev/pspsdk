	.set noreorder

#include "pspimport.s"

#ifdef F_sceHprm_0000
	IMPORT_START	"sceHprm",0x40010000
#endif
#ifdef F_sceHprm_0001
	IMPORT_FUNC	"sceHprm",0xC7154136,sceHprmRegisterCallback
#endif
#ifdef F_sceHprm_0002
	IMPORT_FUNC	"sceHprm",0x444ED0B7,sceHprmUnregisterCallback
#endif
#ifdef F_sceHprm_0003
	IMPORT_FUNC	"sceHprm",0x208DB1BD,sceHprmIsRemoteExist
#endif
#ifdef F_sceHprm_0004
	IMPORT_FUNC	"sceHprm",0x7E69EDA4,sceHprmIsHeadphoneExist
#endif
#ifdef F_sceHprm_0005
	IMPORT_FUNC	"sceHprm",0x219C58F1,sceHprmIsMicrophoneExist
#endif
#ifdef F_sceHprm_0006
	IMPORT_FUNC	"sceHprm",0x1910B327,sceHprmPeekCurrentKey
#endif
#ifdef F_sceHprm_0007
	IMPORT_FUNC	"sceHprm",0x2BCEC83E,sceHprmPeekLatch
#endif
#ifdef F_sceHprm_0008
	IMPORT_FUNC	"sceHprm",0x40D2F9F0,sceHprmReadLatch
#endif
