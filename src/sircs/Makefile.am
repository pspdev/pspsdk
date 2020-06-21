
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

CPPFLAGS = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS)

SIRCS_OBJS = sceSircs_0000.o sceSircs_0001.o 

libpspsircsincludedir = @PSPSDK_INCLUDEDIR@
libpspsircsinclude_HEADERS = pspsircs.h

if SONYSTUBS
lib_LIBRARIES = libpspsircs.a
libpspsircs_a_SOURCES = sceSircs.S
libpspsircs_a_LIBADD = $(SIRCS_OBJS)

$(SIRCS_OBJS): sceSircs.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@
endif
