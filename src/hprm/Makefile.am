
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

HPRM_OBJS = sceHprm_0000.o sceHprm_0001.o sceHprm_0002.o sceHprm_0003.o sceHprm_0004.o sceHprm_0005.o sceHprm_0006.o sceHprm_0007.o sceHprm_0008.o 

HPRM_DRIVER_OBJS = sceHprm_driver_0000.o sceHprm_driver_0001.o sceHprm_driver_0002.o sceHprm_driver_0003.o sceHprm_driver_0004.o sceHprm_driver_0005.o sceHprm_driver_0006.o sceHprm_driver_0007.o sceHprm_driver_0008.o sceHprm_driver_0009.o sceHprm_driver_0010.o sceHprm_driver_0011.o sceHprm_driver_0012.o sceHprm_driver_0013.o sceHprm_driver_0014.o sceHprm_driver_0015.o sceHprm_driver_0016.o sceHprm_driver_0017.o sceHprm_driver_0018.o 

libpsphprmincludedir = @PSPSDK_INCLUDEDIR@
libpsphprminclude_HEADERS = psphprm.h

lib_LIBRARIES = libpsphprm.a libpsphprm_driver.a
libpsphprm_a_SOURCES = sceHprm.S
libpsphprm_a_LIBADD  = $(HPRM_OBJS)
libpsphprm_driver_a_SOURCES = sceHprm_driver.S
libpsphprm_driver_a_LIBADD  = $(HPRM_DRIVER_OBJS)

$(HPRM_OBJS): sceHprm.S
	$(COMPILE) -DF_$* $< -c -o $@

$(HPRM_DRIVER_OBJS): sceHprm_driver.S
	$(COMPILE) -DF_$* $< -c -o $@
