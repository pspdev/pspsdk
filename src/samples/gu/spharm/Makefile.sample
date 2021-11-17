TARGET = spharm
OBJS = cube.o spharm.o disablefpu.o mt19937.o logo.o logo2.o logo3.o

INCDIR =
CFLAGS = -Wall -fno-exceptions
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS= -lpspgum -lpspgu

EXTRA_TARGETS = convlogo EBOOT.PBP
PSP_EBOOT_TITLE = adresd - spharm v1.0

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

convlogo:
	bin2o -i logo.raw logo.o logo
	bin2o -i Image1.raw logo2.o logo2
	bin2o -i Image2.raw logo3.o logo3

copyms:
	cp -f EBOOT.PBP /cygdrive/I/PSP/GAME/SPHARM
