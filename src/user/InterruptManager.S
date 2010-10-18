	.set noreorder

#include "pspimport.s"

#ifdef F_InterruptManager_0000
	IMPORT_START	"InterruptManager",0x40000000
#endif
#ifdef F_InterruptManager_0001
	IMPORT_FUNC	"InterruptManager",0xCA04A2B9,sceKernelRegisterSubIntrHandler
#endif
#ifdef F_InterruptManager_0002
	IMPORT_FUNC	"InterruptManager",0xD61E6961,sceKernelReleaseSubIntrHandler
#endif
#ifdef F_InterruptManager_0003
	IMPORT_FUNC	"InterruptManager",0xFB8E22EC,sceKernelEnableSubIntr
#endif
#ifdef F_InterruptManager_0004
	IMPORT_FUNC	"InterruptManager",0x8A389411,sceKernelDisableSubIntr
#endif
#ifdef F_InterruptManager_0005
	IMPORT_FUNC	"InterruptManager",0x5CB5A78B,sceKernelSuspendSubIntr
#endif
#ifdef F_InterruptManager_0006
	IMPORT_FUNC	"InterruptManager",0x7860E0DC,sceKernelResumeSubIntr
#endif
#ifdef F_InterruptManager_0007
	IMPORT_FUNC	"InterruptManager",0xFC4374B8,sceKernelIsSubInterruptOccurred
#endif
#ifdef F_InterruptManager_0008
	IMPORT_FUNC	"InterruptManager",0xD2E8363F,QueryIntrHandlerInfo
#endif
#ifdef F_InterruptManager_0009
	IMPORT_FUNC	"InterruptManager",0xEEE43F47,sceKernelRegisterUserSpaceIntrStack
#endif
