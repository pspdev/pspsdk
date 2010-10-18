	.set noreorder

#include "pspimport.s"

#ifdef F_ModuleMgrForKernel_0000
	IMPORT_START	"ModuleMgrForKernel",0x00010000
#endif
#ifdef F_ModuleMgrForKernel_0001
	IMPORT_FUNC	"ModuleMgrForKernel",0xABE84F8A,sceKernelLoadModuleBufferWithApitype
#endif
#ifdef F_ModuleMgrForKernel_0002
	IMPORT_FUNC	"ModuleMgrForKernel",0xBA889C07,sceKernelLoadModuleBuffer
#endif
#ifdef F_ModuleMgrForKernel_0003
	IMPORT_FUNC	"ModuleMgrForKernel",0xB7F46618,sceKernelLoadModuleByID
#endif
#ifdef F_ModuleMgrForKernel_0004
	IMPORT_FUNC	"ModuleMgrForKernel",0x437214AE,sceKernelLoadModuleWithApitype
#endif
#ifdef F_ModuleMgrForKernel_0005
	IMPORT_FUNC	"ModuleMgrForKernel",0x977DE386,sceKernelLoadModule
#endif
#ifdef F_ModuleMgrForKernel_0006
	IMPORT_FUNC	"ModuleMgrForKernel",0x710F61B5,sceKernelLoadModuleMs
#endif
#ifdef F_ModuleMgrForKernel_0007
	IMPORT_FUNC	"ModuleMgrForKernel",0x91B87FAE,sceKernelLoadModuleVSHByID
#endif
#ifdef F_ModuleMgrForKernel_0008
	IMPORT_FUNC	"ModuleMgrForKernel",0xA4370E7C,sceKernelLoadModuleVSH
#endif
#ifdef F_ModuleMgrForKernel_0009
	IMPORT_FUNC	"ModuleMgrForKernel",0x23425E93,sceKernelLoadModuleVSHPlain
#endif
#ifdef F_ModuleMgrForKernel_0010
	IMPORT_FUNC	"ModuleMgrForKernel",0xF9275D98,sceKernelLoadModuleBufferUsbWlan
#endif
#ifdef F_ModuleMgrForKernel_0011
	IMPORT_FUNC	"ModuleMgrForKernel",0xF0CAC59E,sceKernelLoadModuleBufferVSH
#endif
#ifdef F_ModuleMgrForKernel_0012
	IMPORT_FUNC	"ModuleMgrForKernel",0x50F0C1EC,sceKernelStartModule
#endif
#ifdef F_ModuleMgrForKernel_0013
	IMPORT_FUNC	"ModuleMgrForKernel",0xD1FF982A,sceKernelStopModule
#endif
#ifdef F_ModuleMgrForKernel_0014
	IMPORT_FUNC	"ModuleMgrForKernel",0x2E0911AA,sceKernelUnloadModule
#endif
#ifdef F_ModuleMgrForKernel_0015
	IMPORT_FUNC	"ModuleMgrForKernel",0xD675EBB8,sceKernelSelfStopUnloadModule
#endif
#ifdef F_ModuleMgrForKernel_0016
	IMPORT_FUNC	"ModuleMgrForKernel",0xCC1D3699,sceKernelStopUnloadSelfModule
#endif
#ifdef F_ModuleMgrForKernel_0017
	IMPORT_FUNC	"ModuleMgrForKernel",0x04B7BD22,sceKernelSearchModuleByName
#endif
#ifdef F_ModuleMgrForKernel_0018
	IMPORT_FUNC	"ModuleMgrForKernel",0x54D9E02E,sceKernelSearchModuleByAddress
#endif
#ifdef F_ModuleMgrForKernel_0019
	IMPORT_FUNC	"ModuleMgrForKernel",0x748CBED9,sceKernelQueryModuleInfo
#endif
#ifdef F_ModuleMgrForKernel_0020
	IMPORT_FUNC	"ModuleMgrForKernel",0x5F0CC575,sceKernelRebootBeforeForUser
#endif
#ifdef F_ModuleMgrForKernel_0021
	IMPORT_FUNC	"ModuleMgrForKernel",0xB49FFB9E,sceKernelRebootBeforeForKernel
#endif
#ifdef F_ModuleMgrForKernel_0022
	IMPORT_FUNC	"ModuleMgrForKernel",0x644395E2,sceKernelGetModuleIdList
#endif
