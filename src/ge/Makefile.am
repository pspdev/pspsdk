
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

GE_OBJS = sceGe_user_0000.o sceGe_user_0001.o sceGe_user_0002.o sceGe_user_0003.o sceGe_user_0004.o sceGe_user_0005.o sceGe_user_0006.o sceGe_user_0007.o sceGe_user_0008.o sceGe_user_0009.o sceGe_user_0010.o sceGe_user_0011.o sceGe_user_0012.o sceGe_user_0013.o sceGe_user_0014.o sceGe_user_0015.o sceGe_user_0016.o sceGe_user_0017.o 

GEDRIVER_OBJS = sceGe_driver_0000.o sceGe_driver_0001.o sceGe_driver_0002.o sceGe_driver_0003.o sceGe_driver_0004.o sceGe_driver_0005.o sceGe_driver_0006.o sceGe_driver_0007.o sceGe_driver_0008.o sceGe_driver_0009.o sceGe_driver_0010.o sceGe_driver_0011.o sceGe_driver_0012.o sceGe_driver_0013.o sceGe_driver_0014.o sceGe_driver_0015.o sceGe_driver_0016.o sceGe_driver_0017.o sceGe_driver_0018.o sceGe_driver_0019.o sceGe_driver_0020.o sceGe_driver_0021.o sceGe_driver_0022.o sceGe_driver_0023.o 

libpspgeincludedir = @PSPSDK_INCLUDEDIR@
libpspgeinclude_HEADERS = pspge.h

lib_LIBRARIES = libpspge.a libpspge_driver.a
libpspge_a_SOURCES = sceGe_user.S
libpspge_a_LIBADD = $(GE_OBJS)
libpspge_driver_a_SOURCES = sceGe_driver.S
libpspge_driver_a_LIBADD = $(GEDRIVER_OBJS)

$(GE_OBJS): sceGe_user.S
	$(COMPILE) -DF_$* $< -c -o $@

$(GEDRIVER_OBJS): sceGe_driver.S
	$(COMPILE) -DF_$* $< -c -o $@
