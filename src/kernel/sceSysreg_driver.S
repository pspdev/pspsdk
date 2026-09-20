	.set noreorder

#include "pspimport.s"

#ifdef F_sceSysreg_driver_0000
	IMPORT_START	"sceSysreg_driver",0x00090000
#endif
#ifdef F_sceSysreg_driver_0001
	IMPORT_FUNC	"sceSysreg_driver",0x9C863542,sceSysregInit
#endif
#ifdef F_sceSysreg_driver_0002
	IMPORT_FUNC	"sceSysreg_driver",0xF2DEAA14,sceSysregEnd
#endif
#ifdef F_sceSysreg_driver_0003
	IMPORT_FUNC	"sceSysreg_driver",0xE88B77ED,sceSysregVblankIRQPolar
#endif
#ifdef F_sceSysreg_driver_0004
	IMPORT_FUNC	"sceSysreg_driver",0xCD0F6715,sceSysregDoTimerEvent
#endif
#ifdef F_sceSysreg_driver_0005
	IMPORT_FUNC	"sceSysreg_driver",0x844AF6BD,sceSysregSetMasterPriv
#endif
#ifdef F_sceSysreg_driver_0006
	IMPORT_FUNC	"sceSysreg_driver",0xE2A5D1EE,sceSysregGetTachyonVersion
#endif
#ifdef F_sceSysreg_driver_0007
	IMPORT_FUNC	"sceSysreg_driver",0x4F46EEDE,sceSysregGetFuseId
#endif
#ifdef F_sceSysreg_driver_0008
	IMPORT_FUNC	"sceSysreg_driver",0x8F4F4E96,sceSysregGetFuseConfig
#endif
#ifdef F_sceSysreg_driver_0009
	IMPORT_FUNC	"sceSysreg_driver",0xC29D614E,sceSysregTopResetEnable
#endif
#ifdef F_sceSysreg_driver_0010
	IMPORT_FUNC	"sceSysreg_driver",0xDC6139A4,sceSysregScResetEnable
#endif
#ifdef F_sceSysreg_driver_0011
	IMPORT_FUNC	"sceSysreg_driver",0xDE59DACB,sceSysregMeResetEnable
#endif
#ifdef F_sceSysreg_driver_0012
	IMPORT_FUNC	"sceSysreg_driver",0x2DB0EB28,sceSysregMeResetDisable
#endif
#ifdef F_sceSysreg_driver_0013
	IMPORT_FUNC	"sceSysreg_driver",0x26283A6F,sceSysregAwResetEnable
#endif
#ifdef F_sceSysreg_driver_0014
	IMPORT_FUNC	"sceSysreg_driver",0xA374195E,sceSysregAwResetDisable
#endif
#ifdef F_sceSysreg_driver_0015
	IMPORT_FUNC	"sceSysreg_driver",0xD20581EA,sceSysregVmeResetEnable
#endif
#ifdef F_sceSysreg_driver_0016
	IMPORT_FUNC	"sceSysreg_driver",0x7558064A,sceSysregVmeResetDisable
#endif
#ifdef F_sceSysreg_driver_0017
	IMPORT_FUNC	"sceSysreg_driver",0x9BB70D34,sceSysregAvcResetEnable
#endif
#ifdef F_sceSysreg_driver_0018
	IMPORT_FUNC	"sceSysreg_driver",0xFD6C562B,sceSysregAvcResetDisable
#endif
#ifdef F_sceSysreg_driver_0019
	IMPORT_FUNC	"sceSysreg_driver",0xCD4FB614,sceSysregUsbResetEnable
#endif
#ifdef F_sceSysreg_driver_0020
	IMPORT_FUNC	"sceSysreg_driver",0x69EECBE5,sceSysregUsbResetDisable
#endif
#ifdef F_sceSysreg_driver_0021
	IMPORT_FUNC	"sceSysreg_driver",0xF5B80837,sceSysregAtaResetEnable
#endif
#ifdef F_sceSysreg_driver_0022
	IMPORT_FUNC	"sceSysreg_driver",0x8075303F,sceSysregAtaResetDisable
#endif
#ifdef F_sceSysreg_driver_0023
	IMPORT_FUNC	"sceSysreg_driver",0x00C2628E,sceSysregMsifResetEnable
