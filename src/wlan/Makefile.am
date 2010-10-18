
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

WLAN_OBJS = sceWlanDrv_0000.o sceWlanDrv_0001.o sceWlanDrv_0002.o sceWlanDrv_0003.o 
WLANLIB_OBJS = sceWlanDrv_lib_0000.o sceWlanDrv_lib_0001.o sceWlanDrv_lib_0002.o sceWlanDrv_lib_0003.o sceWlanDrv_lib_0004.o sceWlanDrv_lib_0005.o sceWlanDrv_lib_0006.o sceWlanDrv_lib_0007.o sceWlanDrv_lib_0008.o sceWlanDrv_lib_0009.o sceWlanDrv_lib_0010.o sceWlanDrv_lib_0011.o sceWlanDrv_lib_0012.o sceWlanDrv_lib_0013.o sceWlanDrv_lib_0014.o sceWlanDrv_lib_0015.o sceWlanDrv_lib_0016.o sceWlanDrv_lib_0017.o sceWlanDrv_lib_0018.o 

libpspwlanincludedir = @PSPSDK_INCLUDEDIR@
libpspwlaninclude_HEADERS = pspwlan.h

lib_LIBRARIES = libpspwlan.a
libpspwlan_a_SOURCES = sceWlanDrv.S sceWlanDrv_lib.S
libpspwlan_a_LIBADD  = $(WLAN_OBJS) $(WLANLIB_OBJS)

$(WLAN_OBJS): sceWlanDrv.S
	$(COMPILE) -DF_$* $< -c -o $@

$(WLANLIB_OBJS): sceWlanDrv_lib.S
	$(COMPILE) -DF_$* $< -c -o $@
