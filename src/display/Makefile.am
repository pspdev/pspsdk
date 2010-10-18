
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

DISPLAY_OBJS = sceDisplay_0000.o sceDisplay_0001.o sceDisplay_0002.o sceDisplay_0003.o sceDisplay_0004.o sceDisplay_0005.o sceDisplay_0006.o sceDisplay_0007.o sceDisplay_0008.o sceDisplay_0009.o sceDisplay_0010.o sceDisplay_0011.o sceDisplay_0012.o sceDisplay_0013.o sceDisplay_0014.o sceDisplay_0015.o sceDisplay_0016.o sceDisplay_0017.o 

DISPLAYDRIVER_OBJS = sceDisplay_driver_0000.o sceDisplay_driver_0001.o sceDisplay_driver_0002.o sceDisplay_driver_0003.o sceDisplay_driver_0004.o sceDisplay_driver_0005.o sceDisplay_driver_0006.o sceDisplay_driver_0007.o sceDisplay_driver_0008.o sceDisplay_driver_0009.o sceDisplay_driver_0010.o sceDisplay_driver_0011.o sceDisplay_driver_0012.o sceDisplay_driver_0013.o sceDisplay_driver_0014.o sceDisplay_driver_0015.o sceDisplay_driver_0016.o sceDisplay_driver_0017.o sceDisplay_driver_0018.o sceDisplay_driver_0019.o sceDisplay_driver_0020.o sceDisplay_driver_0021.o sceDisplay_driver_0022.o sceDisplay_driver_0023.o sceDisplay_driver_0024.o sceDisplay_driver_0025.o sceDisplay_driver_0026.o 

libpspdisplayincludedir = @PSPSDK_INCLUDEDIR@
libpspdisplayinclude_HEADERS = pspdisplay.h pspdisplay_kernel.h

lib_LIBRARIES = libpspdisplay.a libpspdisplay_driver.a
libpspdisplay_a_SOURCES = sceDisplay.S 
libpspdisplay_a_LIBADD = $(DISPLAY_OBJS)
libpspdisplay_driver_a_SOURCES = sceDisplay_driver.S
libpspdisplay_driver_a_LIBADD = $(DISPLAYDRIVER_OBJS)

$(DISPLAY_OBJS): sceDisplay.S
	$(COMPILE) -DF_$* $< -c -o $@

$(DISPLAYDRIVER_OBJS): sceDisplay_driver.S
	$(COMPILE) -DF_$* $< -c -o $@
