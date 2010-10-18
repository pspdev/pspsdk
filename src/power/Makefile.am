
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

POWER_OBJS = scePower_0000.o scePower_0001.o scePower_0002.o scePower_0003.o scePower_0004.o scePower_0005.o scePower_0006.o scePower_0007.o scePower_0008.o scePower_0009.o scePower_0010.o scePower_0011.o scePower_0012.o scePower_0013.o scePower_0014.o scePower_0015.o scePower_0016.o scePower_0017.o scePower_0018.o scePower_0019.o scePower_0020.o scePower_0021.o scePower_0022.o scePower_0023.o scePower_0024.o scePower_0025.o scePower_0026.o scePower_0027.o scePower_0028.o scePower_0029.o scePower_0030.o scePower_0031.o scePower_0032.o scePower_0033.o scePower_0034.o scePower_0035.o scePower_0036.o scePower_0037.o scePower_0038.o scePower_0039.o scePower_0040.o scePower_0041.o scePower_0042.o scePower_0043.o scePower_0044.o scePower_0045.o scePower_0046.o 

POWERDRIVER_OBJS= scePower_driver_0000.o scePower_driver_0001.o scePower_driver_0002.o scePower_driver_0003.o scePower_driver_0004.o scePower_driver_0005.o scePower_driver_0006.o scePower_driver_0007.o scePower_driver_0008.o scePower_driver_0009.o scePower_driver_0010.o scePower_driver_0011.o scePower_driver_0012.o scePower_driver_0013.o scePower_driver_0014.o scePower_driver_0015.o scePower_driver_0016.o scePower_driver_0017.o scePower_driver_0018.o scePower_driver_0019.o scePower_driver_0020.o scePower_driver_0021.o scePower_driver_0022.o scePower_driver_0023.o scePower_driver_0024.o scePower_driver_0025.o scePower_driver_0026.o scePower_driver_0027.o scePower_driver_0028.o scePower_driver_0029.o scePower_driver_0030.o scePower_driver_0031.o scePower_driver_0032.o scePower_driver_0033.o scePower_driver_0034.o scePower_driver_0035.o scePower_driver_0036.o scePower_driver_0037.o scePower_driver_0038.o scePower_driver_0039.o scePower_driver_0040.o scePower_driver_0041.o scePower_driver_0042.o scePower_driver_0043.o scePower_driver_0044.o scePower_driver_0045.o scePower_driver_0046.o scePower_driver_0047.o scePower_driver_0048.o scePower_driver_0049.o scePower_driver_0050.o scePower_driver_0051.o scePower_driver_0052.o scePower_driver_0053.o scePower_driver_0054.o scePower_driver_0055.o scePower_driver_0056.o scePower_driver_0057.o scePower_driver_0058.o scePower_driver_0059.o scePower_driver_0060.o scePower_driver_0061.o scePower_driver_0062.o scePower_driver_0063.o scePower_driver_0064.o 

libpsppowerincludedir = @PSPSDK_INCLUDEDIR@
libpsppowerinclude_HEADERS = psppower.h

lib_LIBRARIES = libpsppower.a libpsppower_driver.a
libpsppower_a_SOURCES = scePower.S 
libpsppower_a_LIBADD = $(POWER_OBJS)

libpsppower_driver_a_SOURCES = scePower_driver.S
libpsppower_driver_a_LIBADD = $(POWERDRIVER_OBJS)

$(POWER_OBJS): scePower.S
	$(COMPILE) -DF_$* $< -c -o $@

$(POWERDRIVER_OBJS): scePower_driver.S
	$(COMPILE) -DF_$* $< -c -o $@
