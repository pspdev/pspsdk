
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

REG_OBJS = sceReg_0000.o sceReg_0001.o sceReg_0002.o sceReg_0003.o sceReg_0004.o sceReg_0005.o sceReg_0006.o sceReg_0007.o sceReg_0008.o sceReg_0009.o sceReg_0010.o sceReg_0011.o sceReg_0012.o sceReg_0013.o sceReg_0014.o sceReg_0015.o sceReg_0016.o sceReg_0017.o sceReg_0018.o 

REGDRIVER_OBJS = sceReg_driver_0000.o sceReg_driver_0001.o sceReg_driver_0002.o sceReg_driver_0003.o sceReg_driver_0004.o sceReg_driver_0005.o sceReg_driver_0006.o sceReg_driver_0007.o sceReg_driver_0008.o sceReg_driver_0009.o sceReg_driver_0010.o sceReg_driver_0011.o sceReg_driver_0012.o sceReg_driver_0013.o sceReg_driver_0014.o sceReg_driver_0015.o sceReg_driver_0016.o sceReg_driver_0017.o sceReg_driver_0018.o sceReg_driver_0019.o 

libpspregincludedir = @PSPSDK_INCLUDEDIR@
libpspreginclude_HEADERS = pspreg.h

lib_LIBRARIES = libpspreg.a libpspreg_driver.a
libpspreg_a_SOURCES = sceReg.S
libpspreg_a_LIBADD = $(REG_OBJS)

libpspreg_driver_a_SOURCES = sceReg_driver.S
libpspreg_driver_a_LIBADD = $(REGDRIVER_OBJS)

$(REG_OBJS): sceReg.S
	$(COMPILE) -DF_$* $< -c -o $@

$(REGDRIVER_OBJS): sceReg_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

