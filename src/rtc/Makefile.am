
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

RTC_OBJS = sceRtc_0000.o sceRtc_0001.o sceRtc_0002.o sceRtc_0003.o sceRtc_0004.o sceRtc_0005.o sceRtc_0006.o sceRtc_0007.o sceRtc_0008.o sceRtc_0009.o sceRtc_0010.o sceRtc_0011.o sceRtc_0012.o sceRtc_0013.o sceRtc_0014.o sceRtc_0015.o sceRtc_0016.o sceRtc_0017.o sceRtc_0018.o sceRtc_0019.o sceRtc_0020.o sceRtc_0021.o sceRtc_0022.o sceRtc_0023.o sceRtc_0024.o sceRtc_0025.o sceRtc_0026.o sceRtc_0027.o sceRtc_0028.o sceRtc_0029.o sceRtc_0030.o sceRtc_0031.o sceRtc_0032.o sceRtc_0033.o sceRtc_0034.o sceRtc_0035.o sceRtc_0036.o sceRtc_0037.o sceRtc_0038.o sceRtc_0039.o sceRtc_0040.o sceRtc_0041.o 

RTCDRIVER_OBJS = sceRtc_driver_0000.o sceRtc_driver_0001.o sceRtc_driver_0002.o sceRtc_driver_0003.o sceRtc_driver_0004.o sceRtc_driver_0005.o sceRtc_driver_0006.o sceRtc_driver_0007.o sceRtc_driver_0008.o sceRtc_driver_0009.o sceRtc_driver_0010.o sceRtc_driver_0011.o sceRtc_driver_0012.o sceRtc_driver_0013.o sceRtc_driver_0014.o sceRtc_driver_0015.o sceRtc_driver_0016.o sceRtc_driver_0017.o sceRtc_driver_0018.o sceRtc_driver_0019.o sceRtc_driver_0020.o sceRtc_driver_0021.o sceRtc_driver_0022.o sceRtc_driver_0023.o sceRtc_driver_0024.o sceRtc_driver_0025.o sceRtc_driver_0026.o sceRtc_driver_0027.o sceRtc_driver_0028.o sceRtc_driver_0029.o sceRtc_driver_0030.o sceRtc_driver_0031.o sceRtc_driver_0032.o sceRtc_driver_0033.o sceRtc_driver_0034.o sceRtc_driver_0035.o sceRtc_driver_0036.o sceRtc_driver_0037.o sceRtc_driver_0038.o sceRtc_driver_0039.o sceRtc_driver_0040.o sceRtc_driver_0041.o sceRtc_driver_0042.o sceRtc_driver_0043.o sceRtc_driver_0044.o sceRtc_driver_0045.o sceRtc_driver_0046.o sceRtc_driver_0047.o sceRtc_driver_0048.o sceRtc_driver_0049.o sceRtc_driver_0050.o sceRtc_driver_0051.o sceRtc_driver_0052.o sceRtc_driver_0053.o sceRtc_driver_0054.o sceRtc_driver_0055.o sceRtc_driver_0056.o 

libpsprtcincludedir = @PSPSDK_INCLUDEDIR@
libpsprtcinclude_HEADERS = psprtc.h

lib_LIBRARIES = libpsprtc.a libpsprtc_driver.a
libpsprtc_a_SOURCES = sceRtc.S
libpsprtc_a_LIBADD = $(RTC_OBJS)

libpsprtc_driver_a_SOURCES = sceRtc_driver.S
libpsprtc_driver_a_LIBADD = $(RTCDRIVER_OBJS)

$(RTC_OBJS): sceRtc.S
	$(COMPILE) -DF_$* $< -c -o $@

$(RTCDRIVER_OBJS): sceRtc_driver.S
	$(COMPILE) -DF_$* $< -c -o $@
