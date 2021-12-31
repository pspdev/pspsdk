
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

CPPFLAGS = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS)

CHNNLSV_OBJS = sceChnnlsv_0000.o sceChnnlsv_0001.o sceChnnlsv_0002.o sceChnnlsv_0003.o sceChnnlsv_0004.o sceChnnlsv_0005.o sceChnnlsv_0006.o
VSHBRIDGE_OBJS = sceVshBridge_0000.o sceVshBridge_0001.o sceVshBridge_0002.o sceVshBridge_0003.o sceVshBridge_0004.o sceVshBridge_0005.o sceVshBridge_0006.o sceVshBridge_0007.o sceVshBridge_0008.o sceVshBridge_0009.o sceVshBridge_0010.o sceVshBridge_0011.o sceVshBridge_0012.o sceVshBridge_0013.o sceVshBridge_0014.o sceVshBridge_0015.o sceVshBridge_0016.o sceVshBridge_0017.o sceVshBridge_0018.o sceVshBridge_0019.o sceVshBridge_0020.o sceVshBridge_0021.o sceVshBridge_0022.o sceVshBridge_0023.o sceVshBridge_0024.o sceVshBridge_0025.o sceVshBridge_0026.o sceVshBridge_0027.o sceVshBridge_0028.o sceVshBridge_0029.o sceVshBridge_0030.o sceVshBridge_0031.o sceVshBridge_0032.o sceVshBridge_0033.o sceVshBridge_0034.o sceVshBridge_0035.o sceVshBridge_0036.o sceVshBridge_0037.o sceVshBridge_0038.o sceVshBridge_0039.o sceVshBridge_0040.o sceVshBridge_0041.o sceVshBridge_0042.o sceVshBridge_0043.o sceVshBridge_0044.o sceVshBridge_0045.o sceVshBridge_0046.o sceVshBridge_0047.o sceVshBridge_0048.o sceVshBridge_0049.o sceVshBridge_0050.o sceVshBridge_0051.o sceVshBridge_0052.o sceVshBridge_0053.o sceVshBridge_0054.o sceVshBridge_0055.o sceVshBridge_0056.o sceVshBridge_0057.o sceVshBridge_0058.o sceVshBridge_0059.o sceVshBridge_0060.o sceVshBridge_0061.o sceVshBridge_0062.o 
PAF_OBJS = scePaf_0000.o scePaf_0001.o scePaf_0002.o scePaf_0003.o scePaf_0004.o scePaf_0005.o scePaf_0006.o scePaf_0007.o scePaf_0008.o

libpspchnnlsvincludedir = @PSPSDK_INCLUDEDIR@
libpspchnnlsvinclude_HEADERS = pspchnnlsv.h psppaf.h

lib_LIBRARIES = libpspchnnlsv.a libpspvshbridge.a libpsppaf.a
libpspchnnlsv_a_SOURCES = sceChnnlsv.S
libpspchnnlsv_a_LIBADD = $(CHNNLSV_OBJS)
libpspvshbridge_a_SOURCES = sceVshBridge.S
libpspvshbridge_a_LIBADD = $(VSHBRIDGE_OBJS)
libpsppaf_a_SOURCES = scePaf.S
libpsppaf_a_LIBADD = $(PAF_OBJS)

$(CHNNLSV_OBJS): sceChnnlsv.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@

$(VSHBRIDGE_OBJS): sceVshBridge.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@

$(PAF_OBJS): scePaf.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@
