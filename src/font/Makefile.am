
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

CPPFLAGS = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS)

FONT_OBJS = sceLibFont_0000.o sceLibFont_0001.o sceLibFont_0002.o sceLibFont_0003.o sceLibFont_0004.o sceLibFont_0005.o sceLibFont_0006.o sceLibFont_0007.o sceLibFont_0008.o sceLibFont_0009.o sceLibFont_0010.o sceLibFont_0011.o sceLibFont_0012.o sceLibFont_0013.o sceLibFont_0014.o sceLibFont_0015.o sceLibFont_0016.o sceLibFont_0017.o sceLibFont_0018.o sceLibFont_0019.o sceLibFont_0020.o sceLibFont_0021.o sceLibFont_0022.o sceLibFont_0023.o sceLibFont_0024.o sceLibFont_0025.o sceLibFont_0026.o sceLibFont_0027.o sceLibFont_0028.o sceLibFont_0029.o

libpspfontincludedir = @PSPSDK_INCLUDEDIR@
libpspfontinclude_HEADERS = pspfont.h

lib_LIBRARIES = libpspfont.a
libpspfont_a_SOURCES = sceFont.S
libpspfont_a_LIBADD = $(FONT_OBJS)

$(FONT_OBJS): sceFont.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@
