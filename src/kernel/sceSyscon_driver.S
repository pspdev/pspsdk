	.set noreorder

#include "pspimport.s"

#ifdef F_sceSyscon_driver_0000
	IMPORT_START	"sceSyscon_driver",0x00010000
#endif
#ifdef F_sceSyscon_driver_0001
	IMPORT_FUNC	"sceSyscon_driver",0x0A771482,sceSysconInit
#endif
#ifdef F_sceSyscon_driver_0002
	IMPORT_FUNC	"sceSyscon_driver",0x92D16FC7,sceSysconEnd
#endif
#ifdef F_sceSyscon_driver_0003
	IMPORT_FUNC	"sceSyscon_driver",0x081826B4,sceSysconSuspend
#endif
#ifdef F_sceSyscon_driver_0004
	IMPORT_FUNC	"sceSyscon_driver",0x56931095,sceSysconResume
#endif
#ifdef F_sceSyscon_driver_0005
	IMPORT_FUNC	"sceSyscon_driver",0x5EE92F3C,sceSyscon_driver_5EE92F3C
#endif
#ifdef F_sceSyscon_driver_0006
	IMPORT_FUNC	"sceSyscon_driver",0x5FF1D610,sceSyscon_driver_5FF1D610
#endif
#ifdef F_sceSyscon_driver_0007
	IMPORT_FUNC	"sceSyscon_driver",0xAD555CE5,sceSyscon_driver_AD555CE5
#endif
#ifdef F_sceSyscon_driver_0008
	IMPORT_FUNC	"sceSyscon_driver",0xF281805D,sceSyscon_driver_F281805D
#endif
#ifdef F_sceSyscon_driver_0009
	IMPORT_FUNC	"sceSyscon_driver",0xA068B3D0,sceSysconSetAlarmCallback
#endif
#ifdef F_sceSyscon_driver_0010
	IMPORT_FUNC	"sceSyscon_driver",0xE540E532,sceSyscon_driver_E540E532
#endif
#ifdef F_sceSyscon_driver_0011
	IMPORT_FUNC	"sceSyscon_driver",0xBBFB70C0,sceSyscon_driver_BBFB70C0
#endif
#ifdef F_sceSyscon_driver_0012
	IMPORT_FUNC	"sceSyscon_driver",0x805180D1,sceSyscon_driver_805180D1
#endif
#ifdef F_sceSyscon_driver_0013
	IMPORT_FUNC	"sceSyscon_driver",0x53072985,sceSyscon_driver_53072985
#endif
#ifdef F_sceSyscon_driver_0014
	IMPORT_FUNC	"sceSyscon_driver",0xF9193EC3,sceSyscon_driver_F9193EC3
#endif
#ifdef F_sceSyscon_driver_0015
	IMPORT_FUNC	"sceSyscon_driver",0x7479DB05,sceSyscon_driver_7479DB05
#endif
#ifdef F_sceSyscon_driver_0016
	IMPORT_FUNC	"sceSyscon_driver",0x6848D817,sceSyscon_driver_6848D817
#endif
#ifdef F_sceSyscon_driver_0017
	IMPORT_FUNC	"sceSyscon_driver",0x5B9ACC97,sceSysconCmdExec
#endif
#ifdef F_sceSyscon_driver_0018
	IMPORT_FUNC	"sceSyscon_driver",0x3AC3D2A4,sceSysconCmdExecAsync
#endif
#ifdef F_sceSyscon_driver_0019
	IMPORT_FUNC	"sceSyscon_driver",0x1602ED0D,sceSysconCmdCancel
#endif
#ifdef F_sceSyscon_driver_0020
	IMPORT_FUNC	"sceSyscon_driver",0xF350F666,sceSysconCmdSync
#endif
#ifdef F_sceSyscon_driver_0021
	IMPORT_FUNC	"sceSyscon_driver",0x86D4CAD8,sceSyscon_driver_86D4CAD8
#endif
#ifdef F_sceSyscon_driver_0022
	IMPORT_FUNC	"sceSyscon_driver",0x32CFD20F,sceSysconIsLowBattery
