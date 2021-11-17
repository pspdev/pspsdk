TARGET = main
OBJS = main.o encrypt.o hash.o psf.o

INCDIR = 
CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -lpspchnnlsv
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP 
PSP_EBOOT_TITLE = Save Encrypt Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

main.c : encrypt.h
encrypt.c : encrypt.h hash.h
hash.c : hash.h psf.h
psf.c : psf.h

