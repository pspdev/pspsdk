	.set noreorder

#include "pspimport.s"

#ifdef F_scePower_0000
	IMPORT_START	"scePower",0x40010000
#endif
#ifdef F_scePower_0001
	IMPORT_FUNC	"scePower",0x2B51FE2F,scePower_2B51FE2F
#endif
#ifdef F_scePower_0002
	IMPORT_FUNC	"scePower",0x442BFBAC,scePower_442BFBAC
#endif
#ifdef F_scePower_0003
	IMPORT_FUNC	"scePower",0xEFD3C963,scePowerTick
#endif
#ifdef F_scePower_0004
	IMPORT_FUNC	"scePower",0xEDC13FE5,scePowerGetIdleTimer
#endif
#ifdef F_scePower_0005
	IMPORT_FUNC	"scePower",0x7F30B3B1,scePowerIdleTimerEnable
#endif
#ifdef F_scePower_0006
	IMPORT_FUNC	"scePower",0x972CE941,scePowerIdleTimerDisable
#endif
#ifdef F_scePower_0007
	IMPORT_FUNC	"scePower",0x27F3292C,scePowerBatteryUpdateInfo
#endif
#ifdef F_scePower_0008
	IMPORT_FUNC	"scePower",0xE8E4E204,scePower_E8E4E204
#endif
#ifdef F_scePower_0009
	IMPORT_FUNC	"scePower",0xB999184C,scePowerGetLowBatteryCapacity
#endif
#ifdef F_scePower_0010
	IMPORT_FUNC	"scePower",0x87440F5E,scePowerIsPowerOnline
#endif
#ifdef F_scePower_0011
	IMPORT_FUNC	"scePower",0x0AFD0D8B,scePowerIsBatteryExist
#endif
#ifdef F_scePower_0012
	IMPORT_FUNC	"scePower",0x1E490401,scePowerIsBatteryCharging
#endif
#ifdef F_scePower_0013
	IMPORT_FUNC	"scePower",0xB4432BC8,scePowerGetBatteryChargingStatus
#endif
#ifdef F_scePower_0014
	IMPORT_FUNC	"scePower",0xD3075926,scePowerIsLowBattery
#endif
#ifdef F_scePower_0015
	IMPORT_FUNC	"scePower",0x78A1A796,scePower_78A1A796
#endif
#ifdef F_scePower_0016
	IMPORT_FUNC	"scePower",0x94F5A53F,scePowerGetBatteryRemainCapacity
#endif
#ifdef F_scePower_0017
	IMPORT_FUNC	"scePower",0xFD18A0FF,scePower_FD18A0FF
#endif
#ifdef F_scePower_0018
	IMPORT_FUNC	"scePower",0x2085D15D,scePowerGetBatteryLifePercent
#endif
#ifdef F_scePower_0019
	IMPORT_FUNC	"scePower",0x8EFB3FA2,scePowerGetBatteryLifeTime
#endif
#ifdef F_scePower_0020
	IMPORT_FUNC	"scePower",0x28E12023,scePowerGetBatteryTemp
#endif
#ifdef F_scePower_0021
	IMPORT_FUNC	"scePower",0x862AE1A6,scePowerGetBatteryElec
#endif
#ifdef F_scePower_0022
	IMPORT_FUNC	"scePower",0x483CE86B,scePowerGetBatteryVolt
#endif
#ifdef F_scePower_0023
	IMPORT_FUNC	"scePower",0x23436A4A,scePower_23436A4A
#endif
#ifdef F_scePower_0024
	IMPORT_FUNC	"scePower",0x0CD21B1F,scePower_0CD21B1F
#endif
#ifdef F_scePower_0025
	IMPORT_FUNC	"scePower",0x165CE085,scePower_165CE085
#endif
#ifdef F_scePower_0026
	IMPORT_FUNC	"scePower",0xD6D016EF,scePowerLock
#endif
#ifdef F_scePower_0027
	IMPORT_FUNC	"scePower",0xCA3D34C1,scePowerUnlock
#endif
#ifdef F_scePower_0028
	IMPORT_FUNC	"scePower",0xDB62C9CF,scePowerCancelRequest
#endif
#ifdef F_scePower_0029
	IMPORT_FUNC	"scePower",0x7FA406DD,scePowerIsRequest
#endif
#ifdef F_scePower_0030
	IMPORT_FUNC	"scePower",0x2B7C7CF4,scePowerRequestStandby
#endif
#ifdef F_scePower_0031
	IMPORT_FUNC	"scePower",0xAC32C9CC,scePowerRequestSuspend
#endif
#ifdef F_scePower_0032
	IMPORT_FUNC	"scePower",0x2875994B,scePower_2875994B
#endif
#ifdef F_scePower_0033
	IMPORT_FUNC	"scePower",0x3951AF53,scePowerEncodeUBattery
#endif
#ifdef F_scePower_0034
	IMPORT_FUNC	"scePower",0x0074EF9B,scePowerGetResumeCount
#endif
#ifdef F_scePower_0035
	IMPORT_FUNC	"scePower",0x04B7766E,scePowerRegisterCallback
#endif
#ifdef F_scePower_0036
	IMPORT_FUNC	"scePower",0xDFA8BAF8,scePowerUnregisterCallback
#endif
#ifdef F_scePower_0037
	IMPORT_FUNC	"scePower",0xDB9D28DD,scePowerUnregitserCallback
#endif
#ifdef F_scePower_0038
	IMPORT_FUNC	"scePower",0x843FBF43,scePowerSetCpuClockFrequency
#endif
#ifdef F_scePower_0039
	IMPORT_FUNC	"scePower",0xB8D7B3FB,scePowerSetBusClockFrequency
#endif
#ifdef F_scePower_0040
	IMPORT_FUNC	"scePower",0xFEE03A2F,scePowerGetCpuClockFrequency
#endif
#ifdef F_scePower_0041
	IMPORT_FUNC	"scePower",0x478FE6F5,scePowerGetBusClockFrequency
#endif
#ifdef F_scePower_0042
	IMPORT_FUNC	"scePower",0xFDB5BFE9,scePowerGetCpuClockFrequencyInt
#endif
#ifdef F_scePower_0043
	IMPORT_FUNC	"scePower",0xBD681969,scePowerGetBusClockFrequencyInt
#endif
#ifdef F_scePower_0044
	IMPORT_FUNC	"scePower",0xB1A52C83,scePowerGetCpuClockFrequencyFloat
#endif
#ifdef F_scePower_0045
	IMPORT_FUNC	"scePower",0x9BADB3EB,scePowerGetBusClockFrequencyFloat
#endif
#ifdef F_scePower_0046
	IMPORT_FUNC	"scePower",0x737486F2,scePowerSetClockFrequency
#endif
