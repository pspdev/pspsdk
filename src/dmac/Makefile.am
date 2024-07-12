
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

CPPFLAGS = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS)

DMAC_OBJS = sceDmac_0000.o sceDmac_0001.o sceDmac_0002.o

libpspdmacincludedir = @PSPSDK_INCLUDEDIR@
libpspdmacinclude_HEADERS = pspdmac.h

lib_LIBRARIES = libpspdmac.a
libpspdmac_a_SOURCES = sceDmac.S
libpspdmac_a_LIBADD = $(DMAC_OBJS)

$(DMAC_OBJS): sceDmac.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@
