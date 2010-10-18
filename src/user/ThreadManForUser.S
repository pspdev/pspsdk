	.set noreorder

#include "pspimport.s"

#ifdef F_ThreadManForUser_0000
	IMPORT_START	"ThreadManForUser",0x40010000
#endif
#ifdef F_ThreadManForUser_0001
	IMPORT_FUNC	"ThreadManForUser",0x6E9EA350,_sceKernelReturnFromCallback
#endif
#ifdef F_ThreadManForUser_0002
	IMPORT_FUNC	"ThreadManForUser",0x0C106E53,sceKernelRegisterThreadEventHandler
#endif
#ifdef F_ThreadManForUser_0003
	IMPORT_FUNC	"ThreadManForUser",0x72F3C145,sceKernelReleaseThreadEventHandler
#endif
#ifdef F_ThreadManForUser_0004
	IMPORT_FUNC	"ThreadManForUser",0x369EEB6B,sceKernelReferThreadEventHandlerStatus
#endif
#ifdef F_ThreadManForUser_0005
	IMPORT_FUNC	"ThreadManForUser",0xE81CAF8F,sceKernelCreateCallback
#endif
#ifdef F_ThreadManForUser_0006
	IMPORT_FUNC	"ThreadManForUser",0xEDBA5844,sceKernelDeleteCallback
#endif
#ifdef F_ThreadManForUser_0007
	IMPORT_FUNC	"ThreadManForUser",0xC11BA8C4,sceKernelNotifyCallback
#endif
#ifdef F_ThreadManForUser_0008
	IMPORT_FUNC	"ThreadManForUser",0xBA4051D6,sceKernelCancelCallback
#endif
#ifdef F_ThreadManForUser_0009
	IMPORT_FUNC	"ThreadManForUser",0x2A3D44FF,sceKernelGetCallbackCount
#endif
#ifdef F_ThreadManForUser_0010
	IMPORT_FUNC	"ThreadManForUser",0x349D6D6C,sceKernelCheckCallback
#endif
#ifdef F_ThreadManForUser_0011
	IMPORT_FUNC	"ThreadManForUser",0x730ED8BC,sceKernelReferCallbackStatus
#endif
#ifdef F_ThreadManForUser_0012
	IMPORT_FUNC	"ThreadManForUser",0x9ACE131E,sceKernelSleepThread
#endif
#ifdef F_ThreadManForUser_0013
	IMPORT_FUNC	"ThreadManForUser",0x82826F70,sceKernelSleepThreadCB
#endif
#ifdef F_ThreadManForUser_0014
	IMPORT_FUNC	"ThreadManForUser",0xD59EAD2F,sceKernelWakeupThread
#endif
#ifdef F_ThreadManForUser_0015
	IMPORT_FUNC	"ThreadManForUser",0xFCCFAD26,sceKernelCancelWakeupThread
#endif
#ifdef F_ThreadManForUser_0016
	IMPORT_FUNC	"ThreadManForUser",0x9944F31F,sceKernelSuspendThread
#endif
#ifdef F_ThreadManForUser_0017
	IMPORT_FUNC	"ThreadManForUser",0x75156E8F,sceKernelResumeThread
#endif
#ifdef F_ThreadManForUser_0018
	IMPORT_FUNC	"ThreadManForUser",0x278C0DF5,sceKernelWaitThreadEnd
#endif
#ifdef F_ThreadManForUser_0019
	IMPORT_FUNC	"ThreadManForUser",0x840E8133,sceKernelWaitThreadEndCB
#endif
#ifdef F_ThreadManForUser_0020
	IMPORT_FUNC	"ThreadManForUser",0xCEADEB47,sceKernelDelayThread
#endif
#ifdef F_ThreadManForUser_0021
	IMPORT_FUNC	"ThreadManForUser",0x68DA9E36,sceKernelDelayThreadCB
#endif
#ifdef F_ThreadManForUser_0022
	IMPORT_FUNC	"ThreadManForUser",0xBD123D9E,sceKernelDelaySysClockThread
#endif
#ifdef F_ThreadManForUser_0023
	IMPORT_FUNC	"ThreadManForUser",0x1181E963,sceKernelDelaySysClockThreadCB
#endif
#ifdef F_ThreadManForUser_0024
	IMPORT_FUNC	"ThreadManForUser",0xD6DA4BA1,sceKernelCreateSema
