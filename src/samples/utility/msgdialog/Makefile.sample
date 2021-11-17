PSPSDK = $(shell psp-config --pspsdk-path)
PSPLIBSDIR = $(PSPSDK)/..
TARGET = msgdialogsample
OBJS = main.o
LIBS = -lpspgum -lpspgu

# Uncomment the following line to comple for custom firmware 3.xx
#BUILD_PRX = 1

CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

include $(PSPSDK)/lib/build.mak
