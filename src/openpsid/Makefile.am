
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

OPENPSID_OBJS = sceOpenPSID_0000.o sceOpenPSID_0001.o

libpspopenspidincludedir = @PSPSDK_INCLUDEDIR@
libpspopenspidinclude_HEADERS = pspopenpsid.h

lib_LIBRARIES = libpspopenpsid.a 
libpspopenpsid_a_SOURCES = sceOpenPSID.S
libpspopenpsid_a_LIBADD  = $(OPENPSID_OBJS)

$(OPENPSID_OBJS): sceOpenPSID.S
	$(COMPILE) -DF_$* $< -c -o $@
