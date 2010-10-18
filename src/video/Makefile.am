
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

VIDEOCODEC_OBJS = sceVideocodec_0000.o sceVideocodec_0001.o sceVideocodec_0002.o sceVideocodec_0003.o sceVideocodec_0004.o sceVideocodec_0005.o sceVideocodec_0006.o sceVideocodec_0007.o sceVideocodec_0008.o sceVideocodec_0009.o sceVideocodec_0010.o sceVideocodec_0011.o sceVideocodec_0012.o sceVideocodec_0013.o


libpspvideocodecincludedir = @PSPSDK_INCLUDEDIR@
libpspvideocodecinclude_HEADERS = pspvideocodec.h


lib_LIBRARIES = libpspvideocodec.a


libpspvideocodec_a_SOURCES = sceVideocodec.S
libpspvideocodec_a_LIBADD = $(VIDEOCODEC_OBJS)

$(VIDEOCODEC_OBJS): sceVideocodec.S
	$(COMPILE) -DF_$* $< -c -o $@