#endif
#ifdef F_sceSyscon_driver_0023
	IMPORT_FUNC	"sceSyscon_driver",0xEC0DE439,sceSysconGetPowerSwitch
#endif
#ifdef F_sceSyscon_driver_0024
	IMPORT_FUNC	"sceSyscon_driver",0xEA5B9823,sceSyscon_driver_EA5B9823
#endif
#ifdef F_sceSyscon_driver_0025
	IMPORT_FUNC	"sceSyscon_driver",0xE20D08FE,sceSyscon_driver_E20D08FE
#endif
#ifdef F_sceSyscon_driver_0026
	IMPORT_FUNC	"sceSyscon_driver",0xE0DDFE18,sceSysconGetHPConnect
#endif
#ifdef F_sceSyscon_driver_0027
	IMPORT_FUNC	"sceSyscon_driver",0xBDA16E46,sceSysconGetWlanSwitch
#endif
#ifdef F_sceSyscon_driver_0028
	IMPORT_FUNC	"sceSyscon_driver",0xF6BB4649,sceSysconGetHoldSwitch
#endif
#ifdef F_sceSyscon_driver_0029
	IMPORT_FUNC	"sceSyscon_driver",0x138747DE,sceSysconGetUmdSwitch
#endif
#ifdef F_sceSyscon_driver_0030
	IMPORT_FUNC	"sceSyscon_driver",0x71AE1BCE,sceSyscon_driver_71AE1BCE
#endif
#ifdef F_sceSyscon_driver_0031
	IMPORT_FUNC	"sceSyscon_driver",0x7016161C,sceSysconGetWlanPowerStatus
#endif
#ifdef F_sceSyscon_driver_0032
	IMPORT_FUNC	"sceSyscon_driver",0x48AB0E44,sceSysconGetLeptonPowerCtrl
#endif
#ifdef F_sceSyscon_driver_0033
	IMPORT_FUNC	"sceSyscon_driver",0x628F2351,sceSysconGetMsPowerCtrl
#endif
#ifdef F_sceSyscon_driver_0034
	IMPORT_FUNC	"sceSyscon_driver",0x3C739F57,sceSyscon_driver_3C739F57
#endif
#ifdef F_sceSyscon_driver_0035
	IMPORT_FUNC	"sceSyscon_driver",0xEC37C549,sceSysconGetWlanPowerCtrl
#endif
#ifdef F_sceSyscon_driver_0036
	IMPORT_FUNC	"sceSyscon_driver",0x8DDA4CA6,sceSyscon_driver_8DDA4CA6
#endif
#ifdef F_sceSyscon_driver_0037
	IMPORT_FUNC	"sceSyscon_driver",0x52B74B6C,sceSyscon_driver_52B74B6C
#endif
#ifdef F_sceSyscon_driver_0038
	IMPORT_FUNC	"sceSyscon_driver",0x1B17D3E3,sceSyscon_driver_1B17D3E3
#endif
#ifdef F_sceSyscon_driver_0039
	IMPORT_FUNC	"sceSyscon_driver",0x5F19C00F,sceSyscon_driver_5F19C00F
#endif
#ifdef F_sceSyscon_driver_0040
	IMPORT_FUNC	"sceSyscon_driver",0xCC04A978,sceSysconGetWlanLedCtrl
#endif
#ifdef F_sceSyscon_driver_0041
	IMPORT_FUNC	"sceSyscon_driver",0xE6B74CB9,sceSysconNop
#endif
#ifdef F_sceSyscon_driver_0042
	IMPORT_FUNC	"sceSyscon_driver",0x7EC5A957,sceSyscon_driver_7EC5A957
#endif
#ifdef F_sceSyscon_driver_0043
	IMPORT_FUNC	"sceSyscon_driver",0x7BCC5EAE,sceSyscon_driver_7BCC5EAE
#endif
#ifdef F_sceSyscon_driver_0044
	IMPORT_FUNC	"sceSyscon_driver",0x3B657A27,sceSyscon_driver_3B657A27
