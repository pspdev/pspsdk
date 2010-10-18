TARGET = zbufferfog
OBJS = zbufferfog.o ../common/callbacks.o ../common/geometry.o ../common/vram.o

INCDIR =
CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS= -lpspgum -lpspgu -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Depth Buffer Fog Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
