	.set noreorder

#include "pspimport.s"

#ifdef F_scePower_driver_0000
	IMPORT_START	"scePower_driver",0x00010000
#endif
#ifdef F_scePower_driver_0001
	IMPORT_FUNC	"scePower_driver",0x9CE06934,scePowerInit
#endif
#ifdef F_scePower_driver_0002
	IMPORT_FUNC	"scePower_driver",0xAD5BB433,scePowerEnd
#endif
#ifdef F_scePower_driver_0003
	IMPORT_FUNC	"scePower_driver",0x6D2CA84B,scePowerWlanActivate
#endif
#ifdef F_scePower_driver_0004
	IMPORT_FUNC	"scePower_driver",0x23BB0A60,scePowerWlanDeactivate
#endif
#ifdef F_scePower_driver_0005
	IMPORT_FUNC	"scePower_driver",0x2B51FE2F,scePower_driver_2B51FE2F
#endif
#ifdef F_scePower_driver_0006
	IMPORT_FUNC	"scePower_driver",0x442BFBAC,scePower_driver_442BFBAC
#endif
#ifdef F_scePower_driver_0007
	IMPORT_FUNC	"scePower_driver",0xE8685403,scePower_driver_E8685403
#endif
#ifdef F_scePower_driver_0008
	IMPORT_FUNC	"scePower_driver",0xEFD3C963,scePowerTick
#endif
#ifdef F_scePower_driver_0009
	IMPORT_FUNC	"scePower_driver",0xEDC13FE5,scePowerGetIdleTimer
#endif
#ifdef F_scePower_driver_0010
	IMPORT_FUNC	"scePower_driver",0x1BA2FCAE,scePowerSetIdleCallback
#endif
#ifdef F_scePower_driver_0011
	IMPORT_FUNC	"scePower_driver",0x7F30B3B1,scePowerIdleTimerEnable
#endif
#ifdef F_scePower_driver_0012
	IMPORT_FUNC	"scePower_driver",0x972CE941,scePowerIdleTimerDisable
#endif
#ifdef F_scePower_driver_0013
	IMPORT_FUNC	"scePower_driver",0x27F3292C,scePowerBatteryUpdateInfo
#endif
#ifdef F_scePower_driver_0014
	IMPORT_FUNC	"scePower_driver",0xE8E4E204,scePower_driver_E8E4E204
#endif
#ifdef F_scePower_driver_0015
	IMPORT_FUNC	"scePower_driver",0xB999184C,scePowerGetLowBatteryCapacity
#endif
#ifdef F_scePower_driver_0016
	IMPORT_FUNC	"scePower_driver",0x166922EC,scePower_driver_166922EC
#endif
#ifdef F_scePower_driver_0017
	IMPORT_FUNC	"scePower_driver",0xDD3D4DAC,scePower_driver_DD3D4DAC
#endif
#ifdef F_scePower_driver_0018
	IMPORT_FUNC	"scePower_driver",0x87440F5E,scePowerIsPowerOnline
#endif
#ifdef F_scePower_driver_0019
	IMPORT_FUNC	"scePower_driver",0x0AFD0D8B,scePowerIsBatteryExist
#endif
#ifdef F_scePower_driver_0020
	IMPORT_FUNC	"scePower_driver",0x1E490401,scePowerIsBatteryCharging
#endif
#ifdef F_scePower_driver_0021
	IMPORT_FUNC	"scePower_driver",0xB4432BC8,scePowerGetBatteryChargingStatus
#endif
#ifdef F_scePower_driver_0022
	IMPORT_FUNC	"scePower_driver",0xD3075926,scePowerIsLowBattery
#endif
#ifdef F_scePower_driver_0023
	IMPORT_FUNC	"scePower_driver",0x78A1A796,scePower_driver_78A1A796
#endif
#ifdef F_scePower_driver_0024
	IMPORT_FUNC	"scePower_driver",0x94F5A53F,scePowerGetBatteryRemainCapacity
#endif
#ifdef F_scePower_driver_0025
	IMPORT_FUNC	"scePower_driver",0xFD18A0FF,scePower_driver_FD18A0FF
#endif
#ifdef F_scePower_driver_0026
	IMPORT_FUNC	"scePower_driver",0x2085D15D,scePowerGetBatteryLifePercent
#endif
#ifdef F_scePower_driver_0027
	IMPORT_FUNC	"scePower_driver",0x8EFB3FA2,scePowerGetBatteryLifeTime
#endif
#ifdef F_scePower_driver_0028
	IMPORT_FUNC	"scePower_driver",0x28E12023,scePowerGetBatteryTemp
#endif
#ifdef F_scePower_driver_0029
	IMPORT_FUNC	"scePower_driver",0x862AE1A6,scePowerGetBatteryElec
#endif
#ifdef F_scePower_driver_0030
	IMPORT_FUNC	"scePower_driver",0x483CE86B,scePowerGetBatteryVolt
#endif
#ifdef F_scePower_driver_0031
	IMPORT_FUNC	"scePower_driver",0x23436A4A,scePower_driver_23436A4A
#endif
#ifdef F_scePower_driver_0032
	IMPORT_FUNC	"scePower_driver",0x0CD21B1F,scePower_driver_0CD21B1F
