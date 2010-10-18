
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

CTRL_OBJS = sceCtrl_0000.o sceCtrl_0001.o sceCtrl_0002.o sceCtrl_0003.o sceCtrl_0004.o sceCtrl_0005.o sceCtrl_0006.o sceCtrl_0007.o sceCtrl_0008.o sceCtrl_0009.o sceCtrl_0010.o sceCtrl_0011.o sceCtrl_0012.o sceCtrl_0013.o sceCtrl_0014.o sceCtrl_0015.o sceCtrl_0016.o

CTRLDRIVER_OBJS = sceCtrl_driver_0000.o sceCtrl_driver_0001.o sceCtrl_driver_0002.o sceCtrl_driver_0003.o sceCtrl_driver_0004.o sceCtrl_driver_0005.o sceCtrl_driver_0006.o sceCtrl_driver_0007.o sceCtrl_driver_0008.o sceCtrl_driver_0009.o sceCtrl_driver_0010.o sceCtrl_driver_0011.o sceCtrl_driver_0012.o sceCtrl_driver_0013.o sceCtrl_driver_0014.o sceCtrl_driver_0015.o sceCtrl_driver_0016.o sceCtrl_driver_0017.o sceCtrl_driver_0018.o sceCtrl_driver_0019.o sceCtrl_driver_0020.o sceCtrl_driver_0021.o sceCtrl_driver_0022.o sceCtrl_driver_0023.o sceCtrl_driver_0024.o sceCtrl_driver_0025.o

libpspctrlincludedir = @PSPSDK_INCLUDEDIR@
libpspctrlinclude_HEADERS = pspctrl.h pspctrl_kernel.h

lib_LIBRARIES = libpspctrl.a libpspctrl_driver.a
libpspctrl_a_SOURCES = sceCtrl.S
libpspctrl_a_LIBADD = $(CTRL_OBJS)

libpspctrl_driver_a_SOURCES = sceCtrl_driver.S
libpspctrl_driver_a_LIBADD = $(CTRLDRIVER_OBJS)

$(CTRL_OBJS): sceCtrl.S
	$(COMPILE) -DF_$* $< -c -o $@

$(CTRLDRIVER_OBJS): sceCtrl_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

