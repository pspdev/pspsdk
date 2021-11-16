TARGET = celshading
OBJS = lightmap.o celshading.o ../common/callbacks.o

INCDIR =
CFLAGS = -Wall -O2
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS= -lpspgum -lpspgu

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Celshading Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

lightmap.o : lightmap.raw
	bin2o -i lightmap.raw lightmap.o lightmap
