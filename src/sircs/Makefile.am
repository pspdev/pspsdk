
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

SIRCS_OBJS = sceSircs_0000.o sceSircs_0001.o 

libpspsircsincludedir = @PSPSDK_INCLUDEDIR@
libpspsircsinclude_HEADERS = pspsircs.h

lib_LIBRARIES = libpspsircs.a
libpspsircs_a_SOURCES = sceSircs.S
libpspsircs_a_LIBADD = $(SIRCS_OBJS)

$(SIRCS_OBJS): sceSircs.S
	$(COMPILE) -DF_$* $< -c -o $@
