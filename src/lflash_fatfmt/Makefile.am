
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

CPPFLAGS = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS)

LFLASH_FATFMT_OBJS = F_LflashFatfmt_0000.o F_LflashFatfmt_0001.o
libpsplflash_fatfmtincludedir = @PSPSDK_INCLUDEDIR@
libpsplflash_fatfmtinclude_HEADERS = psplflash_fatfmt.h

lib_LIBRARIES = libpsplflash_fatfmt.a
libpsplflash_fatfmt_a_SOURCES = LflashFatfmt.S
libpsplflash_fatfmt_a_LIBADD  = $(LFLASH_FATFMT_OBJS)

$(LFLASH_FATFMT_OBJS): LflashFatfmt.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@
