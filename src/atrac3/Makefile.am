
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel

ATRAC3_OBJS = sceAtrac3plus_0000.o sceAtrac3plus_0001.o sceAtrac3plus_0002.o sceAtrac3plus_0003.o sceAtrac3plus_0004.o sceAtrac3plus_0005.o sceAtrac3plus_0006.o sceAtrac3plus_0007.o sceAtrac3plus_0008.o sceAtrac3plus_0009.o sceAtrac3plus_0010.o sceAtrac3plus_0011.o sceAtrac3plus_0012.o sceAtrac3plus_0013.o sceAtrac3plus_0014.o sceAtrac3plus_0015.o sceAtrac3plus_0016.o sceAtrac3plus_0017.o sceAtrac3plus_0018.o sceAtrac3plus_0019.o sceAtrac3plus_0020.o sceAtrac3plus_0021.o sceAtrac3plus_0022.o sceAtrac3plus_0023.o sceAtrac3plus_0024.o sceAtrac3plus_0025.o 

libpspatrac3includedir = @PSPSDK_INCLUDEDIR@
libpspatrac3include_HEADERS = pspatrac3.h

lib_LIBRARIES = libpspatrac3.a 
libpspatrac3_a_SOURCES = sceAtrac3plus.S
libpspatrac3_a_LIBADD  = $(ATRAC3_OBJS)

$(ATRAC3_OBJS): sceAtrac3plus.S
	$(COMPILE) -DF_$* $< -c -o $@
