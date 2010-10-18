	.set noreorder

#include "pspimport.s"

// Build List
// sceHttp_0000.o sceHttp_0001.o sceHttp_0002.o sceHttp_0003.o sceHttp_0004.o sceHttp_0005.o sceHttp_0006.o sceHttp_0007.o sceHttp_0008.o sceHttp_0009.o sceHttp_0010.o sceHttp_0011.o sceHttp_0012.o sceHttp_0013.o sceHttp_0014.o sceHttp_0015.o sceHttp_0016.o sceHttp_0017.o sceHttp_0018.o sceHttp_0019.o sceHttp_0020.o sceHttp_0021.o sceHttp_0022.o sceHttp_0023.o sceHttp_0024.o sceHttp_0025.o sceHttp_0026.o sceHttp_0027.o sceHttp_0028.o sceHttp_0029.o sceHttp_0030.o sceHttp_0031.o sceHttp_0032.o sceHttp_0033.o sceHttp_0034.o sceHttp_0035.o sceHttp_0036.o sceHttp_0037.o sceHttp_0038.o sceHttp_0039.o sceHttp_0040.o sceHttp_0041.o sceHttp_0042.o sceHttp_0043.o sceHttp_0044.o sceHttp_0045.o sceHttp_0046.o sceHttp_0047.o sceHttp_0048.o sceHttp_0049.o sceHttp_0050.o sceHttp_0051.o sceHttp_0052.o sceHttp_0053.o sceHttp_0054.o sceHttp_0055.o sceHttp_0056.o sceHttp_0057.o sceHttp_0058.o sceHttp_0059.o sceHttp_0060.o sceHttp_0061.o sceHttp_0062.o sceHttp_0063.o sceHttp_0064.o sceHttp_0065.o sceHttp_0066.o sceHttp_0067.o sceHttp_0068.o sceHttp_0069.o sceHttp_0070.o sceHttp_0071.o sceHttp_0072.o sceHttp_0073.o sceHttp_0074.o sceHttp_0075.o sceHttp_0076.o sceHttp_0077.o sceHttp_0078.o sceHttp_0079.o sceHttp_0080.o sceHttp_0081.o sceHttp_0082.o sceHttp_0083.o

#ifdef F_sceHttp_0000
	IMPORT_START	"sceHttp",0x00090011
#endif
#ifdef F_sceHttp_0001
	IMPORT_FUNC	"sceHttp",0x0282A3BD,sceHttpGetContentLength
#endif
#ifdef F_sceHttp_0002
	IMPORT_FUNC	"sceHttp",0x03D9526F,sceHttpSetResolveRetry
#endif
#ifdef F_sceHttp_0003
	IMPORT_FUNC	"sceHttp",0x06488A1C,sceHttpSetCookieSendCallback
#endif
#ifdef F_sceHttp_0004
	IMPORT_FUNC	"sceHttp",0x0809C831,sceHttpEnableRedirect
#endif
#ifdef F_sceHttp_0005
	IMPORT_FUNC	"sceHttp",0x0B12ABFB,sceHttpDisableCookie
#endif
#ifdef F_sceHttp_0006
	IMPORT_FUNC	"sceHttp",0x0DAFA58F,sceHttpEnableCookie
#endif
#ifdef F_sceHttp_0007
	IMPORT_FUNC	"sceHttp",0x15540184,sceHttpDeleteHeader
#endif
#ifdef F_sceHttp_0008
	IMPORT_FUNC	"sceHttp",0x1A0EBB69,sceHttpDisableRedirect
#endif
#ifdef F_sceHttp_0009
	IMPORT_FUNC	"sceHttp",0x1CEDB9D4,sceHttpFlushCache
#endif
#ifdef F_sceHttp_0010
	IMPORT_FUNC	"sceHttp",0x1F0FC3E3,sceHttpSetRecvTimeOut
#endif
#ifdef F_sceHttp_0011
	IMPORT_FUNC	"sceHttp",0x2255551E,sceHttpGetNetworkPspError
#endif
#ifdef F_sceHttp_0012
	IMPORT_FUNC	"sceHttp",0x267618F4,sceHttpSetAuthInfoCallback
#endif
#ifdef F_sceHttp_0013
	IMPORT_FUNC	"sceHttp",0x2A6C3296,sceHttpSetAuthInfoCB
#endif
#ifdef F_sceHttp_0014
	IMPORT_FUNC	"sceHttp",0x2C3C82CF,sceHttpFlushAuthList
#endif
#ifdef F_sceHttp_0015
	IMPORT_FUNC	"sceHttp",0x3A67F306,sceHttpSetCookieRecvCallback
#endif
#ifdef F_sceHttp_0016
	IMPORT_FUNC	"sceHttp",0x3C478044,sceHttp_3C478044
#endif
#ifdef F_sceHttp_0017
	IMPORT_FUNC	"sceHttp",0x3EABA285,sceHttpAddExtraHeader
