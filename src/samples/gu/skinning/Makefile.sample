TARGET = skinning
OBJS = skinning.o

INCDIR =
CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lpspgum -lpspgu -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Matrix Skinning Sample

PSPSDK=$(shell psp-config --pspsdk-path)
USE_PSPSDK_LIBC=1
include $(PSPSDK)/lib/build.mak