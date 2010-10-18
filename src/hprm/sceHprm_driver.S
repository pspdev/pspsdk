	.set noreorder

#include "pspimport.s"

#ifdef F_sceHprm_driver_0000
	IMPORT_START	"sceHprm_driver",0x00010000
#endif
#ifdef F_sceHprm_driver_0001
	IMPORT_FUNC	"sceHprm_driver",0x1C5BC5A0,sceHprmInit
#endif
#ifdef F_sceHprm_driver_0002
	IMPORT_FUNC	"sceHprm_driver",0x588845DA,sceHprmEnd
#endif
#ifdef F_sceHprm_driver_0003
	IMPORT_FUNC	"sceHprm_driver",0x526BB7F4,sceHprmSuspend
#endif
#ifdef F_sceHprm_driver_0004
	IMPORT_FUNC	"sceHprm_driver",0x2C7B8B05,sceHprmResume
#endif
#ifdef F_sceHprm_driver_0005
	IMPORT_FUNC	"sceHprm_driver",0xD22913DB,sceHprmSetConnectCallback
#endif
#ifdef F_sceHprm_driver_0006
	IMPORT_FUNC	"sceHprm_driver",0xC7154136,sceHprmRegisterCallback
#endif
#ifdef F_sceHprm_driver_0007
	IMPORT_FUNC	"sceHprm_driver",0x444ED0B7,sceHprmUnregisterCallback
#endif
#ifdef F_sceHprm_driver_0008
	IMPORT_FUNC	"sceHprm_driver",0x208DB1BD,sceHprmIsRemoteExist
#endif
#ifdef F_sceHprm_driver_0009
	IMPORT_FUNC	"sceHprm_driver",0x7E69EDA4,sceHprmIsHeadphoneExist
#endif
#ifdef F_sceHprm_driver_0010
	IMPORT_FUNC	"sceHprm_driver",0x219C58F1,sceHprmIsMicrophoneExist
#endif
#ifdef F_sceHprm_driver_0011
	IMPORT_FUNC	"sceHprm_driver",0x4D1E622C,sceHprmReset
#endif
#ifdef F_sceHprm_driver_0012
	IMPORT_FUNC	"sceHprm_driver",0x7B038374,sceHprmGetInternalState
#endif
#ifdef F_sceHprm_driver_0013
	IMPORT_FUNC	"sceHprm_driver",0xF04591FA,sceHprm_driver_F04591FA
#endif
#ifdef F_sceHprm_driver_0014
	IMPORT_FUNC	"sceHprm_driver",0x971AE8FB,sceHprm_driver_971AE8FB
#endif
#ifdef F_sceHprm_driver_0015
	IMPORT_FUNC	"sceHprm_driver",0xBAD0828E,sceHprmGetModel
#endif
#ifdef F_sceHprm_driver_0016
	IMPORT_FUNC	"sceHprm_driver",0x1910B327,sceHprmPeekCurrentKey
#endif
#ifdef F_sceHprm_driver_0017
	IMPORT_FUNC	"sceHprm_driver",0x2BCEC83E,sceHprmPeekLatch
#endif
#ifdef F_sceHprm_driver_0018
	IMPORT_FUNC	"sceHprm_driver",0x40D2F9F0,sceHprmReadLatch
#endif