#endif
#ifdef F_sceSysreg_driver_0024
	IMPORT_FUNC	"sceSysreg_driver",0xEC4BF81F,sceSysregMsifResetDisable
#endif
#ifdef F_sceSysreg_driver_0025
	IMPORT_FUNC	"sceSysreg_driver",0x8A7F9EB4,sceSysregKirkResetEnable
#endif
#ifdef F_sceSysreg_driver_0026
	IMPORT_FUNC	"sceSysreg_driver",0xC32F2491,sceSysregKirkResetDisable
#endif
#ifdef F_sceSysreg_driver_0027
	IMPORT_FUNC	"sceSysreg_driver",0xB21B6CBF,sceSysregPllGetFrequency
#endif
#ifdef F_sceSysreg_driver_0028
	IMPORT_FUNC	"sceSysreg_driver",0xBB3623DF,sceSysregPllUpdateFrequency
#endif
#ifdef F_sceSysreg_driver_0029
	IMPORT_FUNC	"sceSysreg_driver",0x53A6838B,sceSysregPllGetBaseFrequency
#endif
#ifdef F_sceSysreg_driver_0030
	IMPORT_FUNC	"sceSysreg_driver",0xB4560C45,sceSysregPllGetOutSelect
#endif
#ifdef F_sceSysreg_driver_0031
	IMPORT_FUNC	"sceSysreg_driver",0xDCA57573,sceSysregPllSetOutSelect
#endif
#ifdef F_sceSysreg_driver_0032
	IMPORT_FUNC	"sceSysreg_driver",0x44F6CDA7,sceSysregMeBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0033
	IMPORT_FUNC	"sceSysreg_driver",0x158AD4FC,sceSysregMeBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0034
	IMPORT_FUNC	"sceSysreg_driver",0x4D4CE2B8,sceSysregAwRegABusClockEnable
#endif
#ifdef F_sceSysreg_driver_0035
	IMPORT_FUNC	"sceSysreg_driver",0x789BD609,sceSysregAwRegABusClockDisable
#endif
#ifdef F_sceSysreg_driver_0036
	IMPORT_FUNC	"sceSysreg_driver",0x391CE1C0,sceSysregAwRegBBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0037
	IMPORT_FUNC	"sceSysreg_driver",0x82D35024,sceSysregAwRegBBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0038
	IMPORT_FUNC	"sceSysreg_driver",0xAF904657,sceSysregAwEdramBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0039
	IMPORT_FUNC	"sceSysreg_driver",0x438AECE9,sceSysregAwEdramBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0040
	IMPORT_FUNC	"sceSysreg_driver",0x678AD3ED,sceSysregDmacplusBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0041
	IMPORT_FUNC	"sceSysreg_driver",0x168C09B8,sceSysregDmacplusBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0042
	IMPORT_FUNC	"sceSysreg_driver",0x7E7EBC20,sceSysregDmacBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0043
	IMPORT_FUNC	"sceSysreg_driver",0xA265C719,sceSysregDmacBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0044
	IMPORT_FUNC	"sceSysreg_driver",0x4F5AFBBE,sceSysregKirkBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0045
	IMPORT_FUNC	"sceSysreg_driver",0x845DD1A6,sceSysregKirkBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0046
	IMPORT_FUNC	"sceSysreg_driver",0x16909002,sceSysregAtaBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0047
	IMPORT_FUNC	"sceSysreg_driver",0xB6C10DF0,sceSysregAtaBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0048
	IMPORT_FUNC	"sceSysreg_driver",0x3E216017,sceSysregUsbBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0049
	IMPORT_FUNC	"sceSysreg_driver",0xBFBABB63,sceSysregUsbBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0050
	IMPORT_FUNC	"sceSysreg_driver",0x4716E71E,sceSysregMsifBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0051
	IMPORT_FUNC	"sceSysreg_driver",0x826430C0,sceSysregMsifBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0052
	IMPORT_FUNC	"sceSysreg_driver",0x7CC6CBFD,sceSysregEmcddrBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0053
	IMPORT_FUNC	"sceSysreg_driver",0xEE6B9411,sceSysregEmcddrBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0054
	IMPORT_FUNC	"sceSysreg_driver",0xF97D9D73,sceSysregEmcsmBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0055
	IMPORT_FUNC	"sceSysreg_driver",0x2D0F7755,sceSysregEmcsmBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0056
	IMPORT_FUNC	"sceSysreg_driver",0x63B9EB65,sceSysregApbBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0057
	IMPORT_FUNC	"sceSysreg_driver",0xE1AA9788,sceSysregApbBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0058
	IMPORT_FUNC	"sceSysreg_driver",0xAA63C8BD,sceSysregAudioBusClockEnable
