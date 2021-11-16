TARGET = MIPMAPPING
OBJS = mipmapping.o mip0.o mip1.o mip2.o

INCDIR =
CFLAGS = -Wall -O2 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS = 

LIBS = -lpspgum -lpspgu

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = MIP Mapping Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

mip0.o: mip0.raw
	bin2o -i mip0.raw mip0.o mip0
mip1.o: mip1.raw
	bin2o -i mip1.raw mip1.o mip1
mip2.o: mip2.raw
	bin2o -i mip2.raw mip2.o mip2

