	.set noreorder

#include "pspstub.s"

	STUB_START "MyLib",0x00090000,0x00010005
	STUB_FUNC  0x563FF2B2,getModuleInfo
	STUB_END