#endif
#ifdef F_sceSysreg_driver_0059
	IMPORT_FUNC	"sceSysreg_driver",0x054AC8C6,sceSysregAudioBusClockDisable
#endif
#ifdef F_sceSysreg_driver_0060
	IMPORT_FUNC	"sceSysreg_driver",0x6B01D71B,sceSysregAtaClkEnable
#endif
#ifdef F_sceSysreg_driver_0061
	IMPORT_FUNC	"sceSysreg_driver",0xFC186A83,sceSysregAtaClkDisable
#endif
#ifdef F_sceSysreg_driver_0062
	IMPORT_FUNC	"sceSysreg_driver",0x7234EA80,sceSysregUsbClkEnable
#endif
#ifdef F_sceSysreg_driver_0063
	IMPORT_FUNC	"sceSysreg_driver",0x38EC3281,sceSysregUsbClkDisable
#endif
#ifdef F_sceSysreg_driver_0064
	IMPORT_FUNC	"sceSysreg_driver",0x31154490,sceSysregMsifClkEnable
#endif
#ifdef F_sceSysreg_driver_0065
	IMPORT_FUNC	"sceSysreg_driver",0x8E2D835D,sceSysregMsifClkDisable
#endif
#ifdef F_sceSysreg_driver_0066
	IMPORT_FUNC	"sceSysreg_driver",0x8835D1E1,sceSysregSpiClkEnable
#endif
#ifdef F_sceSysreg_driver_0067
	IMPORT_FUNC	"sceSysreg_driver",0x8B90B8B5,sceSysregSpiClkDisable
#endif
#ifdef F_sceSysreg_driver_0068
	IMPORT_FUNC	"sceSysreg_driver",0x7725CA08,sceSysregUartClkEnable
#endif
#ifdef F_sceSysreg_driver_0069
	IMPORT_FUNC	"sceSysreg_driver",0xA3E4154C,sceSysregUartClkDisable
#endif
#ifdef F_sceSysreg_driver_0070
	IMPORT_FUNC	"sceSysreg_driver",0xE8533DCA,sceSysregApbTimerClkEnable
#endif
#ifdef F_sceSysreg_driver_0071
	IMPORT_FUNC	"sceSysreg_driver",0xF6D83AD0,sceSysregApbTimerClkDisable
#endif
#ifdef F_sceSysreg_driver_0072
	IMPORT_FUNC	"sceSysreg_driver",0xA9CD1C1F,sceSysregAudioClkEnable
#endif
#ifdef F_sceSysreg_driver_0073
	IMPORT_FUNC	"sceSysreg_driver",0x2F216F38,sceSysregAudioClkDisable
#endif
#ifdef F_sceSysreg_driver_0074
	IMPORT_FUNC	"sceSysreg_driver",0xA24C242A,sceSysregLcdcClkEnable
#endif
#ifdef F_sceSysreg_driver_0075
	IMPORT_FUNC	"sceSysreg_driver",0xE89243BE,sceSysregLcdcClkDisable
#endif
#ifdef F_sceSysreg_driver_0076
	IMPORT_FUNC	"sceSysreg_driver",0x7DCA8302,sceSysregPwmClkEnable
#endif
#ifdef F_sceSysreg_driver_0077
	IMPORT_FUNC	"sceSysreg_driver",0x45225F8F,sceSysregPwmClkDisable
#endif
#ifdef F_sceSysreg_driver_0078
	IMPORT_FUNC	"sceSysreg_driver",0xD74D3AB6,sceSysregKeyClkEnable
#endif
#ifdef F_sceSysreg_driver_0079
	IMPORT_FUNC	"sceSysreg_driver",0xAD7C4ACB,sceSysregKeyClkDisable
