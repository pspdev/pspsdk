
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base \
	   -I$(top_srcdir)/src/kernel \
	   -I$(top_srcdir)/src/user \
	   -I$(top_srcdir)/src/net \
	   -I$(top_srcdir)/src/utility \
	   -I$(top_srcdir)/src/debug
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

libpspsdkincludedir = @PSPSDK_INCLUDEDIR@
libpspsdkinclude_HEADERS = pspsdk.h

lib_LIBRARIES = libpspsdk.a

MODULEMGR_PATCHES_OBJS = \
	InstallNoDeviceCheckPatch.o \
	InstallNoPlainModuleCheckPatch.o \
	InstallKernelLoadModulePatch.o

INETHELPER_OBJS = pspSdkLoadInetModules.o pspSdkInetInit.o pspSdkInetTerm.o

MULT_SRCS = modulemgr_patches.c inethelper.c
MULT_OBJS = $(MODULEMGR_PATCHES_OBJS) $(INETHELPER_OBJS)

libpspsdk_a_SOURCES = query_mod.c loadmodule.c fixup.c threadutils.c interrupt.S k1set.S  fpu.S $(MULT_SRCS)
libpspsdk_a_LIBADD  = $(MULT_OBJS)

$(MODULEMGR_PATCHES_OBJS): modulemgr_patches.c
	$(COMPILE) -DF_$* $< -c -o $@

$(INETHELPER_OBJS): inethelper.c
	$(COMPILE) -DF_$* $< -c -o $@
