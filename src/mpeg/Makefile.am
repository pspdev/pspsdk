
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

MPEG_OBJS = sceMpeg_0000.o sceMpeg_0001.o sceMpeg_0002.o sceMpeg_0003.o sceMpeg_0004.o sceMpeg_0005.o sceMpeg_0006.o sceMpeg_0007.o sceMpeg_0008.o sceMpeg_0009.o sceMpeg_0010.o sceMpeg_0011.o sceMpeg_0012.o sceMpeg_0013.o sceMpeg_0014.o sceMpeg_0015.o sceMpeg_0016.o sceMpeg_0017.o sceMpeg_0018.o sceMpeg_0019.o sceMpeg_0020.o sceMpeg_0021.o sceMpeg_0022.o sceMpeg_0023.o sceMpeg_0024.o sceMpeg_0025.o sceMpeg_0026.o sceMpeg_0027.o sceMpeg_0028.o sceMpeg_0029.o sceMpeg_0030.o sceMpeg_0031.o sceMpeg_0032.o sceMpeg_0033.o sceMpeg_0034.o sceMpeg_0035.o sceMpeg_0036.o sceMpeg_0037.o sceMpeg_0038.o

MPEGBASE_OBJS = sceMpegbase_0000.o sceMpegbase_0001.o sceMpegbase_0002.o sceMpegbase_0003.o sceMpegbase_0004.o sceMpegbase_0005.o sceMpegbase_0006.o sceMpegbase_0007.o sceMpegbase_0008.o sceMpegbase_0009.o

MPEGBASE_DRIVER_OBJS = sceMpegbase_driver_0000.o sceMpegbase_driver_0001.o sceMpegbase_driver_0002.o sceMpegbase_driver_0003.o sceMpegbase_driver_0004.o sceMpegbase_driver_0005.o sceMpegbase_driver_0006.o sceMpegbase_driver_0007.o sceMpegbase_driver_0008.o sceMpegbase_driver_0009.o sceMpegbase_driver_0010.o

JPEG_OBJS =  sceJpeg_0000.o sceJpeg_0001.o sceJpeg_0002.o sceJpeg_0003.o sceJpeg_0004.o sceJpeg_0005.o sceJpeg_0006.o sceJpeg_0007.o sceJpeg_0008.o sceJpeg_0009.o sceJpeg_0010.o sceJpeg_0011.o sceJpeg_0012.o sceJpeg_0013.o


libpspmpegincludedir = @PSPSDK_INCLUDEDIR@
libpspmpeginclude_HEADERS = pspmpeg.h

libpspmpegbaseincludedir = @PSPSDK_INCLUDEDIR@
libpspmpegbaseinclude_HEADERS = pspmpegbase.h

libpspmpegbase_driverincludedir = @PSPSDK_INCLUDEDIR@
libpspmpegbase_driverinclude_HEADERS = pspmpegbase.h

libpspjpegincludedir = @PSPSDK_INCLUDEDIR@
libpspjpeginclude_HEADERS = pspjpeg.h


lib_LIBRARIES = libpspmpeg.a libpspmpegbase.a libpspmpegbase_driver.a libpspjpeg.a


libpspmpeg_a_SOURCES = sceMpeg.S
libpspmpeg_a_LIBADD = $(MPEG_OBJS)

libpspmpegbase_a_SOURCES = sceMpegbase.S
libpspmpegbase_a_LIBADD = $(MPEGBASE_OBJS)

libpspmpegbase_driver_a_SOURCES = sceMpegbase_driver.S
libpspmpegbase_driver_a_LIBADD = $(MPEGBASE_DRIVER_OBJS)

libpspjpeg_a_SOURCES = sceJpeg.S
libpspjpeg_a_LIBADD = $(JPEG_OBJS)


$(MPEG_OBJS): sceMpeg.S
	$(COMPILE) -DF_$* $< -c -o $@

$(MPEGBASE_OBJS): sceMpegbase.S
	$(COMPILE) -DF_$* $< -c -o $@

$(MPEGBASE_DRIVER_OBJS): sceMpegbase_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

$(JPEG_OBJS): sceJpeg.S
	$(COMPILE) -DF_$* $< -c -o $@

