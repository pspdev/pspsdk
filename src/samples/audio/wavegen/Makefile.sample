TARGET = alsample
OBJS = main.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR = 
LDFLAGS = 
LIBS = -lpspaudiolib -lpspaudio -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Audiolib Wave Generator

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
