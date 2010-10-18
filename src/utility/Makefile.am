
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

UTILITY_OBJS = sceUtility_0000.o sceUtility_0001.o sceUtility_0002.o sceUtility_0003.o sceUtility_0004.o sceUtility_0005.o sceUtility_0006.o sceUtility_0007.o sceUtility_0008.o sceUtility_0009.o sceUtility_0010.o sceUtility_0011.o sceUtility_0012.o sceUtility_0013.o sceUtility_0014.o sceUtility_0015.o sceUtility_0016.o sceUtility_0017.o sceUtility_0018.o sceUtility_0019.o sceUtility_0020.o sceUtility_0021.o sceUtility_0022.o sceUtility_0023.o sceUtility_0024.o sceUtility_0025.o sceUtility_0026.o sceUtility_0027.o sceUtility_0028.o sceUtility_0029.o sceUtility_0030.o sceUtility_0031.o sceUtility_0032.o sceUtility_0033.o sceUtility_0034.o sceUtility_0035.o sceUtility_0036.o sceUtility_0037.o sceUtility_0038.o sceUtility_0039.o sceUtility_0040.o sceUtility_0041.o sceUtility_0042.o sceUtility_0043.o sceUtility_0044.o sceUtility_0045.o sceUtility_0046.o sceUtility_0047.o

NETPARAM_OBJS = sceUtility_netparam_internal_0000.o sceUtility_netparam_internal_0001.o sceUtility_netparam_internal_0002.o sceUtility_netparam_internal_0003.o sceUtility_netparam_internal_0004.o 

libpsputilityincludedir = @PSPSDK_INCLUDEDIR@
libpsputilityinclude_HEADERS = psputility.h \
                               psputility_msgdialog.h \
                               psputility_netconf.h \
                               psputility_netparam.h \
                               psputility_savedata.h \
                               psputility_sysparam.h \
                               psputility_osk.h \
                               psputility_netmodules.h \
                               psputility_avmodules.h \
                               psputility_usbmodules.h \
                               psputility_gamesharing.h \
                               psputility_htmlviewer.h \
                               psputility_modules.h

lib_LIBRARIES = libpsputility.a
libpsputility_a_SOURCES = sceUtility.S sceUtility_netparam_internal.S
libpsputility_a_LIBADD = $(UTILITY_OBJS) $(NETPARAM_OBJS)

$(UTILITY_OBJS): sceUtility.S
	$(COMPILE) -DF_$* $< -c -o $@

$(NETPARAM_OBJS): sceUtility_netparam_internal.S
	$(COMPILE) -DF_$* $< -c -o $@
