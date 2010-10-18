
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/user -I$(top_srcdir)/src/debug
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

AUDIO_OBJS = sceAudio_0000.o sceAudio_0001.o sceAudio_0002.o sceAudio_0003.o sceAudio_0004.o sceAudio_0005.o sceAudio_0006.o sceAudio_0007.o sceAudio_0008.o sceAudio_0009.o sceAudio_0010.o sceAudio_0011.o sceAudio_0012.o sceAudio_0013.o sceAudio_0014.o sceAudio_0015.o sceAudio_0016.o sceAudio_0017.o sceAudio_0018.o sceAudio_0019.o sceAudio_0020.o sceAudio_0021.o sceAudio_0022.o sceAudio_0023.o sceAudio_0024.o sceAudio_0025.o sceAudio_0026.o sceAudio_0027.o

AUDIO_DRIVER_OBJS = sceAudio_driver_0000.o sceAudio_driver_0001.o sceAudio_driver_0002.o sceAudio_driver_0003.o sceAudio_driver_0004.o sceAudio_driver_0005.o sceAudio_driver_0006.o sceAudio_driver_0007.o sceAudio_driver_0008.o sceAudio_driver_0009.o sceAudio_driver_0010.o sceAudio_driver_0011.o sceAudio_driver_0012.o sceAudio_driver_0013.o sceAudio_driver_0014.o sceAudio_driver_0015.o sceAudio_driver_0016.o sceAudio_driver_0017.o sceAudio_driver_0018.o sceAudio_driver_0019.o sceAudio_driver_0020.o sceAudio_driver_0021.o sceAudio_driver_0022.o sceAudio_driver_0023.o sceAudio_driver_0024.o sceAudio_driver_0025.o sceAudio_driver_0026.o sceAudio_driver_0027.o

CODEC_OBJS = sceAudiocodec_0000.o sceAudiocodec_0001.o sceAudiocodec_0002.o sceAudiocodec_0003.o sceAudiocodec_0004.o sceAudiocodec_0005.o sceAudiocodec_0006.o sceAudiocodec_0007.o sceAudiocodec_0008.o 

libpspaudioincludedir = @PSPSDK_INCLUDEDIR@
libpspaudioinclude_HEADERS = pspaudio.h

libpspaudio_driverincludedir = @PSPSDK_INCLUDEDIR@
libpspaudio_driverinclude_HEADERS = pspaudio_kernel.h

libpspaudiolibincludedir = @PSPSDK_INCLUDEDIR@
libpspaudiolibinclude_HEADERS = pspaudiolib.h

libpspaudiocodecincludedir = @PSPSDK_INCLUDEDIR@
libpspaudiocodecinclude_HEADERS = pspaudiocodec.h

lib_LIBRARIES = libpspaudio.a libpspaudio_driver.a libpspaudiolib.a libpspaudiocodec.a

libpspaudio_a_SOURCES = sceAudio.S
libpspaudio_a_LIBADD = $(AUDIO_OBJS)

libpspaudio_driver_a_SOURCES = sceAudio_driver.S
libpspaudio_driver_a_LIBADD = $(AUDIO_DRIVER_OBJS)

libpspaudiolib_a_SOURCES = pspaudiolib.c

libpspaudiocodec_a_SOURCES = sceAudiocodec.S
libpspaudiocodec_a_LIBADD = $(CODEC_OBJS)

$(AUDIO_OBJS): sceAudio.S
	$(COMPILE) -DF_$* $< -c -o $@

$(AUDIO_DRIVER_OBJS): sceAudio_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

$(CODEC_OBJS): sceAudiocodec.S
	$(COMPILE) -DF_$* $< -c -o $@
