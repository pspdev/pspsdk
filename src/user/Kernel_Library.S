	.set noreorder

#include "pspimport.s"

#ifdef F_Kernel_Library_0000
	IMPORT_START	"Kernel_Library",0x00010000
#endif
#ifdef F_Kernel_Library_0001
	IMPORT_FUNC	"Kernel_Library",0x092968F4,sceKernelCpuSuspendIntr
#endif
#ifdef F_Kernel_Library_0002
	IMPORT_FUNC	"Kernel_Library",0x5F10D406,sceKernelCpuResumeIntr
#endif
#ifdef F_Kernel_Library_0003
	IMPORT_FUNC	"Kernel_Library",0x3B84732D,sceKernelCpuResumeIntrWithSync
#endif
#ifdef F_Kernel_Library_0004
	IMPORT_FUNC	"Kernel_Library",0x47A0B729,sceKernelIsCpuIntrSuspended
#endif
#ifdef F_Kernel_Library_0005
	IMPORT_FUNC	"Kernel_Library",0xB55249D2,sceKernelIsCpuIntrEnable
#endif
#ifdef F_Kernel_Library_0006
	IMPORT_FUNC "Kernel_Library",0xBEA46419,sceKernelLockLwMutex
#endif
#ifdef F_Kernel_Library_0007
	IMPORT_FUNC "Kernel_Library",0x15B6446B,sceKernelUnlockLwMutex
#endif
#ifdef F_Kernel_Library_0008
	IMPORT_FUNC "Kernel_Library",0xDC692EE3,sceKernelTryLockLwMutex
#endif
