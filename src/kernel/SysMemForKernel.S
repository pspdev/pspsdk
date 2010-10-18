	.set noreorder

#include "pspimport.s"

// Build List

#ifdef F_SysMemForKernel_0000
	IMPORT_START	"SysMemForKernel",0x00010011
#endif
#ifdef F_SysMemForKernel_0001
	IMPORT_FUNC	"SysMemForKernel",0x1C1FBFE7,sceKernelCreateHeap
#endif
#ifdef F_SysMemForKernel_0002
	IMPORT_FUNC	"SysMemForKernel",0xC9805775,sceKernelDeleteHeap
#endif
#ifdef F_SysMemForKernel_0003
	IMPORT_FUNC	"SysMemForKernel",0xEB7A74DB,sceKernelAllocHeapMemoryWithOption
#endif
#ifdef F_SysMemForKernel_0004
	IMPORT_FUNC	"SysMemForKernel",0x636C953B,sceKernelAllocHeapMemory
#endif
#ifdef F_SysMemForKernel_0005
	IMPORT_FUNC	"SysMemForKernel",0x7B749390,sceKernelFreeHeapMemory
#endif
#ifdef F_SysMemForKernel_0006
	IMPORT_FUNC	"SysMemForKernel",0xA823047E,sceKernelHeapTotalFreeSize
#endif
#ifdef F_SysMemForKernel_0007
	IMPORT_FUNC	"SysMemForKernel",0xB2163AA1,sceKernelGetHeapTypeCB
#endif
#ifdef F_SysMemForKernel_0008
	IMPORT_FUNC	"SysMemForKernel",0xEFF0C6DD,SysMemForKernel_EFF0C6DD
#endif
#ifdef F_SysMemForKernel_0009
	IMPORT_FUNC	"SysMemForKernel",0xEFEEBAC7,SysMemForKernel_EFEEBAC7
#endif
#ifdef F_SysMemForKernel_0010
	IMPORT_FUNC	"SysMemForKernel",0x2DB687E9,sceKernelIsValidHeap
#endif
#ifdef F_SysMemForKernel_0011
	IMPORT_FUNC	"SysMemForKernel",0x55A40B2C,sceKernelQueryMemoryPartitionInfo
#endif
#ifdef F_SysMemForKernel_0012
	IMPORT_FUNC	"SysMemForKernel",0xE6581468,sceKernelPartitionMaxFreeMemSize
#endif
#ifdef F_SysMemForKernel_0013
	IMPORT_FUNC	"SysMemForKernel",0x9697CD32,sceKernelPartitionTotalFreeMemSize
#endif
#ifdef F_SysMemForKernel_0014
	IMPORT_FUNC	"SysMemForKernel",0xA2A65F0E,sceKernelFillFreeBlock
#endif
#ifdef F_SysMemForKernel_0015
	IMPORT_FUNC	"SysMemForKernel",0x237DBD4F,sceKernelAllocPartitionMemory
#endif
#ifdef F_SysMemForKernel_0016
	IMPORT_FUNC	"SysMemForKernel",0xEE867074,sceKernelSizeLockMemoryBlock
#endif
#ifdef F_SysMemForKernel_0017
	IMPORT_FUNC	"SysMemForKernel",0xCE5544F4,sceKernelResizeMemoryBlock
#endif
#ifdef F_SysMemForKernel_0018
	IMPORT_FUNC	"SysMemForKernel",0x5EBE73DE,sceKernelJointMemoryBlock
#endif
#ifdef F_SysMemForKernel_0019
	IMPORT_FUNC	"SysMemForKernel",0x915EF4AC,SysMemForKernel_915EF4AC
#endif
#ifdef F_SysMemForKernel_0020
	IMPORT_FUNC	"SysMemForKernel",0xB6D61D02,sceKernelFreePartitionMemory
#endif
#ifdef F_SysMemForKernel_0021
	IMPORT_FUNC	"SysMemForKernel",0x2A3E5280,sceKernelQueryMemoryInfo
