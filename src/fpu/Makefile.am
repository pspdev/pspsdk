
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/debug -I$(top_srcdir)/src/user
CFLAGS = @PSPSDK_CFLAGS@ -std=gnu99 -Wall -Wmissing-prototypes
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

libpspfpuincludedir = @PSPSDK_INCLUDEDIR@
libpspfpuinclude_HEADERS = pspfpu.h

lib_LIBRARIES = libpspfpu.a
libpspfpu_a_SOURCES = pspfpu.c
libpspfpu_a_LIBADD  = 