#endif
#ifdef F_sceSyscon_driver_0045
	IMPORT_FUNC	"sceSyscon_driver",0xFC32141A,sceSyscon_driver_FC32141A
#endif
#ifdef F_sceSyscon_driver_0046
	IMPORT_FUNC	"sceSyscon_driver",0xF775BC34,sceSyscon_driver_F775BC34
#endif
#ifdef F_sceSyscon_driver_0047
	IMPORT_FUNC	"sceSyscon_driver",0xA9AEF39F,sceSyscon_driver_A9AEF39F
#endif
#ifdef F_sceSyscon_driver_0048
	IMPORT_FUNC	"sceSyscon_driver",0xC4D66C1D,sceSysconReadClock
#endif
#ifdef F_sceSyscon_driver_0049
	IMPORT_FUNC	"sceSyscon_driver",0xC7634A7A,sceSysconWriteClock
#endif
#ifdef F_sceSyscon_driver_0050
	IMPORT_FUNC	"sceSyscon_driver",0x7A805EE4,sceSysconReadAlarm
#endif
#ifdef F_sceSyscon_driver_0051
	IMPORT_FUNC	"sceSyscon_driver",0x6C911742,sceSysconWriteAlarm
#endif
#ifdef F_sceSyscon_driver_0052
	IMPORT_FUNC	"sceSyscon_driver",0x65EB6096,sceSyscon_driver_65EB6096
#endif
#ifdef F_sceSyscon_driver_0053
	IMPORT_FUNC	"sceSyscon_driver",0xEB277C88,sceSyscon_driver_EB277C88
#endif
#ifdef F_sceSyscon_driver_0054
	IMPORT_FUNC	"sceSyscon_driver",0x992C22C2,sceSysconSendSetParam
#endif
#ifdef F_sceSyscon_driver_0055
	IMPORT_FUNC	"sceSyscon_driver",0x08234E6D,sceSysconReceiveSetParam
#endif
#ifdef F_sceSyscon_driver_0056
	IMPORT_FUNC	"sceSyscon_driver",0x882F0AAB,sceSyscon_driver_882F0AAB
#endif
#ifdef F_sceSyscon_driver_0057
	IMPORT_FUNC	"sceSyscon_driver",0x2EE82492,sceSyscon_driver_2EE82492
#endif
#ifdef F_sceSyscon_driver_0058
	IMPORT_FUNC	"sceSyscon_driver",0x8CBC7987,sceSysconResetDevice
#endif
#ifdef F_sceSyscon_driver_0059
	IMPORT_FUNC	"sceSyscon_driver",0x00E7B6C2,sceSyscon_driver_00E7B6C2
#endif
#ifdef F_sceSyscon_driver_0060
	IMPORT_FUNC	"sceSyscon_driver",0x44439604,sceSysconCtrlHRPower
#endif
#ifdef F_sceSyscon_driver_0061
	IMPORT_FUNC	"sceSyscon_driver",0xC8439C57,sceSysconPowerStandby
#endif
#ifdef F_sceSyscon_driver_0062
	IMPORT_FUNC	"sceSyscon_driver",0x91E183CB,sceSysconPowerSuspend
#endif
#ifdef F_sceSyscon_driver_0063
	IMPORT_FUNC	"sceSyscon_driver",0xE7E87741,sceSyscon_driver_E7E87741
#endif
#ifdef F_sceSyscon_driver_0064
	IMPORT_FUNC	"sceSyscon_driver",0xFB148FB6,sceSyscon_driver_FB148FB6
#endif
#ifdef F_sceSyscon_driver_0065
	IMPORT_FUNC	"sceSyscon_driver",0x01677F91,sceSyscon_driver_01677F91
#endif
#ifdef F_sceSyscon_driver_0066
	IMPORT_FUNC	"sceSyscon_driver",0xBE27FE66,sceSysconCtrlPower
#endif
#ifdef F_sceSyscon_driver_0067
	IMPORT_FUNC	"sceSyscon_driver",0x09721F7F,sceSysconGetPowerStatus