#endif
#ifdef F_sceHttp_0018
	IMPORT_FUNC	"sceHttp",0x457D221D,sceHttp_457D221D
#endif
#ifdef F_sceHttp_0019
	IMPORT_FUNC	"sceHttp",0x47347B50,sceHttpCreateRequest
#endif
#ifdef F_sceHttp_0020
	IMPORT_FUNC	"sceHttp",0x47940436,sceHttpSetResolveTimeOut
#endif
#ifdef F_sceHttp_0021
	IMPORT_FUNC	"sceHttp",0x4CC7D78F,sceHttpGetStatusCode
#endif
#ifdef F_sceHttp_0022
	IMPORT_FUNC	"sceHttp",0x4E4A284A,sceHttp_4E4A284A
#endif
#ifdef F_sceHttp_0023
	IMPORT_FUNC	"sceHttp",0x5152773B,sceHttpDeleteConnection
#endif
#ifdef F_sceHttp_0024
	IMPORT_FUNC	"sceHttp",0x54E7DF75,sceHttpIsRequestInCache
#endif
#ifdef F_sceHttp_0025
	IMPORT_FUNC	"sceHttp",0x569A1481,sceHttpsSetSslCallback
#endif
#ifdef F_sceHttp_0026
	IMPORT_FUNC	"sceHttp",0x59E6D16F,sceHttpEnableCache
#endif
#ifdef F_sceHttp_0027
	IMPORT_FUNC	"sceHttp",0x68AB0F86,sceHttpsInitWithPath
#endif
#ifdef F_sceHttp_0028
	IMPORT_FUNC	"sceHttp",0x739C2D79,sceHttp_739C2D79
#endif
#ifdef F_sceHttp_0029
	IMPORT_FUNC	"sceHttp",0x76D1363B,sceHttpSaveSystemCookie
#endif
#ifdef F_sceHttp_0030
	IMPORT_FUNC	"sceHttp",0x7774BF4C,sceHttpAddCookie
#endif
#ifdef F_sceHttp_0031
	IMPORT_FUNC	"sceHttp",0x77EE5319,sceHttp_77EE5319
#endif
#ifdef F_sceHttp_0032
	IMPORT_FUNC	"sceHttp",0x78A0D3EC,sceHttpEnableKeepAlive
#endif
#ifdef F_sceHttp_0033
	IMPORT_FUNC	"sceHttp",0x78B54C09,sceHttpEndCache
#endif
#ifdef F_sceHttp_0034
	IMPORT_FUNC	"sceHttp",0x8046E250,sceHttp_8046E250
#endif
#ifdef F_sceHttp_0035
	IMPORT_FUNC	"sceHttp",0x87797BDD,sceHttpsLoadDefaultCert
#endif
#ifdef F_sceHttp_0036
	IMPORT_FUNC	"sceHttp",0x87F1E666,sceHttp_87F1E666
#endif
#ifdef F_sceHttp_0037
	IMPORT_FUNC	"sceHttp",0x8ACD1F73,sceHttpSetConnectTimeOut
#endif
#ifdef F_sceHttp_0038
	IMPORT_FUNC	"sceHttp",0x8EEFD953,sceHttpCreateConnection
#endif
#ifdef F_sceHttp_0039
	IMPORT_FUNC	"sceHttp",0x951D310E,sceHttp_951D310E
#endif
#ifdef F_sceHttp_0040
	IMPORT_FUNC	"sceHttp",0x9668864C,sceHttpSetRecvBlockSize
#endif
#ifdef F_sceHttp_0041
	IMPORT_FUNC	"sceHttp",0x96F16D3E,sceHttpGetCookie
#endif
#ifdef F_sceHttp_0042
	IMPORT_FUNC	"sceHttp",0x9988172D,sceHttpSetSendTimeOut
#endif
#ifdef F_sceHttp_0043
	IMPORT_FUNC	"sceHttp",0x9AFC98B2,sceHttpSendRequestInCacheFirstMode
#endif
#ifdef F_sceHttp_0044
	IMPORT_FUNC	"sceHttp",0x9B1F1F36,sceHttpCreateTemplate
#endif
#ifdef F_sceHttp_0045
	IMPORT_FUNC	"sceHttp",0x9FC5F10D,sceHttpEnableAuth
#endif
#ifdef F_sceHttp_0046
	IMPORT_FUNC	"sceHttp",0xA4496DE5,sceHttpSetRedirectCallback
#endif
#ifdef F_sceHttp_0047
	IMPORT_FUNC	"sceHttp",0xA461A167,sceHttp_A461A167
#endif
#ifdef F_sceHttp_0048
	IMPORT_FUNC	"sceHttp",0xA5512E01,sceHttpDeleteRequest
#endif
#ifdef F_sceHttp_0049
	IMPORT_FUNC	"sceHttp",0xA6800C34,sceHttpInitCache
#endif
#ifdef F_sceHttp_0050
	IMPORT_FUNC	"sceHttp",0xA909F2AE,sceHttp_A909F2AE
