
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

CPPFLAGS = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel -I$(top_srcdir)/src/display -I$(top_srcdir)/src/ge -I$(top_srcdir)/src/user -I$(top_srcdir)/src/debug
CFLAGS =  @PSPSDK_CFLAGS@

libpspguincludedir = @PSPSDK_INCLUDEDIR@
libpspguinclude_HEADERS = pspgu.h

lib_LIBRARIES = libpspgu.a

noinst_HEADERS = 

libpspgu_a_SOURCES = \
	guInternal.c \
	sceGuGetMemory.c \
	sceGuInit.c \
	sceGuStart.c \
	sceGuTerm.c \
	vram.c