#endif
#ifdef F_ThreadManForUser_0025
	IMPORT_FUNC	"ThreadManForUser",0x28B6489C,sceKernelDeleteSema
#endif
#ifdef F_ThreadManForUser_0026
	IMPORT_FUNC	"ThreadManForUser",0x3F53E640,sceKernelSignalSema
#endif
#ifdef F_ThreadManForUser_0027
	IMPORT_FUNC	"ThreadManForUser",0x4E3A1105,sceKernelWaitSema
#endif
#ifdef F_ThreadManForUser_0028
	IMPORT_FUNC	"ThreadManForUser",0x6D212BAC,sceKernelWaitSemaCB
#endif
#ifdef F_ThreadManForUser_0029
	IMPORT_FUNC	"ThreadManForUser",0x58B1F937,sceKernelPollSema
#endif
#ifdef F_ThreadManForUser_0030
	IMPORT_FUNC	"ThreadManForUser",0x8FFDF9A2,sceKernelCancelSema
#endif
#ifdef F_ThreadManForUser_0031
	IMPORT_FUNC	"ThreadManForUser",0xBC6FEBC5,sceKernelReferSemaStatus
#endif
#ifdef F_ThreadManForUser_0032
	IMPORT_FUNC	"ThreadManForUser",0x55C20A00,sceKernelCreateEventFlag
#endif
#ifdef F_ThreadManForUser_0033
	IMPORT_FUNC	"ThreadManForUser",0xEF9E4C70,sceKernelDeleteEventFlag
#endif
#ifdef F_ThreadManForUser_0034
	IMPORT_FUNC	"ThreadManForUser",0x1FB15A32,sceKernelSetEventFlag
#endif
#ifdef F_ThreadManForUser_0035
	IMPORT_FUNC	"ThreadManForUser",0x812346E4,sceKernelClearEventFlag
#endif
#ifdef F_ThreadManForUser_0036
	IMPORT_FUNC	"ThreadManForUser",0x402FCF22,sceKernelWaitEventFlag
#endif
#ifdef F_ThreadManForUser_0037
	IMPORT_FUNC	"ThreadManForUser",0x328C546A,sceKernelWaitEventFlagCB
#endif
#ifdef F_ThreadManForUser_0038
	IMPORT_FUNC	"ThreadManForUser",0x30FD48F0,sceKernelPollEventFlag
#endif
#ifdef F_ThreadManForUser_0039
	IMPORT_FUNC	"ThreadManForUser",0xCD203292,sceKernelCancelEventFlag
#endif
#ifdef F_ThreadManForUser_0040
	IMPORT_FUNC	"ThreadManForUser",0xA66B0120,sceKernelReferEventFlagStatus
#endif
#ifdef F_ThreadManForUser_0041
	IMPORT_FUNC	"ThreadManForUser",0x8125221D,sceKernelCreateMbx
#endif
#ifdef F_ThreadManForUser_0042
	IMPORT_FUNC	"ThreadManForUser",0x86255ADA,sceKernelDeleteMbx
#endif
#ifdef F_ThreadManForUser_0043
	IMPORT_FUNC	"ThreadManForUser",0xE9B3061E,sceKernelSendMbx
#endif
#ifdef F_ThreadManForUser_0044
	IMPORT_FUNC	"ThreadManForUser",0x18260574,sceKernelReceiveMbx
#endif
#ifdef F_ThreadManForUser_0045
	IMPORT_FUNC	"ThreadManForUser",0xF3986382,sceKernelReceiveMbxCB
#endif
#ifdef F_ThreadManForUser_0046
	IMPORT_FUNC	"ThreadManForUser",0x0D81716A,sceKernelPollMbx
#endif
#ifdef F_ThreadManForUser_0047
	IMPORT_FUNC	"ThreadManForUser",0x87D4DD36,sceKernelCancelReceiveMbx
#endif
#ifdef F_ThreadManForUser_0048
	IMPORT_FUNC	"ThreadManForUser",0xA8E8C846,sceKernelReferMbxStatus
#endif
#ifdef F_ThreadManForUser_0049
	IMPORT_FUNC	"ThreadManForUser",0x7C0DC2A0,sceKernelCreateMsgPipe
#endif
#ifdef F_ThreadManForUser_0050
	IMPORT_FUNC	"ThreadManForUser",0xF0B7DA1C,sceKernelDeleteMsgPipe