#endif
#ifdef F_sceSyscon_driver_0068
	IMPORT_FUNC	"sceSyscon_driver",0x18BFBE65,sceSysconCtrlLED
#endif
#ifdef F_sceSyscon_driver_0069
	IMPORT_FUNC	"sceSyscon_driver",0xD1B501E8,sceSyscon_driver_D1B501E8
#endif
#ifdef F_sceSyscon_driver_0070
	IMPORT_FUNC	"sceSyscon_driver",0x3DE38336,sceSyscon_driver_3DE38336
#endif
#ifdef F_sceSyscon_driver_0071
	IMPORT_FUNC	"sceSyscon_driver",0x2B9E6A06,sceSysconGetPowerError
#endif
#ifdef F_sceSyscon_driver_0072
	IMPORT_FUNC	"sceSyscon_driver",0x8A4519F5,sceSysconCtrlLeptonPower
#endif
#ifdef F_sceSyscon_driver_0073
	IMPORT_FUNC	"sceSyscon_driver",0x99BBB24C,sceSysconCtrlMsPower
#endif
#ifdef F_sceSyscon_driver_0074
	IMPORT_FUNC	"sceSyscon_driver",0xF0ED3255,sceSysconCtrlWlanPower
#endif
#ifdef F_sceSyscon_driver_0075
	IMPORT_FUNC	"sceSyscon_driver",0x3C6DB1C5,sceSyscon_driver_3C6DB1C5
#endif
#ifdef F_sceSyscon_driver_0076
	IMPORT_FUNC	"sceSyscon_driver",0xB2558E37,sceSyscon_driver_B2558E37
#endif
#ifdef F_sceSyscon_driver_0077
	IMPORT_FUNC	"sceSyscon_driver",0xE5E35721,sceSyscon_driver_E5E35721
#endif
#ifdef F_sceSyscon_driver_0078
	IMPORT_FUNC	"sceSyscon_driver",0x9478F399,sceSyscon_driver_9478F399
#endif
#ifdef F_sceSyscon_driver_0079
	IMPORT_FUNC	"sceSyscon_driver",0x806D4D6C,sceSyscon_driver_806D4D6C
#endif
#ifdef F_sceSyscon_driver_0080
	IMPORT_FUNC	"sceSyscon_driver",0xD8471760,sceSyscon_driver_D8471760
#endif
#ifdef F_sceSyscon_driver_0081
	IMPORT_FUNC	"sceSyscon_driver",0xEAB13FBE,sceSyscon_driver_EAB13FBE
#endif
#ifdef F_sceSyscon_driver_0082
	IMPORT_FUNC	"sceSyscon_driver",0xC5075828,sceSyscon_driver_C5075828
#endif
#ifdef F_sceSyscon_driver_0083
	IMPORT_FUNC	"sceSyscon_driver",0xE448FD3F,sceSysconBatteryNop
#endif
#ifdef F_sceSyscon_driver_0084
	IMPORT_FUNC	"sceSyscon_driver",0x6A53F3F8,sceSysconBatteryGetStatusCap
#endif
#ifdef F_sceSyscon_driver_0085
	IMPORT_FUNC	"sceSyscon_driver",0x70C10E61,sceSysconBatteryGetTemp
#endif
#ifdef F_sceSyscon_driver_0086
	IMPORT_FUNC	"sceSyscon_driver",0x8BDEBB1E,sceSysconBatteryGetVolt
#endif
#ifdef F_sceSyscon_driver_0087
	IMPORT_FUNC	"sceSyscon_driver",0x373EC933,sceSysconBatteryGetElec
#endif
#ifdef F_sceSyscon_driver_0088
	IMPORT_FUNC	"sceSyscon_driver",0x82861DE2,sceSyscon_driver_82861DE2
#endif
#ifdef F_sceSyscon_driver_0089
	IMPORT_FUNC	"sceSyscon_driver",0x876CA580,sceSysconBatteryGetCap
#endif
#ifdef F_sceSyscon_driver_0090
	IMPORT_FUNC	"sceSyscon_driver",0x71135D7D,sceSyscon_driver_71135D7D
