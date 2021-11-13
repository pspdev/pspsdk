TARGET = savedata
OBJS = main.o

# For custom firmware uncomment the following lines:
#PSP_FW_VERSION = 200
#BUILD_PRX = 1

LIBS = -lpspgum -lpspgu

CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PSPSDK Savedata Sample

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
