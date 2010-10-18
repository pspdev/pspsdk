TARGET = shadowprojection
OBJS = shadowprojection.o

INCDIR =
CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lpspgum -lpspgu -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Shadow Projection Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