#endif
#ifdef F_sceSyscon_driver_0091
	IMPORT_FUNC	"sceSyscon_driver",0x7CBD4522,sceSyscon_driver_7CBD4522
#endif
#ifdef F_sceSyscon_driver_0092
	IMPORT_FUNC	"sceSyscon_driver",0x284FE366,sceSyscon_driver_284FE366
#endif
#ifdef F_sceSyscon_driver_0093
	IMPORT_FUNC	"sceSyscon_driver",0x75025299,sceSysconBatteryGetStatus
#endif
#ifdef F_sceSyscon_driver_0094
	IMPORT_FUNC	"sceSyscon_driver",0xB5105D51,sceSysconBatteryGetCycle
#endif
#ifdef F_sceSyscon_driver_0095
	IMPORT_FUNC	"sceSyscon_driver",0xD5340103,sceSysconBatteryGetSerial
#endif
#ifdef F_sceSyscon_driver_0096
	IMPORT_FUNC	"sceSyscon_driver",0xFA4C4518,sceSysconBatteryGetInfo
#endif
#ifdef F_sceSyscon_driver_0097
	IMPORT_FUNC	"sceSyscon_driver",0xB71B98A8,sceSyscon_driver_B71B98A8
#endif
#ifdef F_sceSyscon_driver_0098
	IMPORT_FUNC	"sceSyscon_driver",0x87671B18,sceSyscon_driver_87671B18
#endif
#ifdef F_sceSyscon_driver_0099
	IMPORT_FUNC	"sceSyscon_driver",0x75D22BF8,sceSyscon_driver_75D22BF8
#endif
#ifdef F_sceSyscon_driver_0100
	IMPORT_FUNC	"sceSyscon_driver",0x4C539345,sceSyscon_driver_4C539345
#endif
#ifdef F_sceSyscon_driver_0101
	IMPORT_FUNC	"sceSyscon_driver",0x4C0EE2FA,sceSyscon_driver_4C0EE2FA
#endif
#ifdef F_sceSyscon_driver_0102
	IMPORT_FUNC	"sceSyscon_driver",0x1165C864,sceSyscon_driver_1165C864
#endif
#ifdef F_sceSyscon_driver_0103
	IMPORT_FUNC	"sceSyscon_driver",0x68EF0BEF,sceSyscon_driver_68EF0BEF
#endif
#ifdef F_sceSyscon_driver_0104
	IMPORT_FUNC	"sceSyscon_driver",0x36E28C5F,sceSysconBatteryAuth
#endif
#ifdef F_sceSyscon_driver_0105
	IMPORT_FUNC	"sceSyscon_driver",0x08DA3752,sceSyscon_driver_08DA3752
#endif
#ifdef F_sceSyscon_driver_0106
	IMPORT_FUNC	"sceSyscon_driver",0x9C4E3CA9,sceSyscon_driver_9C4E3CA9
#endif
#ifdef F_sceSyscon_driver_0107
	IMPORT_FUNC	"sceSyscon_driver",0x34C36FF9,sceSyscon_driver_34C36FF9
#endif
#ifdef F_sceSyscon_driver_0108
	IMPORT_FUNC	"sceSyscon_driver",0xB8919D79,sceSysconMsOn
#endif
#ifdef F_sceSyscon_driver_0109
	IMPORT_FUNC	"sceSyscon_driver",0x7BE86143,sceSysconMsOff
#endif
#ifdef F_sceSyscon_driver_0110
	IMPORT_FUNC	"sceSyscon_driver",0x0E8560F9,sceSysconWlanOn
#endif
#ifdef F_sceSyscon_driver_0111
	IMPORT_FUNC	"sceSyscon_driver",0x1B60C8AD,sceSysconWlanOff
#endif
#ifdef F_sceSyscon_driver_0112
	IMPORT_FUNC	"sceSyscon_driver",0xE00BFC9E,sceSyscon_driver_E00BFC9E
#endif
#ifdef F_sceSyscon_driver_0113
	IMPORT_FUNC	"sceSyscon_driver",0xC8D97773,sceSyscon_driver_C8D97773
#endif
