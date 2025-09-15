
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

CPPFLAGS = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS)

KERMIT_DRIVER_OBJS = sceKermit_driver_0000.o sceKermit_driver_0001.o sceKermit_driver_0002.o sceKermit_driver_0003.o sceKermit_driver_0004.o sceKermit_driver_0005.o

KERMIT_FLASHFS_DRIVER_OBJS = sceKermitFlashfs_driver_0000.o sceKermitFlashfs_driver_0001.o 

KERMIT_MSFS_DRIVER_OBJS = sceKermitMsfs_driver_0000.o sceKermitMsfs_driver_0001.o sceKermitMsfs_driver_0002.o sceKermitMsfs_driver_0003.o sceKermitMsfs_driver_0004.o sceKermitMsfs_driver_0005.o sceKermitMsfs_driver_0006.o

KERMIT_MEMORY_DRIVER_OBJS = sceKermitMemory_driver_0000.o sceKermitMemory_driver_0001.o sceKermitMemory_driver_0002.o sceKermitMemory_driver_0003.o

KERMIT_PERIPHERAL_OBJS = sceKermitPeripheral_0000.o sceKermitPeripheral_0001.o sceKermitPeripheral_0002.o sceKermitPeripheral_0003.o

KERMIT_PERIPHERAL_DRIVER_OBJS = sceKermitPeripheral_driver_0000.o sceKermitPeripheral_driver_0001.o sceKermitPeripheral_driver_0002.o sceKermitPeripheral_driver_0003.o sceKermitPeripheral_driver_0004.o sceKermitPeripheral_driver_0005.o sceKermitPeripheral_driver_0006.o sceKermitPeripheral_driver_0007.o sceKermitPeripheral_driver_0008.o sceKermitPeripheral_driver_0009.o sceKermitPeripheral_driver_0010.o sceKermitPeripheral_driver_0011.o sceKermitPeripheral_driver_0012.o sceKermitPeripheral_driver_0013.o sceKermitPeripheral_driver_0014.o sceKermitPeripheral_driver_0015.o sceKermitPeripheral_driver_0016.o sceKermitPeripheral_driver_0017.o sceKermitPeripheral_driver_0018.o

kermitincludedir = @PSPSDK_INCLUDEDIR@
kermitinclude_HEADERS = pspkermit.h

lib_LIBRARIES = libpspkermit_driver.a libpspkermitflashfs_driver.a libpspkermitmsfs_driver.a libpspkermitmemory_driver.a libpspkermitperipheral.a libpspkermitperipheral_driver.a
libpspkermit_driver_a_SOURCES = sceKermit_driver.S
libpspkermit_driver_a_LIBADD  = $(KERMIT_DRIVER_OBJS)
libpspkermitflashfs_driver_a_SOURCES = sceKermitFlashfs_driver.S
libpspkermitflashfs_driver_a_LIBADD  = $(KERMIT_FALSHFS_DRIVER_OBJS)
libpspkermitmsfs_driver_a_SOURCES = sceKermitMsfs_driver.S
libpspkermitmsfs_driver_a_LIBADD  = $(KERMIT_MSFS_DRIVER_OBJS)
libpspkermitmemory_driver_a_SOURCES = sceKermitMemory_driver.S
libpspkermitmemory_driver_a_LIBADD  = $(KERMIT_MEMORY_DRIVER_OBJS)
libpspkermitperipheral_a_SOURCES = sceKermitPeripheral.S
libpspkermitperipheral_a_LIBADD  = $(KERMIT_PERIPHERAL_OBJS)
libpspkermitperipheral_driver_a_SOURCES = sceKermitPeripheral_driver.S
libpspkermitperipheral_driver_a_LIBADD  = $(KERMIT_PERIPHERAL_DRIVER_OBJS)

$(KERMIT_DRIVER_OBJS): sceKermit_driver.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@

$(KERMIT_FLASHFS_DRIVER_OBJS): sceKermitFlashfs_driver.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@

$(KERMIT_MSFS_DRIVER_OBJS): sceKermitMsfs_driver.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@

$(KERMIT_MEMORY_DRIVER_OBJS): sceKermitMemory_driver.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@

$(KERMIT_PERIPHERAL_OBJS): sceKermitPeripheral.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@

$(KERMIT_PERIPHERAL_DRIVER_OBJS): sceKermitPeripheral_driver.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@
