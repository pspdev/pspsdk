	.set noreorder

#include "pspimport.s"

#ifdef F_sceRtc_driver_0000
	IMPORT_START	"sceRtc_driver",0x00010000
#endif
#ifdef F_sceRtc_driver_0001
	IMPORT_FUNC	"sceRtc_driver",0xC41C2853,sceRtcGetTickResolution
#endif
#ifdef F_sceRtc_driver_0002
	IMPORT_FUNC	"sceRtc_driver",0x3F7AD767,sceRtcGetCurrentTick
#endif
#ifdef F_sceRtc_driver_0003
	IMPORT_FUNC	"sceRtc_driver",0x029CA3B3,sceRtc_029CA3B3
#endif
#ifdef F_sceRtc_driver_0004
	IMPORT_FUNC	"sceRtc_driver",0x4CFA57B0,sceRtcGetCurrentClock
#endif
#ifdef F_sceRtc_driver_0005
	IMPORT_FUNC	"sceRtc_driver",0xE7C27D1B,sceRtcGetCurrentClockLocalTime
#endif
#ifdef F_sceRtc_driver_0006
	IMPORT_FUNC	"sceRtc_driver",0x34885E0D,sceRtcConvertUtcToLocalTime
#endif
#ifdef F_sceRtc_driver_0007
	IMPORT_FUNC	"sceRtc_driver",0x779242A2,sceRtcConvertLocalTimeToUTC
#endif
#ifdef F_sceRtc_driver_0008
	IMPORT_FUNC	"sceRtc_driver",0x42307A17,sceRtcIsLeapYear
#endif
#ifdef F_sceRtc_driver_0009
	IMPORT_FUNC	"sceRtc_driver",0x05EF322C,sceRtcGetDaysInMonth
#endif
#ifdef F_sceRtc_driver_0010
	IMPORT_FUNC	"sceRtc_driver",0x57726BC1,sceRtcGetDayOfWeek
#endif
#ifdef F_sceRtc_driver_0011
	IMPORT_FUNC	"sceRtc_driver",0x4B1B5E82,sceRtcCheckValid
#endif
#ifdef F_sceRtc_driver_0012
	IMPORT_FUNC	"sceRtc_driver",0x3A807CC8,sceRtcSetTime_t
#endif
#ifdef F_sceRtc_driver_0013
	IMPORT_FUNC	"sceRtc_driver",0x27C4594C,sceRtcGetTime_t
#endif
#ifdef F_sceRtc_driver_0014
	IMPORT_FUNC	"sceRtc_driver",0xF006F264,sceRtcSetDosTime
#endif
#ifdef F_sceRtc_driver_0015
	IMPORT_FUNC	"sceRtc_driver",0x36075567,sceRtcGetDosTime
#endif
#ifdef F_sceRtc_driver_0016
	IMPORT_FUNC	"sceRtc_driver",0x7ACE4C04,sceRtcSetWin32FileTime
#endif
#ifdef F_sceRtc_driver_0017
	IMPORT_FUNC	"sceRtc_driver",0xCF561893,sceRtcGetWin32FileTime
#endif
#ifdef F_sceRtc_driver_0018
	IMPORT_FUNC	"sceRtc_driver",0x7ED29E40,sceRtcSetTick
#endif
#ifdef F_sceRtc_driver_0019
	IMPORT_FUNC	"sceRtc_driver",0x6FF40ACC,sceRtcGetTick
#endif
#ifdef F_sceRtc_driver_0020
	IMPORT_FUNC	"sceRtc_driver",0x9ED0AE87,sceRtcCompareTick
#endif
#ifdef F_sceRtc_driver_0021
	IMPORT_FUNC	"sceRtc_driver",0x44F45E05,sceRtcTickAddTicks
#endif
#ifdef F_sceRtc_driver_0022
	IMPORT_FUNC	"sceRtc_driver",0x26D25A5D,sceRtcTickAddMicroseconds
#endif
#ifdef F_sceRtc_driver_0023
	IMPORT_FUNC	"sceRtc_driver",0xF2A4AFE5,sceRtcTickAddSeconds
#endif
#ifdef F_sceRtc_driver_0024
	IMPORT_FUNC	"sceRtc_driver",0xE6605BCA,sceRtcTickAddMinutes
#endif
#ifdef F_sceRtc_driver_0025
	IMPORT_FUNC	"sceRtc_driver",0x26D7A24A,sceRtcTickAddHours
#endif
#ifdef F_sceRtc_driver_0026
	IMPORT_FUNC	"sceRtc_driver",0xE51B4B7A,sceRtcTickAddDays
#endif
#ifdef F_sceRtc_driver_0027
	IMPORT_FUNC	"sceRtc_driver",0xCF3A2CA8,sceRtcTickAddWeeks
