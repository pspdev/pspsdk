TARGET = vsync30FPS
OBJS = vsync30FPS.o ../common/callbacks.o

INCDIR =
CFLAGS = -Wall -O2
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS= -lpspgu

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = VSYNC 30FPS Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