#endif
#ifdef F_sceSysreg_driver_0080
	IMPORT_FUNC	"sceSysreg_driver",0xDC68A93F,sceSysregIicClkEnable
#endif
#ifdef F_sceSysreg_driver_0081
	IMPORT_FUNC	"sceSysreg_driver",0x94B0323C,sceSysregIicClkDisable
#endif
#ifdef F_sceSysreg_driver_0082
	IMPORT_FUNC	"sceSysreg_driver",0x6417CDD6,sceSysregSircsClkEnable
#endif
#ifdef F_sceSysreg_driver_0083
	IMPORT_FUNC	"sceSysreg_driver",0x20388C9E,sceSysregSircsClkDisable
#endif
#ifdef F_sceSysreg_driver_0084
	IMPORT_FUNC	"sceSysreg_driver",0xE3AECFFA,sceSysregGpioClkEnable
#endif
#ifdef F_sceSysreg_driver_0085
	IMPORT_FUNC	"sceSysreg_driver",0x3BBD0C0C,sceSysregGpioClkDisable
#endif
#ifdef F_sceSysreg_driver_0086
	IMPORT_FUNC	"sceSysreg_driver",0xC1DA05D2,sceSysregAudioClkoutClkEnable
#endif
#ifdef F_sceSysreg_driver_0087
	IMPORT_FUNC	"sceSysreg_driver",0xDE170397,sceSysregAudioClkoutClkDisable
#endif
#ifdef F_sceSysreg_driver_0088
	IMPORT_FUNC	"sceSysreg_driver",0x1969E840,sceSysregMsifClkSelect
#endif
#ifdef F_sceSysreg_driver_0089
	IMPORT_FUNC	"sceSysreg_driver",0x1D382514,sceSysregMsifDelaySelect
#endif
#ifdef F_sceSysreg_driver_0090
	IMPORT_FUNC	"sceSysreg_driver",0x833E6FB1,sceSysregAtaClkSelect
#endif
#ifdef F_sceSysreg_driver_0091
	IMPORT_FUNC	"sceSysreg_driver",0x03340297,sceSysregApbTimerClkSelect
#endif
#ifdef F_sceSysreg_driver_0092
	IMPORT_FUNC	"sceSysreg_driver",0x9100B4E5,sceSysregAudioClkSelect
#endif
#ifdef F_sceSysreg_driver_0093
	IMPORT_FUNC	"sceSysreg_driver",0x0A83FC7B,sceSysregAudioClkoutClkSelect
#endif
#ifdef F_sceSysreg_driver_0094
	IMPORT_FUNC	"sceSysreg_driver",0xD6628A48,sceSysregSpiClkSelect
#endif
#ifdef F_sceSysreg_driver_0095
	IMPORT_FUNC	"sceSysreg_driver",0x1E18EA43,sceSysregLcdcClkSelect
#endif
#ifdef F_sceSysreg_driver_0096
	IMPORT_FUNC	"sceSysreg_driver",0x9DD1F821,sceSysregEmcsmIoEnable
#endif
#ifdef F_sceSysreg_driver_0097
	IMPORT_FUNC	"sceSysreg_driver",0x1C4C4C7A,sceSysregEmcsmIoDisable
#endif
#ifdef F_sceSysreg_driver_0098
	IMPORT_FUNC	"sceSysreg_driver",0xBC68D9B6,sceSysregUsbIoEnable
#endif
#ifdef F_sceSysreg_driver_0099
	IMPORT_FUNC	"sceSysreg_driver",0xA3C8E075,sceSysregUsbIoDisable
#endif
#ifdef F_sceSysreg_driver_0100
	IMPORT_FUNC	"sceSysreg_driver",0x79338EA3,sceSysregAtaIoEnable
#endif
#ifdef F_sceSysreg_driver_0101
	IMPORT_FUNC	"sceSysreg_driver",0xCADB92AA,sceSysregAtaIoDisable
#endif
#ifdef F_sceSysreg_driver_0102
	IMPORT_FUNC	"sceSysreg_driver",0xD74F1D48,sceSysregMsifIoEnable
#endif
#ifdef F_sceSysreg_driver_0103
	IMPORT_FUNC	"sceSysreg_driver",0x18172C6A,sceSysregMsifIoDisable
