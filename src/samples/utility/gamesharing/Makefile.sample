TARGET = gamesharing
OBJS = main.o

PSP_FW_VERSION = 200
BUILD_PRX = 1

CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)


LIBDIR =
LDFLAGS =
LIBS = -lpspgum -lpspgu -lpspnet_adhoc -lpspnet_adhocctl -lpspnet_adhocmatching

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Game Sharing Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
