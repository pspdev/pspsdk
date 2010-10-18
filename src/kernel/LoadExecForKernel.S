	.set noreorder

#include "pspimport.s"

#ifdef F_LoadExecForKernel_0000
	IMPORT_START	"LoadExecForKernel",0x00010000
#endif
#ifdef F_LoadExecForKernel_0001
	IMPORT_FUNC	"LoadExecForKernel",0xBD2F1094,sceKernelLoadExec
#endif
#ifdef F_LoadExecForKernel_0002
	IMPORT_FUNC	"LoadExecForKernel",0x2AC9954B,sceKernelExitGameWithStatus
#endif
#ifdef F_LoadExecForKernel_0003
	IMPORT_FUNC	"LoadExecForKernel",0x05572A5F,sceKernelExitGame
#endif
#ifdef F_LoadExecForKernel_0004
	IMPORT_FUNC	"LoadExecForKernel",0xAC085B9E,sceKernelLoadExecVSHFromHost
#endif
#ifdef F_LoadExecForKernel_0005
	IMPORT_FUNC	"LoadExecForKernel",0x1B97BDB3,sceKernelLoadExecVSHDisc
#endif
#ifdef F_LoadExecForKernel_0006
	IMPORT_FUNC	"LoadExecForKernel",0x821BE114,sceKernelLoadExecVSHDiscUpdater
#endif
#ifdef F_LoadExecForKernel_0007
	IMPORT_FUNC	"LoadExecForKernel",0x015DA036,sceKernelLoadExecBufferVSHUsbWlan
#endif
#ifdef F_LoadExecForKernel_0008
	IMPORT_FUNC	"LoadExecForKernel",0x4F41E75E,sceKernelLoadExecBufferVSHUsbWlanDebug
#endif
#ifdef F_LoadExecForKernel_0009
	IMPORT_FUNC	"LoadExecForKernel",0x31DF42BF,sceKernelLoadExecVSHMs1
#endif
#ifdef F_LoadExecForKernel_0010
	IMPORT_FUNC	"LoadExecForKernel",0x28D0D249,sceKernelLoadExecVSHMs2
#endif
#ifdef F_LoadExecForKernel_0011
	IMPORT_FUNC	"LoadExecForKernel",0x70901231,sceKernelLoadExecVSHMs3
#endif
#ifdef F_LoadExecForKernel_0012
	IMPORT_FUNC	"LoadExecForKernel",0xA3D5E142,sceKernelExitVSHVSH
#endif
#ifdef F_LoadExecForKernel_0013
	IMPORT_FUNC	"LoadExecForKernel",0x62C459E1,sceKernelLoadExecBufferVSHPlain
#endif
#ifdef F_LoadExecForKernel_0014
	IMPORT_FUNC	"LoadExecForKernel",0x918782E8,sceKernelLoadExecBufferVSHFromHost
#endif
#ifdef F_LoadExecForKernel_0015
	IMPORT_FUNC	"LoadExecForKernel",0xBB28E9B7,sceKernelLoadExecBufferPlain0
#endif
#ifdef F_LoadExecForKernel_0016
	IMPORT_FUNC	"LoadExecForKernel",0x71A1D738,sceKernelLoadExecBufferPlain
#endif
#ifdef F_LoadExecForKernel_0017
	IMPORT_FUNC	"LoadExecForKernel",0x4D5C75BE,sceKernelLoadExecFromHost
#endif
#ifdef F_LoadExecForKernel_0018
	IMPORT_FUNC	"LoadExecForKernel",0x4AC57943,sceKernelRegisterExitCallback
#endif
#ifdef F_LoadExecForKernel_0019
	IMPORT_FUNC	"LoadExecForKernel",0xD9739B89,sceKernelUnregisterExitCallback
#endif
#ifdef F_LoadExecForKernel_0020
	IMPORT_FUNC	"LoadExecForKernel",0x659188E1,sceKernelCheckExitCallback
#endif
#ifdef F_LoadExecForKernel_0021
	IMPORT_FUNC	"LoadExecForKernel",0x62A27008,sceKernelInvokeExitCallback
#endif
#ifdef F_LoadExecForKernel_0022
	IMPORT_FUNC	"LoadExecForKernel",0x7B7C47EF,sceKernelLoadExecVSHDiscDebug
#endif
#ifdef F_LoadExecForKernel_0023
	IMPORT_FUNC	"LoadExecForKernel",0x061D9514,sceKernelLoadExecVSHMs4
#endif
#ifdef F_LoadExecForKernel_0024
	IMPORT_FUNC	"LoadExecForKernel",0xB7AB08DA,sceKernelLoadExecVSHMs5
#endif
#ifdef F_LoadExecForKernel_0025
	IMPORT_FUNC	"LoadExecForKernel",0x6D302D3D,sceKernelExitVSHKernel
#endif
#ifdef F_LoadExecForKernel_0026
	IMPORT_FUNC	"LoadExecForKernel",0x11412288,LoadExecForKernel_11412288
#endif
