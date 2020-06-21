
pspsdkincludedir = @PSPSDK_INCLUDEDIR@

pspsdkinclude_HEADERS =		\
	as_reg_compat.h		\
	psptypes.h		\
	pspstub.s		\
	pspimport.s \
	clang_psp.h

## Install the build.mak fragment to $PSPSDK/lib.
buildmakdir = @PSPSDK_LIBDIR@
buildmak_DATA = build.mak prxspecs

buildmakprxdir = @PSPSDK_LIBDIR@
buildmakprx_DATA = build_prx.mak linkfile.prx clang.conf

EXTRA_DIST = build.mak prxspecs build_prx.mak linkfile.prx
