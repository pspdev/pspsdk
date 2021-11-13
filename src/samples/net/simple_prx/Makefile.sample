TARGET = netsample
OBJS = main.o

PRX_EXPORTS=exports.exp
BUILD_PRX=1

INCDIR = 
CFLAGS = -O0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
