PSPSDK = $(shell psp-config --pspsdk-path)
PSPLIBSDIR = $(PSPSDK)/..
TARGET = wlansample
OBJS = main.o
LIBS = -lpspwlan


CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

include $(PSPSDK)/lib/build.mak
