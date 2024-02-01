
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

CPPFLAGS = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/user -I$(top_srcdir)/src/debug
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS)

VAUDIO_OBJS = sceVaudio_0000.o sceVaudio_0001.o sceVaudio_0002.o sceVaudio_0003.o sceVaudio_0004.o sceVaudio_0005.o sceVaudio_0006.o sceVaudio_0007.o sceVaudio_0008.o

libpspvaudioincludedir = @PSPSDK_INCLUDEDIR@
libpspvaudioinclude_HEADERS = pspvaudio.h

lib_LIBRARIES = libpspvaudio.a

libpspvaudio_a_SOURCES = sceVaudio.S
libpspvaudio_a_LIBADD = $(VAUDIO_OBJS)

$(VAUDIO_OBJS): sceVaudio.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@
