PSPSDK = $(shell psp-config --pspsdk-path)
PSPLIBSDIR = $(PSPSDK)/..
TARGET = mp3sample
OBJS = main.o
LIBS = -lpspaudio -lpspmp3

BUILD_PRX = 1

CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Mp3 Sample

include $(PSPSDK)/lib/build.mak
