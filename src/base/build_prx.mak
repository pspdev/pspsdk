# PSP Software Development Kit - https://github.com/pspdev
# -----------------------------------------------------------------------
# Licensed under the BSD license, see LICENSE in PSPSDK root for details.
#
# build.mak - Base makefile for projects using PSPSDK.
#
# Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
# Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
# Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
#

# Note: The PSPSDK make variable must be defined before this file is included.
ifeq ($(PSPSDK),)
$(error $$(PSPSDK) is undefined.  Use "PSPSDK := $$(shell psp-config --pspsdk-path)" in your Makefile)
endif

CC       = psp-gcc
CXX      = psp-g++
AS       = psp-gcc
LD       = psp-gcc
STRIP    = psp-strip
FIXUP    = psp-fixup-imports

# Add PSPSDK includes and libraries.
INCDIR   := $(INCDIR) . $(PSPDEV)/psp/include $(PSPSDK)/include
LIBDIR   := $(LIBDIR) . $(PSPDEV)/psp/lib $(PSPSDK)/lib

CFLAGS   := $(addprefix -I,$(INCDIR)) $(CFLAGS)
CXXFLAGS := $(CFLAGS) $(CXXFLAGS)
ASFLAGS  := $(CFLAGS) $(ASFLAGS)

LDFLAGS  := $(addprefix -L,$(LIBDIR)) -Wl,-q,-T$(PSPSDK)/lib/linkfile.prx -nostartfiles -Wl,-zmax-page-size=128 $(LDFLAGS)

ifeq ($(USE_KERNEL_LIBS),1)
LIBS := -nostdlib $(LIBS) -lpspdebug -lpspdisplay_driver -lpspctrl_driver -lpspmodinfo -lpspsdk -lpspkernel
else 
LIBS := $(LIBS) -lpspdebug -lpspdisplay -lpspge -lpspctrl
endif

ifeq ($(PSP_FW_VERSION),)
PSP_FW_VERSION=600
endif

CFLAGS += -D_PSP_FW_VERSION=$(PSP_FW_VERSION)

FINAL_TARGET = $(TARGET).prx

all: $(FINAL_TARGET)
ifeq ($(NO_FIXUP_IMPORTS), 1)
$(TARGET).elf: $(OBJS)
	$(LINK.c) $^ $(LIBS) -o $@
else
$(TARGET).elf: $(OBJS)
	$(LINK.c) $^ $(LIBS) -o $@
	$(FIXUP) $@
endif

%.prx: %.elf
	$(STRIP) --strip-unneeded --keep-section=.rodata.sce* --keep-section=.sceStub.text --keep-section=.lib.ent* --keep-section=.lib.stub* --keep-section=.symtab --keep-section=.strtab --keep-section=.dynsym --keep-section=.dynstr --keep-section=.hash --keep-section=.dynamic --keep-section=.got --keep-section=.plt --keep-section=.rel* $< -o $(TARGET)_stripped.elf
	psp-prxgen $(TARGET)_stripped.elf $@
	-rm -f $(TARGET)_stripped.elf

%.c: %.exp
	psp-build-exports -b $< > $@

clean: $(EXTRA_CLEAN)
	-rm -f $(FINAL_TARGET) $(TARGET).elf $(OBJS)

rebuild: clean all
