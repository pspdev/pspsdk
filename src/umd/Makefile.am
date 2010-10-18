
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

UMDUSER_OBJS = sceUmdUser_0000.o sceUmdUser_0001.o sceUmdUser_0002.o sceUmdUser_0003.o sceUmdUser_0004.o sceUmdUser_0005.o sceUmdUser_0006.o sceUmdUser_0007.o sceUmdUser_0008.o sceUmdUser_0009.o sceUmdUser_0010.o sceUmdUser_0011.o sceUmdUser_0012.o sceUmdUser_0013.o sceUmdUser_0014.o

UMD_OBJS = sceUmd_0000.o sceUmd_0001.o sceUmd_0002.o sceUmd_0003.o sceUmd_0004.o sceUmd_0005.o sceUmd_0006.o sceUmd_0007.o sceUmd_0008.o sceUmd_0009.o sceUmd_0010.o sceUmd_0011.o sceUmd_0012.o sceUmd_0013.o sceUmd_0014.o sceUmd_0015.o sceUmd_0016.o sceUmd_0017.o sceUmd_0018.o sceUmd_0019.o sceUmd_0020.o sceUmd_0021.o sceUmd_0022.o sceUmd_0023.o sceUmd_0024.o sceUmd_0025.o sceUmd_0026.o sceUmd_0027.o sceUmd_0028.o sceUmd_0029.o sceUmd_0030.o sceUmd_0031.o sceUmd_0032.o sceUmd_0033.o sceUmd_0034.o sceUmd_0035.o

libpspumdlincludedir = @PSPSDK_INCLUDEDIR@
libpspumdlinclude_HEADERS = pspumd.h

lib_LIBRARIES = libpspumd.a libpspumd_driver.a

libpspumd_a_SOURCES = sceUmdUser.S
libpspumd_a_LIBADD = $(UMDUSER_OBJS)

libpspumd_driver_a_SOURCES = sceUmd.S
libpspumd_driver_a_LIBADD = $(UMD_OBJS)

$(UMDUSER_OBJS): sceUmdUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(UMD_OBJS): sceUmd.S
	$(COMPILE) -DF_$* $< -c -o $@