#endif
#ifdef F_sceHttp_0051
	IMPORT_FUNC	"sceHttp",0xAB1540D5,sceHttpsGetSslError
#endif
#ifdef F_sceHttp_0052
	IMPORT_FUNC	"sceHttp",0xAB1ABE07,sceHttpInit
#endif
#ifdef F_sceHttp_0053
	IMPORT_FUNC	"sceHttp",0xAE948FEE,sceHttpDisableAuth
#endif
#ifdef F_sceHttp_0054
	IMPORT_FUNC	"sceHttp",0xB0257723,sceHttp_B0257723
#endif
#ifdef F_sceHttp_0055
	IMPORT_FUNC	"sceHttp",0xB0C34B1D,sceHttpSetCacheContentLengthMaxSize
#endif
#ifdef F_sceHttp_0056
	IMPORT_FUNC	"sceHttp",0xB3FAF831,sceHttpsDisableOption
#endif
#ifdef F_sceHttp_0057
	IMPORT_FUNC	"sceHttp",0xB509B09E,sceHttpCreateRequestWithURL
#endif
#ifdef F_sceHttp_0058
	IMPORT_FUNC	"sceHttp",0xBAC31BF1,sceHttpsEnableOption
#endif
#ifdef F_sceHttp_0059
	IMPORT_FUNC	"sceHttp",0xBB70706F,sceHttpSendRequest
#endif
#ifdef F_sceHttp_0060
	IMPORT_FUNC	"sceHttp",0xC0E69162,sceHttp_C0E69162
#endif
#ifdef F_sceHttp_0061
	IMPORT_FUNC	"sceHttp",0xC10B6BD9,sceHttpAbortRequest
#endif
#ifdef F_sceHttp_0062
	IMPORT_FUNC	"sceHttp",0xC6330B0D,sceHttp_C6330B0D
#endif
#ifdef F_sceHttp_0063
	IMPORT_FUNC	"sceHttp",0xC7EF2559,sceHttpDisableKeepAlive
#endif
#ifdef F_sceHttp_0064
	IMPORT_FUNC	"sceHttp",0xC98CBBA7,sceHttpSetResHeaderMaxSize
#endif
#ifdef F_sceHttp_0065
	IMPORT_FUNC	"sceHttp",0xCC920C12,sceHttp_CC920C12
#endif
#ifdef F_sceHttp_0066
	IMPORT_FUNC	"sceHttp",0xCCBD167A,sceHttpDisableCache
#endif
#ifdef F_sceHttp_0067
	IMPORT_FUNC	"sceHttp",0xCDB0DC58,sceHttp_CDB0DC58
#endif
#ifdef F_sceHttp_0068
	IMPORT_FUNC	"sceHttp",0xCDF8ECB9,sceHttpCreateConnectionWithURL
#endif
#ifdef F_sceHttp_0069
	IMPORT_FUNC	"sceHttp",0xD081EC8F,sceHttpGetNetworkErrno
#endif
#ifdef F_sceHttp_0070
	IMPORT_FUNC	"sceHttp",0xD11DAB01,sceHttpsGetCaList
#endif
#ifdef F_sceHttp_0071
	IMPORT_FUNC	"sceHttp",0xD1C8945E,sceHttpEnd
#endif
#ifdef F_sceHttp_0072
	IMPORT_FUNC	"sceHttp",0xD29163DA,sceHttp_D29163DA
#endif
#ifdef F_sceHttp_0073
	IMPORT_FUNC	"sceHttp",0xD70D4847,sceHttpGetProxy
#endif
#ifdef F_sceHttp_0074
	IMPORT_FUNC	"sceHttp",0xD80BE761,sceHttp_D80BE761
#endif
#ifdef F_sceHttp_0075
	IMPORT_FUNC	"sceHttp",0xDB266CCF,sceHttpGetAllHeader
#endif
#ifdef F_sceHttp_0076
	IMPORT_FUNC	"sceHttp",0xDD6E7857,sceHttp_DD6E7857
#endif
#ifdef F_sceHttp_0077
	IMPORT_FUNC	"sceHttp",0xE4D21302,sceHttpsInit
#endif
#ifdef F_sceHttp_0078
	IMPORT_FUNC	"sceHttp",0xEDEEB999,sceHttpReadData
#endif
#ifdef F_sceHttp_0079
	IMPORT_FUNC	"sceHttp",0xF0F46C62,sceHttpSetProxy
#endif
#ifdef F_sceHttp_0080
	IMPORT_FUNC	"sceHttp",0xF1657B22,sceHttpLoadSystemCookie
#endif
#ifdef F_sceHttp_0081
	IMPORT_FUNC	"sceHttp",0xF49934F6,sceHttpSetMallocFunction
#endif
#ifdef F_sceHttp_0082
	IMPORT_FUNC	"sceHttp",0xF9D8EB63,sceHttpsEnd
#endif
#ifdef F_sceHttp_0083
	IMPORT_FUNC	"sceHttp",0xFCF8C055,sceHttpDeleteTemplate
#endif
