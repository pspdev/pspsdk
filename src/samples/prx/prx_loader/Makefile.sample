TARGET = prxloader
OBJS = main.o MyLib.o

INCDIR = 
CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS = 

LIBS = 

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Sample PRX Loader

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