#endif
#ifdef F_ThreadManForUser_0051
	IMPORT_FUNC	"ThreadManForUser",0x876DBFAD,sceKernelSendMsgPipe
#endif
#ifdef F_ThreadManForUser_0052
	IMPORT_FUNC	"ThreadManForUser",0x7C41F2C2,sceKernelSendMsgPipeCB
#endif
#ifdef F_ThreadManForUser_0053
	IMPORT_FUNC	"ThreadManForUser",0x884C9F90,sceKernelTrySendMsgPipe
#endif
#ifdef F_ThreadManForUser_0054
	IMPORT_FUNC	"ThreadManForUser",0x74829B76,sceKernelReceiveMsgPipe
#endif
#ifdef F_ThreadManForUser_0055
	IMPORT_FUNC	"ThreadManForUser",0xFBFA697D,sceKernelReceiveMsgPipeCB
#endif
#ifdef F_ThreadManForUser_0056
	IMPORT_FUNC	"ThreadManForUser",0xDF52098F,sceKernelTryReceiveMsgPipe
#endif
#ifdef F_ThreadManForUser_0057
	IMPORT_FUNC	"ThreadManForUser",0x349B864D,sceKernelCancelMsgPipe
#endif
#ifdef F_ThreadManForUser_0058
	IMPORT_FUNC	"ThreadManForUser",0x33BE4024,sceKernelReferMsgPipeStatus
#endif
#ifdef F_ThreadManForUser_0059
	IMPORT_FUNC	"ThreadManForUser",0x56C039B5,sceKernelCreateVpl
#endif
#ifdef F_ThreadManForUser_0060
	IMPORT_FUNC	"ThreadManForUser",0x89B3D48C,sceKernelDeleteVpl
#endif
#ifdef F_ThreadManForUser_0061
	IMPORT_FUNC	"ThreadManForUser",0xBED27435,sceKernelAllocateVpl
#endif
#ifdef F_ThreadManForUser_0062
	IMPORT_FUNC	"ThreadManForUser",0xEC0A693F,sceKernelAllocateVplCB
#endif
#ifdef F_ThreadManForUser_0063
	IMPORT_FUNC	"ThreadManForUser",0xAF36D708,sceKernelTryAllocateVpl
#endif
#ifdef F_ThreadManForUser_0064
	IMPORT_FUNC	"ThreadManForUser",0xB736E9FF,sceKernelFreeVpl
#endif
#ifdef F_ThreadManForUser_0065
	IMPORT_FUNC	"ThreadManForUser",0x1D371B8A,sceKernelCancelVpl
#endif
#ifdef F_ThreadManForUser_0066
	IMPORT_FUNC	"ThreadManForUser",0x39810265,sceKernelReferVplStatus
#endif
#ifdef F_ThreadManForUser_0067
	IMPORT_FUNC	"ThreadManForUser",0xC07BB470,sceKernelCreateFpl
#endif
#ifdef F_ThreadManForUser_0068
	IMPORT_FUNC	"ThreadManForUser",0xED1410E0,sceKernelDeleteFpl
#endif
#ifdef F_ThreadManForUser_0069
	IMPORT_FUNC	"ThreadManForUser",0xD979E9BF,sceKernelAllocateFpl
#endif
#ifdef F_ThreadManForUser_0070
	IMPORT_FUNC	"ThreadManForUser",0xE7282CB6,sceKernelAllocateFplCB
#endif
#ifdef F_ThreadManForUser_0071
	IMPORT_FUNC	"ThreadManForUser",0x623AE665,sceKernelTryAllocateFpl
#endif
#ifdef F_ThreadManForUser_0072
	IMPORT_FUNC	"ThreadManForUser",0xF6414A71,sceKernelFreeFpl
#endif
#ifdef F_ThreadManForUser_0073
	IMPORT_FUNC	"ThreadManForUser",0xA8AA591F,sceKernelCancelFpl
#endif
#ifdef F_ThreadManForUser_0074
	IMPORT_FUNC	"ThreadManForUser",0xD8199E4C,sceKernelReferFplStatus
#endif
#ifdef F_ThreadManForUser_0075
	IMPORT_FUNC	"ThreadManForUser",0x0E927AED,_sceKernelReturnFromTimerHandler