#endif
#ifdef F_sceRtc_driver_0028
	IMPORT_FUNC	"sceRtc_driver",0xDBF74F1B,sceRtcTickAddMonths
#endif
#ifdef F_sceRtc_driver_0029
	IMPORT_FUNC	"sceRtc_driver",0x42842C77,sceRtcTickAddYears
#endif
#ifdef F_sceRtc_driver_0030
	IMPORT_FUNC	"sceRtc_driver",0xC663B3B9,sceRtcFormatRFC2822
#endif
#ifdef F_sceRtc_driver_0031
	IMPORT_FUNC	"sceRtc_driver",0x7DE6711B,sceRtcFormatRFC2822LocalTime
#endif
#ifdef F_sceRtc_driver_0032
	IMPORT_FUNC	"sceRtc_driver",0x0498FB3C,sceRtcFormatRFC3339
#endif
#ifdef F_sceRtc_driver_0033
	IMPORT_FUNC	"sceRtc_driver",0x27F98543,sceRtcFormatRFC3339LocalTime
#endif
#ifdef F_sceRtc_driver_0034
	IMPORT_FUNC	"sceRtc_driver",0xDFBC5F16,sceRtcParseDateTime
#endif
#ifdef F_sceRtc_driver_0035
	IMPORT_FUNC	"sceRtc_driver",0x28E1E988,sceRtcParseRFC3339
#endif
#ifdef F_sceRtc_driver_0036
	IMPORT_FUNC	"sceRtc_driver",0x011F03C1,sceRtcGetAccumulativeTime
#endif
#ifdef F_sceRtc_driver_0037
	IMPORT_FUNC	"sceRtc_driver",0x17C26C00,sceRtc_driver_17C26C00
#endif
#ifdef F_sceRtc_driver_0038
	IMPORT_FUNC	"sceRtc_driver",0x1909C99B,sceRtcSetTime64_t
#endif
#ifdef F_sceRtc_driver_0039
	IMPORT_FUNC	"sceRtc_driver",0x203CEB0D,sceRtcGetLastReincarnatedTime
#endif
#ifdef F_sceRtc_driver_0040
	IMPORT_FUNC	"sceRtc_driver",0x48D07D70,sceRtcResume
#endif
#ifdef F_sceRtc_driver_0041
	IMPORT_FUNC	"sceRtc_driver",0x62685E98,sceRtcGetLastAdjustedTime
#endif
#ifdef F_sceRtc_driver_0042
	IMPORT_FUNC	"sceRtc_driver",0x6A676D2D,sceRtc_driver_6A676D2D
#endif
#ifdef F_sceRtc_driver_0043
	IMPORT_FUNC	"sceRtc_driver",0x759937C5,sceRtcSetConf
#endif
#ifdef F_sceRtc_driver_0044
	IMPORT_FUNC	"sceRtc_driver",0x7D1FBED3,sceRtcSetAlarmTick
#endif
#ifdef F_sceRtc_driver_0045
	IMPORT_FUNC	"sceRtc_driver",0x81FCDA34,sceRtc_driver_81FCDA34
#endif
#ifdef F_sceRtc_driver_0046
	IMPORT_FUNC	"sceRtc_driver",0x912BEE56,sceRtcInit
#endif
#ifdef F_sceRtc_driver_0047
	IMPORT_FUNC	"sceRtc_driver",0x9763C138,sceRtcSetCurrentTick
#endif
#ifdef F_sceRtc_driver_0048
	IMPORT_FUNC	"sceRtc_driver",0x9CC2797E,sceRtcSuspend
#endif
#ifdef F_sceRtc_driver_0049
	IMPORT_FUNC	"sceRtc_driver",0xB44BDAED,sceRtc_driver_B44BDAED
#endif
#ifdef F_sceRtc_driver_0050
	IMPORT_FUNC	"sceRtc_driver",0xC2DDBEB5,sceRtcGetAlarmTick
#endif
#ifdef F_sceRtc_driver_0051
	IMPORT_FUNC	"sceRtc_driver",0xC499AF2F,sceRtc_driver_C499AF2F
#endif
#ifdef F_sceRtc_driver_0052
	IMPORT_FUNC	"sceRtc_driver",0xCE27DE2F,sceRtcEnd
#endif
#ifdef F_sceRtc_driver_0053
	IMPORT_FUNC	"sceRtc_driver",0xDFBC5F16,sceRtcParseDateTime
#endif
#ifdef F_sceRtc_driver_0054
	IMPORT_FUNC	"sceRtc_driver",0xE1C93E47,sceRtcGetTime64_t
#endif
#ifdef F_sceRtc_driver_0055
	IMPORT_FUNC	"sceRtc_driver",0xF0B5571C,sceRtcSynchronize
#endif
#ifdef F_sceRtc_driver_0056
	IMPORT_FUNC	"sceRtc_driver",0xFB3B18CD,sceRtc_driver_FB3B18CD
#endif

