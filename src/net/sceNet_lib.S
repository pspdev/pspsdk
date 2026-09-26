	.set noreorder

#include "pspimport.s"

#ifdef F_sceNet_lib_0000
	IMPORT_START	"sceNet_lib",0x00090000
#endif
#ifdef F_sceNet_lib_0001
	IMPORT_FUNC	"sceNet_lib",0x3B617AA0,sceNetBpfOpen
#endif
#ifdef F_sceNet_lib_0002
	IMPORT_FUNC	"sceNet_lib",0xDB88F458,sceNetBpfClose
#endif
#ifdef F_sceNet_lib_0003
	IMPORT_FUNC	"sceNet_lib",0xB6FC0A5B,sceNetBpfRead
#endif
#ifdef F_sceNet_lib_0004
	IMPORT_FUNC	"sceNet_lib",0xC431A214,sceNetBpfWrite
#endif
#ifdef F_sceNet_lib_0005
	IMPORT_FUNC	"sceNet_lib",0xBFCFEFF6,sceNetBpfPoll
#endif
#ifdef F_sceNet_lib_0006
	IMPORT_FUNC	"sceNet_lib",0xE1F4696F,sceNetBpfIoctl
#endif
#ifdef F_sceNet_lib_0007
	IMPORT_FUNC	"sceNet_lib",0x5216CBF5,sceNetConfigUpInterface
#endif
#ifdef F_sceNet_lib_0008
	IMPORT_FUNC	"sceNet_lib",0xD2422E4D,sceNetConfigDownInterface
#endif
#ifdef F_sceNet_lib_0009
	IMPORT_FUNC	"sceNet_lib",0xD1BE2CE9,sceNetConfigGetIfEvent
#endif
#ifdef F_sceNet_lib_0010
	IMPORT_FUNC	"sceNet_lib",0xAB7DD9A5,sceNetConfigSetIfEventFlag
#endif
#ifdef F_sceNet_lib_0011
	IMPORT_FUNC	"sceNet_lib",0x80E1933E,sceNetConfigGetIfEventFlag
#endif
#ifdef F_sceNet_lib_0012
	IMPORT_FUNC	"sceNet_lib",0x7BA3ED91,sceNetConfig80211ScanRequest
#endif
#ifdef F_sceNet_lib_0013
	IMPORT_FUNC	"sceNet_lib",0x03164B12,sceNetConfig80211CreateRequest
#endif
#ifdef F_sceNet_lib_0014
	IMPORT_FUNC	"sceNet_lib",0x389728AB,sceNetConfig80211JoinRequest
#endif
#ifdef F_sceNet_lib_0015
	IMPORT_FUNC	"sceNet_lib",0x4BF9E1DE,sceNetConfig80211ScanJoinRequest
#endif
#ifdef F_sceNet_lib_0016
	IMPORT_FUNC	"sceNet_lib",0xD5B64E37,sceNetConfig80211ScanCreateRequest
#endif
#ifdef F_sceNet_lib_0017
	IMPORT_FUNC	"sceNet_lib",0xDA02F383,sceNetConfig80211LeaveRequest
#endif
#ifdef F_sceNet_lib_0018
	IMPORT_FUNC	"sceNet_lib",0xAFA11338,sceNetConfig80211SetConf
#endif
#ifdef F_sceNet_lib_0019
	IMPORT_FUNC	"sceNet_lib",0xB20F84F8,sceNetConfig80211GetConf
#endif
#ifdef F_sceNet_lib_0020
	IMPORT_FUNC	"sceNet_lib",0x83FE280A,sceNetConfig80211SetAuth
#endif
#ifdef F_sceNet_lib_0021
	IMPORT_FUNC	"sceNet_lib",0x4F8F3808,sceNetConfig80211GetAuth
#endif
#ifdef F_sceNet_lib_0022
	IMPORT_FUNC	"sceNet_lib",0x891723D5,sceNetConfig80211SetPowerSave
#endif
#ifdef F_sceNet_lib_0023
	IMPORT_FUNC	"sceNet_lib",0x0DFF67F9,sceNetConfig80211GetPowerSave
#endif
#ifdef F_sceNet_lib_0024
	IMPORT_FUNC	"sceNet_lib",0xF355C73B,sceNetConfig80211GetIfInfo
