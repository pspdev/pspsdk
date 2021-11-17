TARGET = main
OBJS = main.o decrypt.o

INCDIR = 
CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -lpspchnnlsv
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP 
PSP_EBOOT_TITLE = Save Decrypt Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

main.c : decrypt.h
decrypt.c : decrypt.h
