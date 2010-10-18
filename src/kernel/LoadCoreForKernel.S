	.set noreorder

#include "pspimport.s"

#ifdef F_LoadCoreForKernel_0000
	IMPORT_START	"LoadCoreForKernel",0x00010000
#endif
#ifdef F_LoadCoreForKernel_0001
	IMPORT_FUNC	"LoadCoreForKernel",0xACE23476,sceKernelCheckPspConfig
#endif
#ifdef F_LoadCoreForKernel_0002
	IMPORT_FUNC	"LoadCoreForKernel",0x7BE1421C,sceKernelCheckExecFile
#endif
#ifdef F_LoadCoreForKernel_0003
	IMPORT_FUNC	"LoadCoreForKernel",0xBF983EF2,sceKernelProbeExecutableObject
#endif
#ifdef F_LoadCoreForKernel_0004
	IMPORT_FUNC	"LoadCoreForKernel",0x7068E6BA,sceKernelLoadExecutableObject
#endif
#ifdef F_LoadCoreForKernel_0005
	IMPORT_FUNC	"LoadCoreForKernel",0xB4D6FECC,sceKernelApplyElfRelSection
#endif
#ifdef F_LoadCoreForKernel_0006
	IMPORT_FUNC	"LoadCoreForKernel",0x54AB2675,sceKernelApplyPspRelSection
#endif
#ifdef F_LoadCoreForKernel_0007
	IMPORT_FUNC	"LoadCoreForKernel",0x2952F5AC,sceKernelDcacheWBinvAll
#endif
#ifdef F_LoadCoreForKernel_0008
	IMPORT_FUNC	"LoadCoreForKernel",0xD8779AC6,sceKernelIcacheClearAll
#endif
#ifdef F_LoadCoreForKernel_0009
	IMPORT_FUNC	"LoadCoreForKernel",0x99A695F0,sceKernelRegisterLibrary
#endif
#ifdef F_LoadCoreForKernel_0010
	IMPORT_FUNC	"LoadCoreForKernel",0x5873A31F,sceKernelRegisterLibraryForUser
#endif
#ifdef F_LoadCoreForKernel_0011
	IMPORT_FUNC	"LoadCoreForKernel",0x0B464512,sceKernelReleaseLibrary
#endif
#ifdef F_LoadCoreForKernel_0012
	IMPORT_FUNC	"LoadCoreForKernel",0x9BAF90F6,sceKernelCanReleaseLibrary
#endif
#ifdef F_LoadCoreForKernel_0013
	IMPORT_FUNC	"LoadCoreForKernel",0x0E760DBA,sceKernelLinkLibraryEntries
#endif
#ifdef F_LoadCoreForKernel_0014
	IMPORT_FUNC	"LoadCoreForKernel",0x0DE1F600,sceKernelLinkLibraryEntriesForUser
#endif
#ifdef F_LoadCoreForKernel_0015
	IMPORT_FUNC	"LoadCoreForKernel",0xDA1B09AA,sceKernelUnLinkLibraryEntries
#endif
#ifdef F_LoadCoreForKernel_0016
	IMPORT_FUNC	"LoadCoreForKernel",0xC99DD47A,sceKernelQueryLoadCoreCB
#endif
#ifdef F_LoadCoreForKernel_0017
	IMPORT_FUNC	"LoadCoreForKernel",0x616FCCCD,LoadCoreForKernel_616FCCCD
#endif
#ifdef F_LoadCoreForKernel_0018
	IMPORT_FUNC	"LoadCoreForKernel",0xF32A2940,sceKernelModuleFromUID
#endif
#ifdef F_LoadCoreForKernel_0019
	IMPORT_FUNC	"LoadCoreForKernel",0xCD0F3BAC,sceKernelCreateModule
#endif
#ifdef F_LoadCoreForKernel_0020
	IMPORT_FUNC	"LoadCoreForKernel",0x6B2371C2,sceKernelDeleteModule
#endif
#ifdef F_LoadCoreForKernel_0021
	IMPORT_FUNC	"LoadCoreForKernel",0x7320D964,sceKernelModuleAssign
#endif
#ifdef F_LoadCoreForKernel_0022
	IMPORT_FUNC	"LoadCoreForKernel",0x44B292AB,sceKernelAllocModule
#endif
#ifdef F_LoadCoreForKernel_0023
	IMPORT_FUNC	"LoadCoreForKernel",0xBD61D4D5,sceKernelFreeModule
#endif
#ifdef F_LoadCoreForKernel_0024
	IMPORT_FUNC	"LoadCoreForKernel",0xAE7C6E76,sceKernelRegisterModule
#endif
#ifdef F_LoadCoreForKernel_0025
	IMPORT_FUNC	"LoadCoreForKernel",0x74CF001A,sceKernelReleaseModule
#endif
#ifdef F_LoadCoreForKernel_0026
	IMPORT_FUNC	"LoadCoreForKernel",0xCF8A41B1,sceKernelFindModuleByName
#endif
#ifdef F_LoadCoreForKernel_0027
	IMPORT_FUNC	"LoadCoreForKernel",0xFB8AE27D,sceKernelFindModuleByAddress
#endif
#ifdef F_LoadCoreForKernel_0028
	IMPORT_FUNC	"LoadCoreForKernel",0xCCE4A157,sceKernelFindModuleByUID
#endif
#ifdef F_LoadCoreForKernel_0029
	IMPORT_FUNC	"LoadCoreForKernel",0x82CE54ED,sceKernelModuleCount
#endif
#ifdef F_LoadCoreForKernel_0030
	IMPORT_FUNC	"LoadCoreForKernel",0xC0584F0C,sceKernelGetModuleList
#endif
