PSPSDK = $(shell psp-config --pspsdk-path)
PSPLIBSDIR = $(PSPSDK)/..
TARGET = usbstorage
OBJS = main.o
LIBS = -lpspusb -lpspusbstor
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

include $(PSPSDK)/lib/build.mak
