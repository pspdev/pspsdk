
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/debug -I$(top_srcdir)/src/user
CFLAGS = @PSPSDK_CFLAGS@ -std=gnu99 -Wall -Wmissing-prototypes
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

libpspprofincludedir = @PSPSDK_INCLUDEDIR@
libpspprofinclude_HEADERS = pspprof.h

lib_LIBRARIES = libpspprof.a
libpspprof_a_SOURCES = prof.c mcount.s
libpspprof_a_LIBADD  = 
