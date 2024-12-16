TARGET = light_size
OBJS = main.o

INCDIR = 
CFLAGS = -Os -Wall -fdata-sections -ffunction-sections
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS = -s 

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Light Hello World

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
