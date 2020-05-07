
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

MP3_OBJS = sceMp3_0000.o sceMp3_0001.o sceMp3_0002.o sceMp3_0003.o sceMp3_0004.o sceMp3_0005.o sceMp3_0006.o sceMp3_0007.o sceMp3_0008.o sceMp3_0009.o sceMp3_0010.o sceMp3_0011.o sceMp3_0012.o sceMp3_0013.o sceMp3_0014.o sceMp3_0015.o sceMp3_0016.o sceMp3_0017.o sceMp3_0018.o sceMp3_0019.o

libpspmp3includedir = @PSPSDK_INCLUDEDIR@
libpspmp3include_HEADERS = pspmp3.h

lib_LIBRARIES = libpspmp3.a


libpspmp3_a_SOURCES = sceMp3.S
libpspmp3_a_LIBADD = $(MP3_OBJS)

$(MP3_OBJS): sceMp3.S
	$(COMPILE) -DF_$* $< -c -o $@
