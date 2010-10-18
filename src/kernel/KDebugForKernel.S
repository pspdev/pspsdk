	.set noreorder

#include "pspimport.s"

#ifdef F_KDebugForKernel_0000
	IMPORT_START	"KDebugForKernel",0x00010000
#endif
#ifdef F_KDebugForKernel_0001
	IMPORT_FUNC	"KDebugForKernel",0xE7A3874D,sceKernelRegisterAssertHandler
#endif
#ifdef F_KDebugForKernel_0002
	IMPORT_FUNC	"KDebugForKernel",0x2FF4E9F9,sceKernelAssert
#endif
#ifdef F_KDebugForKernel_0003
	IMPORT_FUNC	"KDebugForKernel",0x9B868276,sceKernelGetDebugPutchar
#endif
#ifdef F_KDebugForKernel_0004
	IMPORT_FUNC	"KDebugForKernel",0xE146606D,sceKernelRegisterDebugPutchar
#endif
#ifdef F_KDebugForKernel_0005
	IMPORT_FUNC	"KDebugForKernel",0x7CEB2C09,sceKernelRegisterKprintfHandler
#endif
#ifdef F_KDebugForKernel_0006
	IMPORT_FUNC	"KDebugForKernel",0x84F370BC,Kprintf
#endif
#ifdef F_KDebugForKernel_0007
	IMPORT_FUNC	"KDebugForKernel",0x5CE9838B,sceKernelDebugWrite
#endif
#ifdef F_KDebugForKernel_0008
	IMPORT_FUNC	"KDebugForKernel",0x66253C4E,sceKernelRegisterDebugWrite
#endif
#ifdef F_KDebugForKernel_0009
	IMPORT_FUNC	"KDebugForKernel",0xDBB5597F,sceKernelDebugRead
#endif
#ifdef F_KDebugForKernel_0010
	IMPORT_FUNC	"KDebugForKernel",0xE6554FDA,sceKernelRegisterDebugRead
#endif
#ifdef F_KDebugForKernel_0011
	IMPORT_FUNC	"KDebugForKernel",0xB9C643C9,sceKernelDebugEcho
#endif
#ifdef F_KDebugForKernel_0012
	IMPORT_FUNC	"KDebugForKernel",0x7D1C74F0,sceKernelDebugEchoSet
#endif
#ifdef F_KDebugForKernel_0013
	IMPORT_FUNC	"KDebugForKernel",0x24C32559,KDebugForKernel_24C32559
#endif
#ifdef F_KDebugForKernel_0014
	IMPORT_FUNC	"KDebugForKernel",0xD636B827,sceKernelRemoveByDebugSection
#endif
#ifdef F_KDebugForKernel_0015
	IMPORT_FUNC	"KDebugForKernel",0x5282DD5E,KDebugForKernel_5282DD5E
#endif
#ifdef F_KDebugForKernel_0016
	IMPORT_FUNC	"KDebugForKernel",0x9F8703E4,KDebugForKernel_9F8703E4
#endif
#ifdef F_KDebugForKernel_0017
	IMPORT_FUNC	"KDebugForKernel",0x333DCEC7,KDebugForKernel_333DCEC7
#endif
#ifdef F_KDebugForKernel_0018
	IMPORT_FUNC	"KDebugForKernel",0xE892D9A1,KDebugForKernel_E892D9A1
#endif
#ifdef F_KDebugForKernel_0019
	IMPORT_FUNC	"KDebugForKernel",0xA126F497,KDebugForKernel_A126F497
#endif
#ifdef F_KDebugForKernel_0020
	IMPORT_FUNC	"KDebugForKernel",0xB7251823,KDebugForKernel_B7251823
#endif
