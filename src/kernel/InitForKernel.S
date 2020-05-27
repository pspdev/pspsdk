	.set noreorder

#include "pspimport.s"

#ifdef F_InitForKernel_0000
	IMPORT_START	"InitForKernel",0x00090000
#endif
#ifdef F_InitForKernel_0001
	IMPORT_FUNC	"InitForKernel",0x1D3256BA,sceKernelRegisterChunk
#endif
#ifdef F_InitForKernel_0002
	IMPORT_FUNC	"InitForKernel",0x27932388,sceKernelBootFrom
#endif
#ifdef F_InitForKernel_0003
	IMPORT_FUNC	"InitForKernel",0x2C6E9FE9,sceKernelGetChunk
#endif
#ifdef F_InitForKernel_0004
	IMPORT_FUNC	"InitForKernel",0x33D30F49,InitForKernel_33D30F49
#endif
#ifdef F_InitForKernel_0005
	IMPORT_FUNC	"InitForKernel",0x7233B5BC,InitForKernel_7233B5BC
#endif
#ifdef F_InitForKernel_0006
	IMPORT_FUNC	"InitForKernel",0x7A2333AD,sceKernelInitApitype
#endif
#ifdef F_InitForKernel_0007
	IMPORT_FUNC	"InitForKernel",0x9F9AE99C,InitForKernel_9F9AE99C
#endif
#ifdef F_InitForKernel_0008
	IMPORT_FUNC	"InitForKernel",0xA6E71B93,sceKernelInitFileName
#endif
#ifdef F_InitForKernel_0009
	IMPORT_FUNC	"InitForKernel",0xC4F1BA33,InitForKernel_C4F1BA33
#endif
#ifdef F_InitForKernel_0010
	IMPORT_FUNC	"InitForKernel",0xCE88E870,sceKernelReleaseChunk
#endif
#ifdef F_InitForKernel_0011
	IMPORT_FUNC	"InitForKernel",0xFD0F25AD,InitForKernel_FD0F25AD
#endif