#endif
#ifdef F_ThreadManForUser_0076
	IMPORT_FUNC	"ThreadManForUser",0x110DEC9A,sceKernelUSec2SysClock
#endif
#ifdef F_ThreadManForUser_0077
	IMPORT_FUNC	"ThreadManForUser",0xC8CD158C,sceKernelUSec2SysClockWide
#endif
#ifdef F_ThreadManForUser_0078
	IMPORT_FUNC	"ThreadManForUser",0xBA6B92E2,sceKernelSysClock2USec
#endif
#ifdef F_ThreadManForUser_0079
	IMPORT_FUNC	"ThreadManForUser",0xE1619D7C,sceKernelSysClock2USecWide
#endif
#ifdef F_ThreadManForUser_0080
	IMPORT_FUNC	"ThreadManForUser",0xDB738F35,sceKernelGetSystemTime
#endif
#ifdef F_ThreadManForUser_0081
	IMPORT_FUNC	"ThreadManForUser",0x82BC5777,sceKernelGetSystemTimeWide
#endif
#ifdef F_ThreadManForUser_0082
	IMPORT_FUNC	"ThreadManForUser",0x369ED59D,sceKernelGetSystemTimeLow
#endif
#ifdef F_ThreadManForUser_0083
	IMPORT_FUNC	"ThreadManForUser",0x6652B8CA,sceKernelSetAlarm
#endif
#ifdef F_ThreadManForUser_0084
	IMPORT_FUNC	"ThreadManForUser",0xB2C25152,sceKernelSetSysClockAlarm
#endif
#ifdef F_ThreadManForUser_0085
	IMPORT_FUNC	"ThreadManForUser",0x7E65B999,sceKernelCancelAlarm
#endif
#ifdef F_ThreadManForUser_0086
	IMPORT_FUNC	"ThreadManForUser",0xDAA3F564,sceKernelReferAlarmStatus
#endif
#ifdef F_ThreadManForUser_0087
	IMPORT_FUNC	"ThreadManForUser",0x20FFF560,sceKernelCreateVTimer
#endif
#ifdef F_ThreadManForUser_0088
	IMPORT_FUNC	"ThreadManForUser",0x328F9E52,sceKernelDeleteVTimer
#endif
#ifdef F_ThreadManForUser_0089
	IMPORT_FUNC	"ThreadManForUser",0xB3A59970,sceKernelGetVTimerBase
#endif
#ifdef F_ThreadManForUser_0090
	IMPORT_FUNC	"ThreadManForUser",0xB7C18B77,sceKernelGetVTimerBaseWide
#endif
#ifdef F_ThreadManForUser_0091
	IMPORT_FUNC	"ThreadManForUser",0x034A921F,sceKernelGetVTimerTime
#endif
#ifdef F_ThreadManForUser_0092
	IMPORT_FUNC	"ThreadManForUser",0xC0B3FFD2,sceKernelGetVTimerTimeWide
#endif
#ifdef F_ThreadManForUser_0093
	IMPORT_FUNC	"ThreadManForUser",0x542AD630,sceKernelSetVTimerTime
#endif
#ifdef F_ThreadManForUser_0094
	IMPORT_FUNC	"ThreadManForUser",0xFB6425C3,sceKernelSetVTimerTimeWide
#endif
#ifdef F_ThreadManForUser_0095
	IMPORT_FUNC	"ThreadManForUser",0xC68D9437,sceKernelStartVTimer
#endif
#ifdef F_ThreadManForUser_0096
	IMPORT_FUNC	"ThreadManForUser",0xD0AEEE87,sceKernelStopVTimer
#endif
#ifdef F_ThreadManForUser_0097
	IMPORT_FUNC	"ThreadManForUser",0xD8B299AE,sceKernelSetVTimerHandler
#endif
#ifdef F_ThreadManForUser_0098
	IMPORT_FUNC	"ThreadManForUser",0x53B00E9A,sceKernelSetVTimerHandlerWide
#endif
#ifdef F_ThreadManForUser_0099
	IMPORT_FUNC	"ThreadManForUser",0xD2D615EF,sceKernelCancelVTimerHandler
#endif
#ifdef F_ThreadManForUser_0100
	IMPORT_FUNC	"ThreadManForUser",0x5F32BEAA,sceKernelReferVTimerStatus
#endif
#ifdef F_ThreadManForUser_0101
	IMPORT_FUNC	"ThreadManForUser",0x446D8DE6,sceKernelCreateThread