#endif
#ifdef F_sceSysreg_driver_0104
	IMPORT_FUNC	"sceSysreg_driver",0x63B1AADF,sceSysregLcdcIoEnable
#endif
#ifdef F_sceSysreg_driver_0105
	IMPORT_FUNC	"sceSysreg_driver",0xF74F14E9,sceSysregLcdcIoDisable
#endif
#ifdef F_sceSysreg_driver_0106
	IMPORT_FUNC	"sceSysreg_driver",0xBB26CF1F,sceSysregAudioIoEnable
#endif
#ifdef F_sceSysreg_driver_0107
	IMPORT_FUNC	"sceSysreg_driver",0x8E2FB536,sceSysregAudioIoDisable
#endif
#ifdef F_sceSysreg_driver_0108
	IMPORT_FUNC	"sceSysreg_driver",0x0436B60F,sceSysregIicIoEnable
#endif
#ifdef F_sceSysreg_driver_0109
	IMPORT_FUNC	"sceSysreg_driver",0x58F47EFD,sceSysregIicIoDisable
#endif
#ifdef F_sceSysreg_driver_0110
	IMPORT_FUNC	"sceSysreg_driver",0x4C49A8BC,sceSysregSircsIoEnable
#endif
#ifdef F_sceSysreg_driver_0111
	IMPORT_FUNC	"sceSysreg_driver",0x26FA0928,sceSysregSircsIoDisable
#endif
#ifdef F_sceSysreg_driver_0112
	IMPORT_FUNC	"sceSysreg_driver",0xF844DDF3,sceSysregAudioClkoutIoEnable
#endif
#ifdef F_sceSysreg_driver_0113
	IMPORT_FUNC	"sceSysreg_driver",0x29A119A1,sceSysregAudioClkoutIoDisable
#endif
#ifdef F_sceSysreg_driver_0114
	IMPORT_FUNC	"sceSysreg_driver",0x77DED992,sceSysregKeyIoEnable
#endif
#ifdef F_sceSysreg_driver_0115
	IMPORT_FUNC	"sceSysreg_driver",0x6879790B,sceSysregKeyIoDisable
#endif
#ifdef F_sceSysreg_driver_0116
	IMPORT_FUNC	"sceSysreg_driver",0x7A5D2D15,sceSysregPwmIoEnable
#endif
#ifdef F_sceSysreg_driver_0117
	IMPORT_FUNC	"sceSysreg_driver",0x25B0AC52,sceSysregPwmIoDisable
#endif
#ifdef F_sceSysreg_driver_0118
	IMPORT_FUNC	"sceSysreg_driver",0x7FD7A631,sceSysregUartIoEnable
#endif
#ifdef F_sceSysreg_driver_0119
	IMPORT_FUNC	"sceSysreg_driver",0xBB823481,sceSysregUartIoDisable
#endif
#ifdef F_sceSysreg_driver_0120
	IMPORT_FUNC	"sceSysreg_driver",0x8C5C53DE,sceSysregSpiIoEnable
#endif
#ifdef F_sceSysreg_driver_0121
	IMPORT_FUNC	"sceSysreg_driver",0xA16E55F4,sceSysregSpiIoDisable
#endif
#ifdef F_sceSysreg_driver_0122
	IMPORT_FUNC	"sceSysreg_driver",0xB627582E,sceSysregGpioIoEnable
#endif
#ifdef F_sceSysreg_driver_0123
	IMPORT_FUNC	"sceSysreg_driver",0x1E9C3607,sceSysregGpioIoDisable
#endif
#ifdef F_sceSysreg_driver_0124
	IMPORT_FUNC	"sceSysreg_driver",0x55B18B84,sceSysreg_driver_55B18B84
#endif
#ifdef F_sceSysreg_driver_0125
	IMPORT_FUNC	"sceSysreg_driver",0x2112E686,sceSysreg_driver_2112E686
#endif
#ifdef F_sceSysreg_driver_0126
	IMPORT_FUNC	"sceSysreg_driver",0x7B9E9A53,sceSysreg_driver_7B9E9A53
#endif
#ifdef F_sceSysreg_driver_0127
	IMPORT_FUNC	"sceSysreg_driver",0x7BDF0556,sceSysreg_driver_7BDF0556
