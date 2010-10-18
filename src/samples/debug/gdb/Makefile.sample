TARGET = gdb
OBJS = main.o 

USE_PSPSDK_LIBC = 1

INCDIR = 
CFLAGS = -O0 -G0 -Wall -ggdb
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBS = -lpspgdb -lpspgdb_user
LIBDIR =
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = GDB

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

LIBS += -lpsphprm_driver
