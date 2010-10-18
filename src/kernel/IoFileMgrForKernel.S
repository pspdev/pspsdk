	.set noreorder

#include "pspimport.s"

#ifdef F_IoFileMgrForKernel_0000
	IMPORT_START	"IoFileMgrForKernel",0x00010000
#endif
#ifdef F_IoFileMgrForKernel_0001
	IMPORT_FUNC	"IoFileMgrForKernel",0x3251EA56,sceIoPollAsync
#endif
#ifdef F_IoFileMgrForKernel_0002
	IMPORT_FUNC	"IoFileMgrForKernel",0xE23EEC33,sceIoWaitAsync
#endif
#ifdef F_IoFileMgrForKernel_0003
	IMPORT_FUNC	"IoFileMgrForKernel",0x35DBD746,sceIoWaitAsyncCB
#endif
#ifdef F_IoFileMgrForKernel_0004
	IMPORT_FUNC	"IoFileMgrForKernel",0xCB05F8D6,sceIoGetAsyncStat
#endif
#ifdef F_IoFileMgrForKernel_0005
	IMPORT_FUNC	"IoFileMgrForKernel",0xB293727F,sceIoChangeAsyncPriority
#endif
#ifdef F_IoFileMgrForKernel_0006
	IMPORT_FUNC	"IoFileMgrForKernel",0xA12A0514,sceIoSetAsyncCallback
#endif
#ifdef F_IoFileMgrForKernel_0007
	IMPORT_FUNC	"IoFileMgrForKernel",0x810C4BC3,sceIoClose
#endif
#ifdef F_IoFileMgrForKernel_0008
	IMPORT_FUNC	"IoFileMgrForKernel",0xFF5940B6,sceIoCloseAsync
#endif
#ifdef F_IoFileMgrForKernel_0009
	IMPORT_FUNC	"IoFileMgrForKernel",0xA905B705,sceIoCloseAll
#endif
#ifdef F_IoFileMgrForKernel_0010
	IMPORT_FUNC	"IoFileMgrForKernel",0x109F50BC,sceIoOpen
#endif
#ifdef F_IoFileMgrForKernel_0011
	IMPORT_FUNC	"IoFileMgrForKernel",0x89AA9906,sceIoOpenAsync
#endif
#ifdef F_IoFileMgrForKernel_0012
	IMPORT_FUNC	"IoFileMgrForKernel",0x3C54E908,sceIoReopen
#endif
#ifdef F_IoFileMgrForKernel_0013
	IMPORT_FUNC	"IoFileMgrForKernel",0x6A638D83,sceIoRead
#endif
#ifdef F_IoFileMgrForKernel_0014
	IMPORT_FUNC	"IoFileMgrForKernel",0xA0B5A7C2,sceIoReadAsync
#endif
#ifdef F_IoFileMgrForKernel_0015
	IMPORT_FUNC	"IoFileMgrForKernel",0x42EC03AC,sceIoWrite
#endif
#ifdef F_IoFileMgrForKernel_0016
	IMPORT_FUNC	"IoFileMgrForKernel",0x0FACAB19,sceIoWriteAsync
#endif
#ifdef F_IoFileMgrForKernel_0017
	IMPORT_FUNC	"IoFileMgrForKernel",0x27EB27B8,sceIoLseek
#endif
#ifdef F_IoFileMgrForKernel_0018
	IMPORT_FUNC	"IoFileMgrForKernel",0x71B19E77,sceIoLseekAsync
#endif
#ifdef F_IoFileMgrForKernel_0019
	IMPORT_FUNC	"IoFileMgrForKernel",0x68963324,sceIoLseek32
#endif
#ifdef F_IoFileMgrForKernel_0020
	IMPORT_FUNC	"IoFileMgrForKernel",0x1B385D8F,sceIoLseek32Async
#endif
#ifdef F_IoFileMgrForKernel_0021
	IMPORT_FUNC	"IoFileMgrForKernel",0x63632449,sceIoIoctl
#endif
#ifdef F_IoFileMgrForKernel_0022
	IMPORT_FUNC	"IoFileMgrForKernel",0xE95A012B,sceIoIoctlAsync
#endif
#ifdef F_IoFileMgrForKernel_0023
	IMPORT_FUNC	"IoFileMgrForKernel",0xB29DDF9C,sceIoDopen
#endif
#ifdef F_IoFileMgrForKernel_0024
	IMPORT_FUNC	"IoFileMgrForKernel",0xE3EB004C,sceIoDread
#endif
#ifdef F_IoFileMgrForKernel_0025
	IMPORT_FUNC	"IoFileMgrForKernel",0xEB092469,sceIoDclose
#endif
#ifdef F_IoFileMgrForKernel_0026
	IMPORT_FUNC	"IoFileMgrForKernel",0xF27A9C51,sceIoRemove
#endif
#ifdef F_IoFileMgrForKernel_0027
	IMPORT_FUNC	"IoFileMgrForKernel",0x06A70004,sceIoMkdir
#endif
#ifdef F_IoFileMgrForKernel_0028
	IMPORT_FUNC	"IoFileMgrForKernel",0x1117C65F,sceIoRmdir
#endif
#ifdef F_IoFileMgrForKernel_0029
	IMPORT_FUNC	"IoFileMgrForKernel",0x55F4717D,sceIoChdir
#endif
#ifdef F_IoFileMgrForKernel_0030
	IMPORT_FUNC	"IoFileMgrForKernel",0xAB96437F,sceIoSync
#endif
#ifdef F_IoFileMgrForKernel_0031
	IMPORT_FUNC	"IoFileMgrForKernel",0xACE946E8,sceIoGetstat
#endif
#ifdef F_IoFileMgrForKernel_0032
	IMPORT_FUNC	"IoFileMgrForKernel",0xB8A740F4,sceIoChstat
#endif
#ifdef F_IoFileMgrForKernel_0033
	IMPORT_FUNC	"IoFileMgrForKernel",0x779103A0,sceIoRename
#endif
#ifdef F_IoFileMgrForKernel_0034
	IMPORT_FUNC	"IoFileMgrForKernel",0x54F5FB11,sceIoDevctl
#endif
#ifdef F_IoFileMgrForKernel_0035
	IMPORT_FUNC	"IoFileMgrForKernel",0x08BD7374,sceIoGetDevType
#endif
#ifdef F_IoFileMgrForKernel_0036
	IMPORT_FUNC	"IoFileMgrForKernel",0xB2A628C1,sceIoAssign
#endif
#ifdef F_IoFileMgrForKernel_0037
	IMPORT_FUNC	"IoFileMgrForKernel",0x6D08A871,sceIoUnassign
#endif
#ifdef F_IoFileMgrForKernel_0038
	IMPORT_FUNC	"IoFileMgrForKernel",0x411106BA,sceIoGetThreadCwd
#endif
#ifdef F_IoFileMgrForKernel_0039
	IMPORT_FUNC	"IoFileMgrForKernel",0xCB0A151F,sceIoChangeThreadCwd
#endif
#ifdef F_IoFileMgrForKernel_0040
	IMPORT_FUNC	"IoFileMgrForKernel",0xE8BC6571,sceIoCancel
#endif
#ifdef F_IoFileMgrForKernel_0041
	IMPORT_FUNC	"IoFileMgrForKernel",0x8E982A74,sceIoAddDrv
#endif
#ifdef F_IoFileMgrForKernel_0042
	IMPORT_FUNC	"IoFileMgrForKernel",0xC7F35804,sceIoDelDrv
#endif
