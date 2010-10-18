	.set noreorder

#include "pspimport.s"

#ifdef F_LoadExecForUser_0000
	IMPORT_START	"LoadExecForUser",0x40010000
#endif
#ifdef F_LoadExecForUser_0001
	IMPORT_FUNC	"LoadExecForUser",0xBD2F1094,sceKernelLoadExec
#endif
#ifdef F_LoadExecForUser_0002
	IMPORT_FUNC	"LoadExecForUser",0x2AC9954B,sceKernelExitGameWithStatus
#endif
#ifdef F_LoadExecForUser_0003
	IMPORT_FUNC	"LoadExecForUser",0x05572A5F,sceKernelExitGame
#endif
#ifdef F_LoadExecForUser_0004
	IMPORT_FUNC	"LoadExecForUser",0x4AC57943,sceKernelRegisterExitCallback
#endif
