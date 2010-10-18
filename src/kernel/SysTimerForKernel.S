	.set noreorder

#include "pspimport.s"

#ifdef F_SysTimerForKernel_0000
	IMPORT_START	"SysTimerForKernel",0x00010000
#endif
#ifdef F_SysTimerForKernel_0001
	IMPORT_FUNC	"SysTimerForKernel",0xC99073E3,sceSTimerAlloc
#endif
#ifdef F_SysTimerForKernel_0002
	IMPORT_FUNC	"SysTimerForKernel",0xC105CF38,sceSTimerFree
#endif
#ifdef F_SysTimerForKernel_0003
	IMPORT_FUNC	"SysTimerForKernel",0xB53534B4,SysTimerForKernel_B53534B4
#endif
#ifdef F_SysTimerForKernel_0004
	IMPORT_FUNC	"SysTimerForKernel",0x975D8E84,sceSTimerSetHandler
#endif
#ifdef F_SysTimerForKernel_0005
	IMPORT_FUNC	"SysTimerForKernel",0xA95143E2,sceSTimerStartCount
#endif
#ifdef F_SysTimerForKernel_0006
	IMPORT_FUNC	"SysTimerForKernel",0x4A01F9D3,sceSTimerStopCount
#endif
#ifdef F_SysTimerForKernel_0007
	IMPORT_FUNC	"SysTimerForKernel",0x54BB5DB4,sceSTimerResetCount
#endif
#ifdef F_SysTimerForKernel_0008
	IMPORT_FUNC	"SysTimerForKernel",0x228EDAE4,sceSTimerGetCount
#endif
#ifdef F_SysTimerForKernel_0009
	IMPORT_FUNC	"SysTimerForKernel",0x53231A15,SysTimerForKernel_53231A15
#endif
