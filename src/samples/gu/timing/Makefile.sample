TARGET = timing
OBJS = timing.o

INCDIR =
CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lpspgum -lpspgu -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Timing Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

