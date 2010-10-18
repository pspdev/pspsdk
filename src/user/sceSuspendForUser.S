	.set noreorder

#include "pspimport.s"

#ifdef F_sceSuspendForUser_0000
	IMPORT_START	"sceSuspendForUser",0x40000000
#endif
#ifdef F_sceSuspendForUser_0001
	IMPORT_FUNC	"sceSuspendForUser",0xEADB1BD7,sceKernelPowerLock
#endif
#ifdef F_sceSuspendForUser_0002
	IMPORT_FUNC	"sceSuspendForUser",0x3AEE7261,sceKernelPowerUnlock
#endif
#ifdef F_sceSuspendForUser_0003
	IMPORT_FUNC	"sceSuspendForUser",0x090CCB3F,sceKernelPowerTick
#endif
#ifdef F_sceSuspendForUser_0004
	IMPORT_FUNC	"sceSuspendForUser",0x3E0271D3,sceKernelVolatileMemLock
#endif
#ifdef F_sceSuspendForUser_0005
	IMPORT_FUNC	"sceSuspendForUser",0xA14F40B2,sceKernelVolatileMemTryLock
#endif
#ifdef F_sceSuspendForUser_0006
	IMPORT_FUNC	"sceSuspendForUser",0xA569E425,sceKernelVolatileMemUnlock
#endif
