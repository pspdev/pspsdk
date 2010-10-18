	.set noreorder

#include "pspimport.s"

#ifdef F_SysclibForKernel_0000
	IMPORT_START	"SysclibForKernel",0x00010000
#endif
#ifdef F_SysclibForKernel_0001
	IMPORT_FUNC	"SysclibForKernel",0x476FD94A,strcat
#endif
#ifdef F_SysclibForKernel_0002
	IMPORT_FUNC	"SysclibForKernel",0x89B79CB1,strcspn
#endif
#ifdef F_SysclibForKernel_0003
	IMPORT_FUNC	"SysclibForKernel",0xD1CD40E5,index
#endif
#ifdef F_SysclibForKernel_0004
	IMPORT_FUNC	"SysclibForKernel",0x243665ED,rindex
#endif
#ifdef F_SysclibForKernel_0005
	IMPORT_FUNC	"SysclibForKernel",0x90C5573D,strnlen
#endif
#ifdef F_SysclibForKernel_0006
	IMPORT_FUNC	"SysclibForKernel",0x0DFB7B6C,strpbrk
#endif
#ifdef F_SysclibForKernel_0007
	IMPORT_FUNC	"SysclibForKernel",0x62AE052F,strspn
#endif
#ifdef F_SysclibForKernel_0008
	IMPORT_FUNC	"SysclibForKernel",0x0D188658,strstr
#endif
#ifdef F_SysclibForKernel_0009
	IMPORT_FUNC	"SysclibForKernel",0x87F8D2DA,strtok
#endif
#ifdef F_SysclibForKernel_0010
	IMPORT_FUNC	"SysclibForKernel",0x1AB53A58,strtok_r
#endif
#ifdef F_SysclibForKernel_0011
	IMPORT_FUNC	"SysclibForKernel",0x47DD934D,strtol
#endif
#ifdef F_SysclibForKernel_0012
	IMPORT_FUNC	"SysclibForKernel",0x1D83F344,atob
#endif
#ifdef F_SysclibForKernel_0013
	IMPORT_FUNC	"SysclibForKernel",0x6A7900E1,strtoul
#endif
#ifdef F_SysclibForKernel_0014
	IMPORT_FUNC	"SysclibForKernel",0x8AF6B8F8,SysclibForKernel_8AF6B8F8
#endif
#ifdef F_SysclibForKernel_0015
	IMPORT_FUNC	"SysclibForKernel",0xDF17F4A2,SysclibForKernel_DF17F4A2
#endif
#ifdef F_SysclibForKernel_0016
	IMPORT_FUNC	"SysclibForKernel",0x7DEE14DE,SysclibForKernel_7DEE14DE
#endif
#ifdef F_SysclibForKernel_0017
	IMPORT_FUNC	"SysclibForKernel",0x5E8E5F42,SysclibForKernel_5E8E5F42
#endif
#ifdef F_SysclibForKernel_0018
	IMPORT_FUNC	"SysclibForKernel",0xC0AB8932,strcmp
#endif
#ifdef F_SysclibForKernel_0019
	IMPORT_FUNC	"SysclibForKernel",0xEC6F1CF2,strcpy
#endif
#ifdef F_SysclibForKernel_0020
	IMPORT_FUNC	"SysclibForKernel",0xB1DC2AE8,strchr
#endif
#ifdef F_SysclibForKernel_0021
	IMPORT_FUNC	"SysclibForKernel",0x4C0E0274,strrchr
#endif
#ifdef F_SysclibForKernel_0022
	IMPORT_FUNC	"SysclibForKernel",0x7AB35214,strncmp
#endif
#ifdef F_SysclibForKernel_0023
	IMPORT_FUNC	"SysclibForKernel",0xB49A7697,strncpy
#endif
#ifdef F_SysclibForKernel_0024
	IMPORT_FUNC	"SysclibForKernel",0x52DF196C,strlen
#endif
#ifdef F_SysclibForKernel_0025
	IMPORT_FUNC	"SysclibForKernel",0xD3D1A3B9,strncat
#endif
#ifdef F_SysclibForKernel_0026
	IMPORT_FUNC	"SysclibForKernel",0x68A78817,memchr
#endif
#ifdef F_SysclibForKernel_0027
	IMPORT_FUNC	"SysclibForKernel",0xAB7592FF,memcpy
#endif
#ifdef F_SysclibForKernel_0028
	IMPORT_FUNC	"SysclibForKernel",0x10F3BB61,memset
#endif
#ifdef F_SysclibForKernel_0029
	IMPORT_FUNC	"SysclibForKernel",0x81D0D1F7,memcmp
#endif
#ifdef F_SysclibForKernel_0030
	IMPORT_FUNC	"SysclibForKernel",0xA48D2592,memmove
#endif
#ifdef F_SysclibForKernel_0031
	IMPORT_FUNC	"SysclibForKernel",0x097049BD,bcopy
#endif
#ifdef F_SysclibForKernel_0032
	IMPORT_FUNC	"SysclibForKernel",0x7F8A6F23,bcmp
#endif
#ifdef F_SysclibForKernel_0033
	IMPORT_FUNC	"SysclibForKernel",0x86FEFCE9,bzero
#endif
#ifdef F_SysclibForKernel_0034
	IMPORT_FUNC	"SysclibForKernel",0xCE2F7487,toupper
#endif
#ifdef F_SysclibForKernel_0035
	IMPORT_FUNC	"SysclibForKernel",0x3EC5BBF6,tolower
#endif
#ifdef F_SysclibForKernel_0036
	IMPORT_FUNC	"SysclibForKernel",0x32C767F2,look_ctype_table
#endif
#ifdef F_SysclibForKernel_0037
	IMPORT_FUNC	"SysclibForKernel",0xD887CACD,get_ctype_table
#endif
#ifdef F_SysclibForKernel_0038
	IMPORT_FUNC	"SysclibForKernel",0x87C78FB6,prnt
#endif
#ifdef F_SysclibForKernel_0039
	IMPORT_FUNC	"SysclibForKernel",0x7661E728,sprintf
#endif
#ifdef F_SysclibForKernel_0040
	IMPORT_FUNC	"SysclibForKernel",0x909C228B,setjmp
#endif
#ifdef F_SysclibForKernel_0041
	IMPORT_FUNC	"SysclibForKernel",0x18FE80DB,longjmp
#endif
#ifdef F_SysclibForKernel_0042
	IMPORT_FUNC	"SysclibForKernel",0x1493EBD9,wmemset
#endif
