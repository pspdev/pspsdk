TARGET = idstorage
OBJS = main.o

CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBS = 

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Idstorage Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
