
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/debug -I$(top_srcdir)/src/user
CFLAGS = @PSPSDK_CFLAGS@ -std=gnu99 -Wall -Wmissing-prototypes
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

VFPU_OBJS = 

libpspvfpuincludedir = @PSPSDK_INCLUDEDIR@
libpspvfpuinclude_HEADERS = pspvfpu.h

lib_LIBRARIES = libpspvfpu.a
libpspvfpu_a_SOURCES = pspvfpu.c
libpspvfpu_a_LIBADD  = $(VFPU_OBJS)