#endif
#ifdef F_sceNet_lib_0025
	IMPORT_FUNC	"sceNet_lib",0xA55C914F,sceNetConfig80211GetBssDesc
#endif
#ifdef F_sceNet_lib_0026
	IMPORT_FUNC	"sceNet_lib",0x0D633F53,sceNetConfig80211EnterGameMode
#endif
#ifdef F_sceNet_lib_0027
	IMPORT_FUNC	"sceNet_lib",0x8D33C11D,sceNetConfigGetEtherAddr
#endif
#ifdef F_sceNet_lib_0028
	IMPORT_FUNC	"sceNet_lib",0x522A971B,_sce_pspnet_if_exist
#endif
#ifdef F_sceNet_lib_0029
	IMPORT_FUNC	"sceNet_lib",0x1858883D,sceNetRand
#endif
#ifdef F_sceNet_lib_0030
	IMPORT_FUNC	"sceNet_lib",0x75D9985C,sceNetGetSystemClockSec
#endif
#ifdef F_sceNet_lib_0031
	IMPORT_FUNC	"sceNet_lib",0x25CC373A,_sce_pspnet_callout_init
#endif
#ifdef F_sceNet_lib_0032
	IMPORT_FUNC	"sceNet_lib",0xDCBC596E,_sce_pspnet_callout_cleanup
#endif
#ifdef F_sceNet_lib_0033
	IMPORT_FUNC	"sceNet_lib",0x7C86FBA4,_sce_pspnet_callout_reset
#endif
#ifdef F_sceNet_lib_0034
	IMPORT_FUNC	"sceNet_lib",0xA8B6205A,_sce_pspnet_callout_reset_usec
#endif
#ifdef F_sceNet_lib_0035
	IMPORT_FUNC	"sceNet_lib",0xA93A93E9,_sce_pspnet_callout_stop
#endif
#ifdef F_sceNet_lib_0036
	IMPORT_FUNC	"sceNet_lib",0x6B294EE4,_sce_pspnet_adhoc_sabort
#endif
#ifdef F_sceNet_lib_0037
	IMPORT_FUNC	"sceNet_lib",0x51C209B2,_sce_pspnet_inet_sabort
#endif
#ifdef F_sceNet_lib_0038
	IMPORT_FUNC	"sceNet_lib",0xC9C97945,_sce_pspnet_tabort
#endif
#ifdef F_sceNet_lib_0039
	IMPORT_FUNC	"sceNet_lib",0xB8C4A858,_sce_pspnet_tiwakeup
#endif
#ifdef F_sceNet_lib_0040
	IMPORT_FUNC	"sceNet_lib",0x205E8D17,_sce_pspnet_tsleep
#endif
#ifdef F_sceNet_lib_0041
	IMPORT_FUNC	"sceNet_lib",0xF6DB0A0B,_sce_pspnet_tsleep_usec
#endif
#ifdef F_sceNet_lib_0042
	IMPORT_FUNC	"sceNet_lib",0x7574FDA1,_sce_pspnet_wakeup
#endif
#ifdef F_sceNet_lib_0043
	IMPORT_FUNC	"sceNet_lib",0xCA3CF5EB,_sce_pspnet_thread_enter
#endif
#ifdef F_sceNet_lib_0044
	IMPORT_FUNC	"sceNet_lib",0x757085B0,_sce_pspnet_thread_leave
#endif
#ifdef F_sceNet_lib_0045
	IMPORT_FUNC	"sceNet_lib",0x435843CB,_sce_pspnet_get_thread_errno
#endif
#ifdef F_sceNet_lib_0046
	IMPORT_FUNC	"sceNet_lib",0xD861EF33,_sce_pspnet_set_thread_errno
#endif
#ifdef F_sceNet_lib_0047
	IMPORT_FUNC	"sceNet_lib",0xBB2B3DDB,_sce_pspnet_get_threadinfo
#endif
#ifdef F_sceNet_lib_0048
	IMPORT_FUNC	"sceNet_lib",0x6D5D42D7,_sce_pspnet_lock_threadinfo
#endif
#ifdef F_sceNet_lib_0049
	IMPORT_FUNC	"sceNet_lib",0xC21E18B2,_sce_pspnet_unlock_threadinfo
