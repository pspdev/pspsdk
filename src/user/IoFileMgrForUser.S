	.set noreorder

#include "pspimport.s"

#ifdef F_IoFileMgrForUser_0000
	IMPORT_START	"IoFileMgrForUser",0x40010000
#endif
#ifdef F_IoFileMgrForUser_0001
	IMPORT_FUNC	"IoFileMgrForUser",0x3251EA56,sceIoPollAsync
#endif
#ifdef F_IoFileMgrForUser_0002
	IMPORT_FUNC	"IoFileMgrForUser",0xE23EEC33,sceIoWaitAsync
#endif
#ifdef F_IoFileMgrForUser_0003
	IMPORT_FUNC	"IoFileMgrForUser",0x35DBD746,sceIoWaitAsyncCB
#endif
#ifdef F_IoFileMgrForUser_0004
	IMPORT_FUNC	"IoFileMgrForUser",0xCB05F8D6,sceIoGetAsyncStat
#endif
#ifdef F_IoFileMgrForUser_0005
	IMPORT_FUNC	"IoFileMgrForUser",0xB293727F,sceIoChangeAsyncPriority
#endif
#ifdef F_IoFileMgrForUser_0006
	IMPORT_FUNC	"IoFileMgrForUser",0xA12A0514,sceIoSetAsyncCallback
#endif
#ifdef F_IoFileMgrForUser_0007
	IMPORT_FUNC	"IoFileMgrForUser",0x810C4BC3,sceIoClose
#endif
#ifdef F_IoFileMgrForUser_0008
	IMPORT_FUNC	"IoFileMgrForUser",0xFF5940B6,sceIoCloseAsync
#endif
#ifdef F_IoFileMgrForUser_0009
	IMPORT_FUNC	"IoFileMgrForUser",0x109F50BC,sceIoOpen
#endif
#ifdef F_IoFileMgrForUser_0010
	IMPORT_FUNC	"IoFileMgrForUser",0x89AA9906,sceIoOpenAsync
#endif
#ifdef F_IoFileMgrForUser_0011
	IMPORT_FUNC	"IoFileMgrForUser",0x6A638D83,sceIoRead
#endif
#ifdef F_IoFileMgrForUser_0012
	IMPORT_FUNC	"IoFileMgrForUser",0xA0B5A7C2,sceIoReadAsync
#endif
#ifdef F_IoFileMgrForUser_0013
	IMPORT_FUNC	"IoFileMgrForUser",0x42EC03AC,sceIoWrite
#endif
#ifdef F_IoFileMgrForUser_0014
	IMPORT_FUNC	"IoFileMgrForUser",0x0FACAB19,sceIoWriteAsync
#endif
#ifdef F_IoFileMgrForUser_0015
	IMPORT_FUNC	"IoFileMgrForUser",0x27EB27B8,sceIoLseek
#endif
#ifdef F_IoFileMgrForUser_0016
	IMPORT_FUNC	"IoFileMgrForUser",0x71B19E77,sceIoLseekAsync
#endif
#ifdef F_IoFileMgrForUser_0017
	IMPORT_FUNC	"IoFileMgrForUser",0x68963324,sceIoLseek32
#endif
#ifdef F_IoFileMgrForUser_0018
	IMPORT_FUNC	"IoFileMgrForUser",0x1B385D8F,sceIoLseek32Async
#endif
#ifdef F_IoFileMgrForUser_0019
	IMPORT_FUNC	"IoFileMgrForUser",0x63632449,sceIoIoctl
#endif
#ifdef F_IoFileMgrForUser_0020
	IMPORT_FUNC	"IoFileMgrForUser",0xE95A012B,sceIoIoctlAsync
#endif
#ifdef F_IoFileMgrForUser_0021
	IMPORT_FUNC	"IoFileMgrForUser",0xB29DDF9C,sceIoDopen
#endif
#ifdef F_IoFileMgrForUser_0022
	IMPORT_FUNC	"IoFileMgrForUser",0xE3EB004C,sceIoDread
#endif
#ifdef F_IoFileMgrForUser_0023
	IMPORT_FUNC	"IoFileMgrForUser",0xEB092469,sceIoDclose
#endif
#ifdef F_IoFileMgrForUser_0024
	IMPORT_FUNC	"IoFileMgrForUser",0xF27A9C51,sceIoRemove
#endif
#ifdef F_IoFileMgrForUser_0025
	IMPORT_FUNC	"IoFileMgrForUser",0x06A70004,sceIoMkdir
#endif
#ifdef F_IoFileMgrForUser_0026
	IMPORT_FUNC	"IoFileMgrForUser",0x1117C65F,sceIoRmdir
#endif
#ifdef F_IoFileMgrForUser_0027
	IMPORT_FUNC	"IoFileMgrForUser",0x55F4717D,sceIoChdir
#endif
#ifdef F_IoFileMgrForUser_0028
	IMPORT_FUNC	"IoFileMgrForUser",0xAB96437F,sceIoSync
#endif
#ifdef F_IoFileMgrForUser_0029
	IMPORT_FUNC	"IoFileMgrForUser",0xACE946E8,sceIoGetstat
#endif
#ifdef F_IoFileMgrForUser_0030
	IMPORT_FUNC	"IoFileMgrForUser",0xB8A740F4,sceIoChstat
#endif
#ifdef F_IoFileMgrForUser_0031
	IMPORT_FUNC	"IoFileMgrForUser",0x779103A0,sceIoRename
#endif
#ifdef F_IoFileMgrForUser_0032
	IMPORT_FUNC	"IoFileMgrForUser",0x54F5FB11,sceIoDevctl
#endif
#ifdef F_IoFileMgrForUser_0033
	IMPORT_FUNC	"IoFileMgrForUser",0x08BD7374,sceIoGetDevType
#endif
#ifdef F_IoFileMgrForUser_0034
	IMPORT_FUNC	"IoFileMgrForUser",0xB2A628C1,sceIoAssign
#endif
#ifdef F_IoFileMgrForUser_0035
	IMPORT_FUNC	"IoFileMgrForUser",0x6D08A871,sceIoUnassign
#endif
#ifdef F_IoFileMgrForUser_0036
	IMPORT_FUNC	"IoFileMgrForUser",0xE8BC6571,sceIoCancel
#endif