#endif
#ifdef F_sceSysreg_driver_0128
	IMPORT_FUNC	"sceSysreg_driver",0x8D0FED1E,sceSysreg_driver_8D0FED1E
#endif
#ifdef F_sceSysreg_driver_0129
	IMPORT_FUNC	"sceSysreg_driver",0xA46E9CA8,sceSysreg_driver_A46E9CA8
#endif
#ifdef F_sceSysreg_driver_0130
	IMPORT_FUNC	"sceSysreg_driver",0x633595F2,sceSysregUsbGetConnectStatus
#endif
#ifdef F_sceSysreg_driver_0131
	IMPORT_FUNC	"sceSysreg_driver",0x32471457,sceSysregUsbQueryIntr
#endif
#ifdef F_sceSysreg_driver_0132
	IMPORT_FUNC	"sceSysreg_driver",0x692F31FF,sceSysregUsbAcquireIntr
#endif
#ifdef F_sceSysreg_driver_0133
	IMPORT_FUNC	"sceSysreg_driver",0xD43E98F6,sceSysregMsifGetConnectStatus
#endif
#ifdef F_sceSysreg_driver_0134
	IMPORT_FUNC	"sceSysreg_driver",0xBF91FBDA,sceSysregMsifQueryConnectIntr
#endif
#ifdef F_sceSysreg_driver_0135
	IMPORT_FUNC	"sceSysreg_driver",0x36A75390,sceSysregMsifAcquireConnectIntr
#endif
#ifdef F_sceSysreg_driver_0136
	IMPORT_FUNC	"sceSysreg_driver",0x25673620,sceSysregIntrInit
#endif
#ifdef F_sceSysreg_driver_0137
	IMPORT_FUNC	"sceSysreg_driver",0x4EE8E2C8,sceSysregIntrEnd
#endif
#ifdef F_sceSysreg_driver_0138
	IMPORT_FUNC	"sceSysreg_driver",0x61BFF85F,sceSysregInterruptToOther
#endif
#ifdef F_sceSysreg_driver_0139
	IMPORT_FUNC	"sceSysreg_driver",0x9FC87ED4,sceSysregSemaTryLock
#endif
#ifdef F_sceSysreg_driver_0140
	IMPORT_FUNC	"sceSysreg_driver",0x8BE2D520,sceSysregSemaUnlock
#endif
#ifdef F_sceSysreg_driver_0141
	IMPORT_FUNC	"sceSysreg_driver",0x083F56E2,sceSysregEnableIntr
#endif
#ifdef F_sceSysreg_driver_0142
	IMPORT_FUNC	"sceSysreg_driver",0x7C5B543C,sceSysregDisableIntr
#endif
#ifdef F_sceSysreg_driver_0143
	IMPORT_FUNC	"sceSysreg_driver",0x3EA188AD,sceSysregRequestIntr
#endif
#ifdef F_sceSysreg_driver_0144
	IMPORT_FUNC	"sceSysreg_driver",0x5664F8B5,sceClkcSetCpuGear
#endif
#ifdef F_sceSysreg_driver_0145
	IMPORT_FUNC	"sceSysreg_driver",0x44704E1D,sceClkcGetCpuGear
#endif
#ifdef F_sceSysreg_driver_0146
	IMPORT_FUNC	"sceSysreg_driver",0x584AD989,sceClkcSetBusGear
#endif
#ifdef F_sceSysreg_driver_0147
	IMPORT_FUNC	"sceSysreg_driver",0x377F035F,sceClkcGetBusGear
#endif
#ifdef F_sceSysreg_driver_0148
	IMPORT_FUNC	"sceSysreg_driver",0xAB3185FD,sceClkcSetCpuFrequency
#endif
#ifdef F_sceSysreg_driver_0149
	IMPORT_FUNC	"sceSysreg_driver",0x0EA487FA,sceClkcGetCpuFrequency
#endif
#ifdef F_sceSysreg_driver_0150
	IMPORT_FUNC	"sceSysreg_driver",0x136E8F5A,sceClkcSetBusFrequency
#endif
#ifdef F_sceSysreg_driver_0151
	IMPORT_FUNC	"sceSysreg_driver",0xF4811E00,sceClkcGetBusFrequency
#endif