#endif
#ifdef F_sceNet_lib_0050
	IMPORT_FUNC	"sceNet_lib",0x45452B7B,_sce_pspnet_thread_busycount
#endif
#ifdef F_sceNet_lib_0051
	IMPORT_FUNC	"sceNet_lib",0x94B44F26,_sce_pspnet_spllock
#endif
#ifdef F_sceNet_lib_0052
	IMPORT_FUNC	"sceNet_lib",0x515B2F33,_sce_pspnet_splunlock
#endif
#ifdef F_sceNet_lib_0053
	IMPORT_FUNC	"sceNet_lib",0x6DC71518,sceNet_lib_6DC71518
#endif
#ifdef F_sceNet_lib_0054
	IMPORT_FUNC	"sceNet_lib",0x7C3B86C5,_sce_pspnet_schednetintr
#endif
#ifdef F_sceNet_lib_0055
	IMPORT_FUNC	"sceNet_lib",0x05D525E4,_sce_pspnet_schednetintr_with_evf
#endif
#ifdef F_sceNet_lib_0056
	IMPORT_FUNC	"sceNet_lib",0x1D10419C,_sce_pspnet_ifunit
#endif
#ifdef F_sceNet_lib_0057
	IMPORT_FUNC	"sceNet_lib",0xC2EC2EEA,_sce_pspnet_get_if_core_variables
#endif
#ifdef F_sceNet_lib_0058
	IMPORT_FUNC	"sceNet_lib",0x710BD467,_sce_pspnet_get_ifindex
#endif
#ifdef F_sceNet_lib_0059
	IMPORT_FUNC	"sceNet_lib",0x701DDDC3,_sce_pspnet_if_attach
#endif
#ifdef F_sceNet_lib_0060
	IMPORT_FUNC	"sceNet_lib",0xD5A03BC0,_sce_pspnet_if_detach
#endif
#ifdef F_sceNet_lib_0061
	IMPORT_FUNC	"sceNet_lib",0xFA6DE6A6,_sce_pspnet_if_up
#endif
#ifdef F_sceNet_lib_0062
	IMPORT_FUNC	"sceNet_lib",0xEDB11CB4,_sce_pspnet_if_down
#endif
#ifdef F_sceNet_lib_0063
	IMPORT_FUNC	"sceNet_lib",0x8C55B410,_sce_pspnet_if_nulloutput
#endif
#ifdef F_sceNet_lib_0064
	IMPORT_FUNC	"sceNet_lib",0x13A8B98A,_sce_pspnet_ifioctl
#endif
#ifdef F_sceNet_lib_0065
	IMPORT_FUNC	"sceNet_lib",0xEA42B353,_sce_pspnet_ifioctl_sync
#endif
#ifdef F_sceNet_lib_0066
	IMPORT_FUNC	"sceNet_lib",0x45945E8D,_sce_pspnet_ifplookup_index
#endif
#ifdef F_sceNet_lib_0067
	IMPORT_FUNC	"sceNet_lib",0xD60225A3,_sce_pspnet_ifplookup_lladdr
#endif
#ifdef F_sceNet_lib_0068
	IMPORT_FUNC	"sceNet_lib",0xEB6DE71A,_sce_pspnet_link_rtrequest
#endif
#ifdef F_sceNet_lib_0069
	IMPORT_FUNC	"sceNet_lib",0xEDCC871E,_sce_pspnet_ifafree
#endif
#ifdef F_sceNet_lib_0070
	IMPORT_FUNC	"sceNet_lib",0x4B2B3416,_sce_pspnet_microtime
#endif
#ifdef F_sceNet_lib_0071
	IMPORT_FUNC	"sceNet_lib",0x2B42872F,_sce_pspnet_uiomove
#endif
#ifdef F_sceNet_lib_0072
	IMPORT_FUNC	"sceNet_lib",0xC4261339,_sce_pspnet_hashinit
#endif
#ifdef F_sceNet_lib_0073
	IMPORT_FUNC	"sceNet_lib",0x41FD8B5C,_sce_pspnet_hashdone
#endif
#ifdef F_sceNet_lib_0074
	IMPORT_FUNC	"sceNet_lib",0x92633D8D,_sce_pspnet_selrecord
