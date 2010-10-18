	.set noreorder

#include "pspimport.s"

#ifdef F_ModuleMgrForUser_0000
	IMPORT_START	"ModuleMgrForUser",0x40010000
#endif
#ifdef F_ModuleMgrForUser_0001
	IMPORT_FUNC	"ModuleMgrForUser",0xB7F46618,sceKernelLoadModuleByID
#endif
#ifdef F_ModuleMgrForUser_0002
	IMPORT_FUNC	"ModuleMgrForUser",0x977DE386,sceKernelLoadModule
#endif
#ifdef F_ModuleMgrForUser_0003
	IMPORT_FUNC	"ModuleMgrForUser",0x710F61B5,sceKernelLoadModuleMs
#endif
#ifdef F_ModuleMgrForUser_0004
	IMPORT_FUNC	"ModuleMgrForUser",0xF9275D98,sceKernelLoadModuleBufferUsbWlan
#endif
#ifdef F_ModuleMgrForUser_0005
	IMPORT_FUNC	"ModuleMgrForUser",0x50F0C1EC,sceKernelStartModule
#endif
#ifdef F_ModuleMgrForUser_0006
	IMPORT_FUNC	"ModuleMgrForUser",0xD1FF982A,sceKernelStopModule
#endif
#ifdef F_ModuleMgrForUser_0007
	IMPORT_FUNC	"ModuleMgrForUser",0x2E0911AA,sceKernelUnloadModule
#endif
#ifdef F_ModuleMgrForUser_0008
	IMPORT_FUNC	"ModuleMgrForUser",0xD675EBB8,sceKernelSelfStopUnloadModule
#endif
#ifdef F_ModuleMgrForUser_0009
	IMPORT_FUNC	"ModuleMgrForUser",0xCC1D3699,sceKernelStopUnloadSelfModule
#endif
#ifdef F_ModuleMgrForUser_0010
	IMPORT_FUNC	"ModuleMgrForUser",0x748CBED9,sceKernelQueryModuleInfo
#endif
#ifdef F_ModuleMgrForUser_0011
	IMPORT_FUNC "ModuleMgrForUser", 0x644395E2,sceKernelGetModuleIdList
#endif
