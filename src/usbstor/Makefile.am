
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES) 

USBSTOR_OBJS = sceUsbstor_0000.o sceUsbstor_0001.o 
USBSTORBOOT_OBJS = sceUsbstorBoot_0000.o sceUsbstorBoot_0001.o sceUsbstorBoot_0002.o sceUsbstorBoot_0003.o sceUsbstorBoot_0004.o sceUsbstorBoot_0005.o sceUsbstorBoot_0006.o 

libpspusbstorincludedir = @PSPSDK_INCLUDEDIR@

libpspusbstorinclude_HEADERS =	\
	pspusbstor.h

lib_LIBRARIES = libpspusbstor.a

libpspusbstor_a_SOURCES = sceUsbstor.S	sceUsbstorBoot.S
libpspusbstor_a_LIBADD = $(USBSTOR_OBJS) $(USBSTORBOOT_OBJS)

$(USBSTOR_OBJS): sceUsbstor.S
	$(COMPILE) -DF_$* $< -c -o $@

$(USBSTORBOOT_OBJS): sceUsbstorBoot.S
	$(COMPILE) -DF_$* $< -c -o $@