#endif
#ifdef F_sceNet_lib_0075
	IMPORT_FUNC	"sceNet_lib",0xB9C780C7,_sce_pspnet_selwakeup
#endif
#ifdef F_sceNet_lib_0076
	IMPORT_FUNC	"sceNet_lib",0xB68E1EEA,_sce_pspnet_get_selwait_addr
#endif
#ifdef F_sceNet_lib_0077
	IMPORT_FUNC	"sceNet_lib",0xE155112D,_sce_pspnet_start_of_inet_module_in_sched
#endif
#ifdef F_sceNet_lib_0078
	IMPORT_FUNC	"sceNet_lib",0x41621EB0,_sce_pspnet_stop_of_inet_module_in_sched
#endif
#ifdef F_sceNet_lib_0079
	IMPORT_FUNC	"sceNet_lib",0x2E005032,_sce_pspnet_start_of_adhoc_module_in_sched
#endif
#ifdef F_sceNet_lib_0080
	IMPORT_FUNC	"sceNet_lib",0x33B230BD,_sce_pspnet_stop_of_adhoc_module_in_sched
#endif
#ifdef F_sceNet_lib_0081
	IMPORT_FUNC	"sceNet_lib",0x976AB1E9,_sce_pspnet_start_of_inet_module_in_if_core
#endif
#ifdef F_sceNet_lib_0082
	IMPORT_FUNC	"sceNet_lib",0x4C8FD452,_sce_pspnet_stop_of_inet_module_in_if_core
#endif
#ifdef F_sceNet_lib_0083
	IMPORT_FUNC	"sceNet_lib",0x5ED457BE,_sce_pspnet_start_of_inet_module_in_if_ethersubr_core
#endif
#ifdef F_sceNet_lib_0084
	IMPORT_FUNC	"sceNet_lib",0x31F3CDA1,_sce_pspnet_stop_of_inet_module_in_if_ethersubr_core
#endif
#ifdef F_sceNet_lib_0085
	IMPORT_FUNC	"sceNet_lib",0x1F94AFD9,_sce_pspnet_start_of_adhoc_module_in_if_ethersubr_core
#endif
#ifdef F_sceNet_lib_0086
	IMPORT_FUNC	"sceNet_lib",0x0A5A8751,_sce_pspnet_stop_of_adhoc_module_in_if_ethersubr_core
#endif
#ifdef F_sceNet_lib_0087
	IMPORT_FUNC	"sceNet_lib",0xB3A48B7F,_sce_pspnet_start_of_adhoc_module_in_netintr
#endif
#ifdef F_sceNet_lib_0088
	IMPORT_FUNC	"sceNet_lib",0x949F1FBB,_sce_pspnet_stop_of_adhoc_module_in_netintr
#endif
#ifdef F_sceNet_lib_0089
	IMPORT_FUNC	"sceNet_lib",0x13672F83,_sce_pspnet_start_of_inet_module_in_netintr
#endif
#ifdef F_sceNet_lib_0090
	IMPORT_FUNC	"sceNet_lib",0x5C7C7381,_sce_pspnet_stop_of_inet_module_in_netintr
#endif
#ifdef F_sceNet_lib_0091
	IMPORT_FUNC	"sceNet_lib",0x86B6DCD9,_sce_pspnet_start_of_ipv6_module_in_netintr
#endif
#ifdef F_sceNet_lib_0092
	IMPORT_FUNC	"sceNet_lib",0x7AE91FB4,_sce_pspnet_stop_of_ipv6_module_in_netintr
#endif
#ifdef F_sceNet_lib_0093
	IMPORT_FUNC	"sceNet_lib",0x572AD6ED,_sce_pspnet_start_of_pppoe_module_in_netintr
#endif
#ifdef F_sceNet_lib_0094
	IMPORT_FUNC	"sceNet_lib",0x87DC7A7E,_sce_pspnet_stop_of_pppoe_module_in_netintr
#endif
#ifdef F_sceNet_lib_0095
	IMPORT_FUNC	"sceNet_lib",0x991FF86D,_sce_pspnet_start_of_inet_module_in_ifhandle_ether
#endif
#ifdef F_sceNet_lib_0096
	IMPORT_FUNC	"sceNet_lib",0x5505D820,_sce_pspnet_stop_of_inet_module_in_ifhandle_ether
#endif
