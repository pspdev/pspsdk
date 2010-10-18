	.set noreorder

#include "pspimport.s"

#ifdef F_SysMemUserForUser_0000
	IMPORT_START	"SysMemUserForUser",0x40000000
#endif
#ifdef F_SysMemUserForUser_0001
	IMPORT_FUNC	"SysMemUserForUser",0xA291F107,sceKernelMaxFreeMemSize
#endif
#ifdef F_SysMemUserForUser_0002
	IMPORT_FUNC	"SysMemUserForUser",0xF919F628,sceKernelTotalFreeMemSize
#endif
#ifdef F_SysMemUserForUser_0003
	IMPORT_FUNC	"SysMemUserForUser",0x237DBD4F,sceKernelAllocPartitionMemory
#endif
#ifdef F_SysMemUserForUser_0004
	IMPORT_FUNC	"SysMemUserForUser",0xB6D61D02,sceKernelFreePartitionMemory
#endif
#ifdef F_SysMemUserForUser_0005
	IMPORT_FUNC	"SysMemUserForUser",0x9D9A5BA1,sceKernelGetBlockHeadAddr
#endif
#ifdef F_SysMemUserForUser_0006
	IMPORT_FUNC	"SysMemUserForUser",0x3FC9AE6A,sceKernelDevkitVersion
#endif
#ifdef F_SysMemUserForUser_0007
	IMPORT_FUNC	"SysMemUserForUser",0x13A5ABEF,sceKernelPrintf
#endif