#endif
#ifdef F_scePower_driver_0033
	IMPORT_FUNC	"scePower_driver",0x165CE085,scePower_driver_165CE085
#endif
#ifdef F_scePower_driver_0034
	IMPORT_FUNC	"scePower_driver",0xD6D016EF,scePowerLock
#endif
#ifdef F_scePower_driver_0035
	IMPORT_FUNC	"scePower_driver",0xCA3D34C1,scePowerUnlock
#endif
#ifdef F_scePower_driver_0036
	IMPORT_FUNC	"scePower_driver",0x79DB9421,scePowerRebootStart
#endif
#ifdef F_scePower_driver_0037
	IMPORT_FUNC	"scePower_driver",0xDB62C9CF,scePowerCancelRequest
#endif
#ifdef F_scePower_driver_0038
	IMPORT_FUNC	"scePower_driver",0x7FA406DD,scePowerIsRequest
#endif
#ifdef F_scePower_driver_0039
	IMPORT_FUNC	"scePower_driver",0x2B7C7CF4,scePowerRequestStandby
#endif
#ifdef F_scePower_driver_0040
	IMPORT_FUNC	"scePower_driver",0xAC32C9CC,scePowerRequestSuspend
#endif
#ifdef F_scePower_driver_0041
	IMPORT_FUNC	"scePower_driver",0x2875994B,scePower_driver_2875994B
#endif
#ifdef F_scePower_driver_0042
	IMPORT_FUNC	"scePower_driver",0x3951AF53,scePowerEncodeUBattery
#endif
#ifdef F_scePower_driver_0043
	IMPORT_FUNC	"scePower_driver",0x0074EF9B,scePowerGetResumeCount
#endif
#ifdef F_scePower_driver_0044
	IMPORT_FUNC	"scePower_driver",0xF535D928,scePower_driver_F535D928
#endif
#ifdef F_scePower_driver_0045
	IMPORT_FUNC	"scePower_driver",0x04B7766E,scePowerRegisterCallback
#endif
#ifdef F_scePower_driver_0046
	IMPORT_FUNC	"scePower_driver",0xDFA8BAF8,scePowerUnregisterCallback
#endif
#ifdef F_scePower_driver_0047
	IMPORT_FUNC	"scePower_driver",0xDB9D28DD,scePowerUnregitserCallback
#endif
#ifdef F_scePower_driver_0048
	IMPORT_FUNC	"scePower_driver",0xD24E6BEB,scePower_driver_D24E6BEB
#endif
#ifdef F_scePower_driver_0049
	IMPORT_FUNC	"scePower_driver",0x35B7662E,scePowerGetSectionDescriptionEntry
#endif
#ifdef F_scePower_driver_0050
	IMPORT_FUNC	"scePower_driver",0xF9B4DEA1,scePowerLimitPllClock
#endif
#ifdef F_scePower_driver_0051
	IMPORT_FUNC	"scePower_driver",0x843FBF43,scePowerSetCpuClockFrequency
#endif
#ifdef F_scePower_driver_0052
	IMPORT_FUNC	"scePower_driver",0xB8D7B3FB,scePowerSetBusClockFrequency
#endif
#ifdef F_scePower_driver_0053
	IMPORT_FUNC	"scePower_driver",0xFEE03A2F,scePowerGetCpuClockFrequency
#endif
#ifdef F_scePower_driver_0054
	IMPORT_FUNC	"scePower_driver",0x478FE6F5,scePowerGetBusClockFrequency
#endif
#ifdef F_scePower_driver_0055
	IMPORT_FUNC	"scePower_driver",0xFDB5BFE9,scePowerGetCpuClockFrequencyInt
#endif
#ifdef F_scePower_driver_0056
	IMPORT_FUNC	"scePower_driver",0xBD681969,scePowerGetBusClockFrequencyInt
#endif
#ifdef F_scePower_driver_0057
	IMPORT_FUNC	"scePower_driver",0xB1A52C83,scePowerGetCpuClockFrequencyFloat
#endif
#ifdef F_scePower_driver_0058
	IMPORT_FUNC	"scePower_driver",0x9BADB3EB,scePowerGetBusClockFrequencyFloat
#endif
#ifdef F_scePower_driver_0059
	IMPORT_FUNC	"scePower_driver",0x737486F2,scePowerSetClockFrequency
#endif
#ifdef F_scePower_driver_0060
	IMPORT_FUNC	"scePower_driver",0xE0B7A95D,scePower_driver_E0B7A95D
#endif
#ifdef F_scePower_driver_0061
	IMPORT_FUNC	"scePower_driver",0xC23AC778,scePower_driver_C23AC778
#endif
#ifdef F_scePower_driver_0062
	IMPORT_FUNC	"scePower_driver",0x23C31FFE,scePowerVolatileMemLock
#endif
#ifdef F_scePower_driver_0063
	IMPORT_FUNC	"scePower_driver",0xFA97A599,scePowerVolatileMemTryLock
#endif
#ifdef F_scePower_driver_0064
	IMPORT_FUNC	"scePower_driver",0xB3EDD801,scePowerVolatileMemUnlock
#endif