#endif
#ifdef F_ThreadManForUser_0102
	IMPORT_FUNC	"ThreadManForUser",0x9FA03CD3,sceKernelDeleteThread
#endif
#ifdef F_ThreadManForUser_0103
	IMPORT_FUNC	"ThreadManForUser",0xF475845D,sceKernelStartThread
#endif
#ifdef F_ThreadManForUser_0104
	IMPORT_FUNC	"ThreadManForUser",0x532A522E,_sceKernelExitThread
#endif
#ifdef F_ThreadManForUser_0105
	IMPORT_FUNC	"ThreadManForUser",0xAA73C935,sceKernelExitThread
#endif
#ifdef F_ThreadManForUser_0106
	IMPORT_FUNC	"ThreadManForUser",0x809CE29B,sceKernelExitDeleteThread
#endif
#ifdef F_ThreadManForUser_0107
	IMPORT_FUNC	"ThreadManForUser",0x616403BA,sceKernelTerminateThread
#endif
#ifdef F_ThreadManForUser_0108
	IMPORT_FUNC	"ThreadManForUser",0x383F7BCC,sceKernelTerminateDeleteThread
#endif
#ifdef F_ThreadManForUser_0109
	IMPORT_FUNC	"ThreadManForUser",0x3AD58B8C,sceKernelSuspendDispatchThread
#endif
#ifdef F_ThreadManForUser_0110
	IMPORT_FUNC	"ThreadManForUser",0x27E22EC2,sceKernelResumeDispatchThread
#endif
#ifdef F_ThreadManForUser_0111
	IMPORT_FUNC	"ThreadManForUser",0xEA748E31,sceKernelChangeCurrentThreadAttr
#endif
#ifdef F_ThreadManForUser_0112
	IMPORT_FUNC	"ThreadManForUser",0x71BC9871,sceKernelChangeThreadPriority
#endif
#ifdef F_ThreadManForUser_0113
	IMPORT_FUNC	"ThreadManForUser",0x912354A7,sceKernelRotateThreadReadyQueue
#endif
#ifdef F_ThreadManForUser_0114
	IMPORT_FUNC	"ThreadManForUser",0x2C34E053,sceKernelReleaseWaitThread
#endif
#ifdef F_ThreadManForUser_0115
	IMPORT_FUNC	"ThreadManForUser",0x293B45B8,sceKernelGetThreadId
#endif
#ifdef F_ThreadManForUser_0116
	IMPORT_FUNC	"ThreadManForUser",0x94AA61EE,sceKernelGetThreadCurrentPriority
#endif
#ifdef F_ThreadManForUser_0117
	IMPORT_FUNC	"ThreadManForUser",0x3B183E26,sceKernelGetThreadExitStatus
#endif
#ifdef F_ThreadManForUser_0118
	IMPORT_FUNC	"ThreadManForUser",0xD13BDE95,sceKernelCheckThreadStack
#endif
#ifdef F_ThreadManForUser_0119
	IMPORT_FUNC	"ThreadManForUser",0x52089CA1,sceKernelGetThreadStackFreeSize
#endif
#ifdef F_ThreadManForUser_0120
	IMPORT_FUNC	"ThreadManForUser",0x17C1684E,sceKernelReferThreadStatus
#endif
#ifdef F_ThreadManForUser_0121
	IMPORT_FUNC	"ThreadManForUser",0xFFC36A14,sceKernelReferThreadRunStatus
#endif
#ifdef F_ThreadManForUser_0122
	IMPORT_FUNC	"ThreadManForUser",0x627E6F3A,sceKernelReferSystemStatus
#endif
#ifdef F_ThreadManForUser_0123
	IMPORT_FUNC	"ThreadManForUser",0x94416130,sceKernelGetThreadmanIdList
#endif
#ifdef F_ThreadManForUser_0124
	IMPORT_FUNC	"ThreadManForUser",0x57CF62DD,sceKernelGetThreadmanIdType
#endif
#ifdef F_ThreadManForUser_0125
	IMPORT_FUNC	"ThreadManForUser",0x64D4540E,sceKernelReferThreadProfiler
#endif
#ifdef F_ThreadManForUser_0126
	IMPORT_FUNC	"ThreadManForUser",0x8218B4DD,sceKernelReferGlobalProfiler
#endif
