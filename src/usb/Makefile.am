
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES) 

USB_OBJS = sceUsb_0000.o sceUsb_0001.o sceUsb_0002.o sceUsb_0003.o sceUsb_0004.o sceUsb_0005.o sceUsb_0006.o sceUsb_0007.o sceUsb_0008.o sceUsb_0009.o 

USBDRIVER_OBJS= sceUsb_driver_0000.o sceUsb_driver_0001.o sceUsb_driver_0002.o sceUsb_driver_0003.o sceUsb_driver_0004.o sceUsb_driver_0005.o sceUsb_driver_0006.o sceUsb_driver_0007.o sceUsb_driver_0008.o sceUsb_driver_0009.o sceUsb_driver_0010.o

USBBUSDRIVER_OBJS=sceUsbBus_driver_0000.o sceUsbBus_driver_0001.o sceUsbBus_driver_0002.o sceUsbBus_driver_0003.o sceUsbBus_driver_0004.o sceUsbBus_driver_0005.o sceUsbBus_driver_0006.o sceUsbBus_driver_0007.o sceUsbBus_driver_0008.o sceUsbBus_driver_0009.o 

USBCAM_OBJS = sceUsbCam_0000.o sceUsbCam_0001.o sceUsbCam_0002.o sceUsbCam_0003.o sceUsbCam_0004.o sceUsbCam_0005.o sceUsbCam_0006.o sceUsbCam_0007.o sceUsbCam_0008.o sceUsbCam_0009.o sceUsbCam_0010.o sceUsbCam_0011.o sceUsbCam_0012.o sceUsbCam_0013.o sceUsbCam_0014.o sceUsbCam_0015.o sceUsbCam_0016.o sceUsbCam_0017.o sceUsbCam_0018.o sceUsbCam_0019.o sceUsbCam_0020.o sceUsbCam_0021.o sceUsbCam_0022.o sceUsbCam_0023.o sceUsbCam_0024.o sceUsbCam_0025.o sceUsbCam_0026.o sceUsbCam_0027.o sceUsbCam_0028.o sceUsbCam_0029.o sceUsbCam_0030.o sceUsbCam_0031.o sceUsbCam_0032.o sceUsbCam_0033.o sceUsbCam_0034.o sceUsbCam_0035.o sceUsbCam_0036.o sceUsbCam_0037.o sceUsbCam_0038.o sceUsbCam_0039.o sceUsbCam_0040.o sceUsbCam_0041.o sceUsbCam_0042.o sceUsbCam_0043.o sceUsbCam_0044.o sceUsbCam_0045.o sceUsbCam_0046.o sceUsbCam_0047.o sceUsbCam_0048.o sceUsbCam_0049.o sceUsbCam_0050.o sceUsbCam_0051.o sceUsbCam_0052.o sceUsbCam_0053.o sceUsbCam_0054.o


libpspusbincludedir = @PSPSDK_INCLUDEDIR@

libpspusbinclude_HEADERS =	\
	pspusb.h pspusbbus.h pspusbcam.h pspusbacc.h

lib_LIBRARIES = libpspusb.a libpspusb_driver.a libpspusbbus_driver.a libpspusbcam.a

libpspusb_a_SOURCES = sceUsb.S
libpspusb_a_LIBADD  = $(USB_OBJS)

libpspusb_driver_a_SOURCES = sceUsb_driver.S
libpspusb_driver_a_LIBADD = $(USBDRIVER_OBJS)

libpspusbbus_driver_a_SOURCES = sceUsbBus_driver.S
libpspusbbus_driver_a_LIBADD = $(USBBUSDRIVER_OBJS)

libpspusbcam_a_SOURCES = sceUsbCam.S
libpspusbcam_a_LIBADD  = $(USBCAM_OBJS)

$(USB_OBJS): sceUsb.S
	$(COMPILE) -DF_$* $< -c -o $@

$(USBDRIVER_OBJS): sceUsb_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

$(USBBUSDRIVER_OBJS): sceUsbBus_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

$(USBCAM_OBJS): sceUsbCam.S
	$(COMPILE) -DF_$* $< -c -o $@
