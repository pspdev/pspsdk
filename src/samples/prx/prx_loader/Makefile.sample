TARGET = prxloader
OBJS = main.o MyLib.o

USE_PSPSDK_LIBC = 1

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS = 

LIBS = 

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Sample PRX Loader

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
