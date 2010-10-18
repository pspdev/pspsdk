
CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel -I$(top_srcdir)/src/user -I$(top_srcdir)/src/debug
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

## Borrow this trick from newlib - create a dummy library to generate build rules.
noinst_LIBRARIES = lib.a
lib_a_SOURCES = dummy.c

all: crt0.o crt0_prx.o prxexports.o

startupdir = @PSPDEV_LIBDIR@
pspsdkdir     = @PSPSDK_LIBDIR@

# Install the prx specific stuff in the pspsdk libdir
install-exec-hook:
	$(mkinstalldirs) $(DESTDIR)$(startupdir)
	$(INSTALL_DATA) crt0.o $(DESTDIR)$(startupdir)/crt0.o
	$(INSTALL_DATA) crt0_prx.o $(DESTDIR)$(startupdir)/crt0_prx.o
	$(INSTALL_DATA) prxexports.o $(DESTDIR)$(pspsdkdir)/prxexports.o


uninstall-hook:
	rm -f $(DESTDIR)$(startupdir)/crt0.o
	rm -f $(DESTDIR)$(startupdir)/crt0_prx.o
	rm -f $(DESTDIR)$(pspsdkdir)/prxexports.o

CLEANFILES = crt0.o crt0_prx.o prxexports.o 

## How else do I add a dependency for this?
EXTRA_DIST = crt0.c crt0_prx.c prxexports.c
