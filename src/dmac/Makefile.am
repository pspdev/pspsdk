libdir := @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

CCASFLAGS := @PSPSDK_CFLAGS@ -I$(top_srcdir)/src/base

DMAC_OBJS := sceDmac_0000.o sceDmac_0001.o sceDmac_0002.o

libpspdmacincludedir := @PSPSDK_INCLUDEDIR@
libpspdmacinclude_HEADERS := pspdmac.h

lib_LIBRARIES := libpspdmac.a
libpspdmac_a_SOURCES := sceDmac.S
libpspdmac_a_LIBADD := $(DMAC_OBJS)

$(DMAC_OBJS): sceCtrl.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@