#endif
#ifdef F_SysMemForKernel_0022
	IMPORT_FUNC	"SysMemForKernel",0xEB4C0E1B,sceKernelQueryBlockSize
#endif
#ifdef F_SysMemForKernel_0023
	IMPORT_FUNC	"SysMemForKernel",0x82CCA14F,sceKernelQueryMemoryBlockInfo
#endif
#ifdef F_SysMemForKernel_0024
	IMPORT_FUNC	"SysMemForKernel",0x9D9A5BA1,sceKernelGetBlockHeadAddr
#endif
#ifdef F_SysMemForKernel_0025
	IMPORT_FUNC	"SysMemForKernel",0x2F3B7611,SysMemForKernel_2F3B7611
#endif
#ifdef F_SysMemForKernel_0026
	IMPORT_FUNC	"SysMemForKernel",0x7B3E7441,SysMemForKernel_7B3E7441
#endif
#ifdef F_SysMemForKernel_0027
	IMPORT_FUNC	"SysMemForKernel",0xB2C7AA36,sceKernelSetDdrMemoryProtection
#endif
#ifdef F_SysMemForKernel_0028
	IMPORT_FUNC	"SysMemForKernel",0x6C1DCD41,sceKernelCallUIDFunction
#endif
#ifdef F_SysMemForKernel_0029
	IMPORT_FUNC	"SysMemForKernel",0x5367923C,sceKernelCallUIDObjFunction
#endif
#ifdef F_SysMemForKernel_0030
	IMPORT_FUNC	"SysMemForKernel",0xCE05CCB7,SysMemForKernel_CE05CCB7
#endif
#ifdef F_SysMemForKernel_0031
	IMPORT_FUNC	"SysMemForKernel",0x6CD838EC,sceKernelLookupUIDFunction
#endif
#ifdef F_SysMemForKernel_0032
	IMPORT_FUNC	"SysMemForKernel",0xAD09C397,sceKernelCreateUIDtypeInherit
#endif
#ifdef F_SysMemForKernel_0033
	IMPORT_FUNC	"SysMemForKernel",0xFEFC8666,sceKernelCreateUIDtype
#endif
#ifdef F_SysMemForKernel_0034
	IMPORT_FUNC	"SysMemForKernel",0xD1BAB054,sceKernelDeleteUIDtype
#endif
#ifdef F_SysMemForKernel_0035
	IMPORT_FUNC	"SysMemForKernel",0x1C221A08,sceKernelGetUIDname
#endif
#ifdef F_SysMemForKernel_0036
	IMPORT_FUNC	"SysMemForKernel",0x2E3402CC,sceKernelRenameUID
#endif
#ifdef F_SysMemForKernel_0037
	IMPORT_FUNC	"SysMemForKernel",0x39357F07,sceKernelGetUIDtype
#endif
#ifdef F_SysMemForKernel_0038
	IMPORT_FUNC	"SysMemForKernel",0x89A74008,sceKernelCreateUID
#endif
#ifdef F_SysMemForKernel_0039
	IMPORT_FUNC	"SysMemForKernel",0x8F20C4C0,sceKernelDeleteUID
#endif
#ifdef F_SysMemForKernel_0040
	IMPORT_FUNC	"SysMemForKernel",0x55BFD686,sceKernelSearchUIDbyName
#endif
#ifdef F_SysMemForKernel_0041
	IMPORT_FUNC	"SysMemForKernel",0xCF4DE78C,sceKernelGetUIDcontrolBlock
#endif
#ifdef F_SysMemForKernel_0042
	IMPORT_FUNC	"SysMemForKernel",0x41FFC7F9,sceKernelGetUIDcontrolBlockWithType
#endif
#ifdef F_SysMemForKernel_0043
	IMPORT_FUNC	"SysMemForKernel",0x82D3CEE3,SysMemForKernel_82D3CEE3
#endif
#ifdef F_SysMemForKernel_0044
	IMPORT_FUNC	"SysMemForKernel",0xFC207849,SysMemForKernel_FC207849
