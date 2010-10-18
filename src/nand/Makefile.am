
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

NAND_DRIVER_OBJS = sceNand_driver_0000.o sceNand_driver_0001.o sceNand_driver_0002.o sceNand_driver_0003.o sceNand_driver_0004.o sceNand_driver_0005.o sceNand_driver_0006.o sceNand_driver_0007.o sceNand_driver_0008.o sceNand_driver_0009.o sceNand_driver_0010.o sceNand_driver_0011.o sceNand_driver_0012.o sceNand_driver_0013.o sceNand_driver_0014.o sceNand_driver_0015.o sceNand_driver_0016.o sceNand_driver_0017.o sceNand_driver_0018.o sceNand_driver_0019.o sceNand_driver_0020.o sceNand_driver_0021.o sceNand_driver_0022.o sceNand_driver_0023.o sceNand_driver_0024.o sceNand_driver_0025.o sceNand_driver_0026.o sceNand_driver_0027.o sceNand_driver_0028.o sceNand_driver_0029.o sceNand_driver_0030.o sceNand_driver_0031.o sceNand_driver_0032.o sceNand_driver_0033.o sceNand_driver_0034.o sceNand_driver_0035.o sceNand_driver_0036.o sceNand_driver_0037.o sceNand_driver_0038.o sceNand_driver_0039.o 

libpspnandincludedir = @PSPSDK_INCLUDEDIR@
libpspnandinclude_HEADERS = pspnand_driver.h

lib_LIBRARIES = libpspnand_driver.a
libpspnand_driver_a_SOURCES = sceNand_driver.S
libpspnand_driver_a_LIBADD = $(NAND_DRIVER_OBJS)

$(NAND_DRIVER_OBJS): sceNand_driver.S
	$(COMPILE) -DF_$* $< -c -o $@
