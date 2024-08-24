TARGET = gprofcustom
OBJS = main.o

INCDIR = 
CFLAGS = -O2 -Wall -pg -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS = -pg -g

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = GProf Custom Example

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