#endif
#ifdef F_SysMemForKernel_0045
	IMPORT_FUNC	"SysMemForKernel",0x536AD5E1,SysMemForKernel_536AD5E1
#endif
#ifdef F_SysMemForKernel_0046
	IMPORT_FUNC	"SysMemForKernel",0xDFAEBD5B,sceKernelIsHold
#endif
#ifdef F_SysMemForKernel_0047
	IMPORT_FUNC	"SysMemForKernel",0x7BE95FA0,sceKernelHoldUID
#endif
#ifdef F_SysMemForKernel_0048
	IMPORT_FUNC	"SysMemForKernel",0xFE8DEBE0,sceKernelReleaseUID
#endif
#ifdef F_SysMemForKernel_0049
	IMPORT_FUNC	"SysMemForKernel",0xBD5941B4,sceKernelSysmemIsValidAccess
#endif
#ifdef F_SysMemForKernel_0050
	IMPORT_FUNC	"SysMemForKernel",0x80F25772,sceKernelIsValidUserAccess
#endif
#ifdef F_SysMemForKernel_0051
	IMPORT_FUNC	"SysMemForKernel",0x3905D956,sceKernelSysMemCheckCtlBlk
#endif
#ifdef F_SysMemForKernel_0052
	IMPORT_FUNC	"SysMemForKernel",0x26F96157,sceKernelSysMemDump
#endif
#ifdef F_SysMemForKernel_0053
	IMPORT_FUNC	"SysMemForKernel",0x6D6200DD,sceKernelSysMemDumpBlock
#endif
#ifdef F_SysMemForKernel_0054
	IMPORT_FUNC	"SysMemForKernel",0x621037F5,sceKernelSysMemDumpTail
#endif
#ifdef F_SysMemForKernel_0055
	IMPORT_FUNC	"SysMemForKernel",0xA089ECA4,sceKernelMemset
#endif
#ifdef F_SysMemForKernel_0056
	IMPORT_FUNC	"SysMemForKernel",0x2F808748,SysMemForKernel_2F808748
#endif
#ifdef F_SysMemForKernel_0057
	IMPORT_FUNC	"SysMemForKernel",0x1C4B1713,SysMemForKernel_1C4B1713
#endif
#ifdef F_SysMemForKernel_0058
	IMPORT_FUNC	"SysMemForKernel",0xE400FDB0,sceKernelSysMemInit
#endif
#ifdef F_SysMemForKernel_0059
	IMPORT_FUNC	"SysMemForKernel",0x1890BE9C,sceKernelSysMemMemSize
#endif
#ifdef F_SysMemForKernel_0060
	IMPORT_FUNC	"SysMemForKernel",0x03072750,sceKernelSysMemMaxFreeMemSize
#endif
#ifdef F_SysMemForKernel_0061
	IMPORT_FUNC	"SysMemForKernel",0x811BED79,sceKernelSysMemTotalFreeMemSize
#endif
#ifdef F_SysMemForKernel_0062
	IMPORT_FUNC	"SysMemForKernel",0xF6C10E27,sceKernelGetSysMemoryInfo
#endif
#ifdef F_SysMemForKernel_0063
	IMPORT_FUNC	"SysMemForKernel",0xCDA3A2F7,SysMemForKernel_CDA3A2F7
#endif
#ifdef F_SysMemForKernel_0064
	IMPORT_FUNC	"SysMemForKernel",0x960B888C,SysMemForKernel_960B888C
#endif
#ifdef F_SysMemForKernel_0065
	IMPORT_FUNC	"SysMemForKernel",0x3FC9AE6A,sceKernelDevkitVersion
#endif
#ifdef F_SysMemForKernel_0066
	IMPORT_FUNC	"SysMemForKernel",0x452E3696,SysMemForKernel_452E3696
#endif
#ifdef F_SysMemForKernel_0067
	IMPORT_FUNC	"SysMemForKernel",0x95F5E8DA,SysMemForKernel_95F5E8DA
#endif
#ifdef F_SysMemForKernel_0068
	IMPORT_FUNC "SysMemForKernel",0x6373995D,sceKernelGetModel
#endif
