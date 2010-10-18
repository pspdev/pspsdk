
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base \
	   -I$(top_srcdir)/src/kernel \
	   -I$(top_srcdir)/src/display \
	   -I$(top_srcdir)/src/ge \
	   -I$(top_srcdir)/src/user \
	   -I$(top_srcdir)/src/ctrl 
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

SCRPRINT_OBJS = pspDebugScreenInit.o pspDebugScreenPrintf.o pspDebugScreenKprintf.o

libpspdebugincludedir = @PSPSDK_INCLUDEDIR@
libpspdebuginclude_HEADERS =	\
	pspdebug.h pspdebugkb.h

lib_LIBRARIES = libpspdebug.a libpspgdb.a libpspgdb_user.a libpspgdb_kernel.a libpspdebugkb.a

libpspdebug_a_SOURCES =		\
	callstack.c		\
	callstackget.S		\
	font.c			\
	scr_printf.c	\
	exception.c	\
	exception_asm.S \
	kprintf.c	\
	stacktrace.c	\
	profiler.c \
	stdio.c		\
	sio.c

libpspdebug_a_LIBADD = $(SCRPRINT_OBJS)

libpspgdb_a_SOURCES = gdb-stub.c

libpspgdb_user_a_SOURCES = gdb-userlib.c

libpspgdb_kernel_a_SOURCES = gdb-kernellib.c

libpspdebugkb_a_SOURCES = pspdebugkb.c

$(SCRPRINT_OBJS): scr_printf.c
	$(COMPILE) -DF_$* $< -c -o $@
