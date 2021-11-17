TARGET = osk
OBJS = main.o

INCDIR =
CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1

LIBDIR =
LDFLAGS =
LIBS = -lpspgu

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PSP OSK Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
