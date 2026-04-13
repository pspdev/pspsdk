
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

CPPFLAGS = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/user -I$(top_srcdir)/src/debug
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS)

SASCORE_OBJS = sceSasCore_0000.o __sceSasInit_0001.o __sceSasCore_0002.o \
	__sceSasCoreWithMix_0003.o __sceSasGetEndFlag_0004.o \
	__sceSasSetVolume_0005.o __sceSasSetPitch_0006.o \
	__sceSasSetVoice_0007.o __sceSasSetNoise_0008.o \
	__sceSasSetADSR_0009.o __sceSasSetADSRmode_0010.o \
	__sceSasSetSL_0011.o __sceSasGetEnvelopeHeight_0012.o \
	__sceSasSetSimpleADSR_0013.o __sceSasSetKeyOff_0014.o \
	__sceSasSetKeyOn_0015.o __sceSasRevVON_0016.o \
	__sceSasRevEVOL_0017.o __sceSasRevType_0018.o \
	__sceSasRevParam_0019.o __sceSasGetPauseFlag_0020.o \
	__sceSasSetPause_0021.o __sceSasSetTrianglarWave_0022.o \
	__sceSasSetSteepWave_0023.o __sceSasGetGrain_0024.o \
	__sceSasSetGrain_0025.o __sceSasGetOutputmode_0026.o \
	__sceSasSetOutputmode_0027.o __sceSasGetAllEnvelopeHeights_0028.o \
	__sceSasSetVoicePCM_0029.o __sceSasSetVoiceATRAC3_0030.o \
	__sceSasConcatenateATRAC3_0031.o __sceSasUnsetATRAC3_0032.o

libpspsascoreincludedir = @PSPSDK_INCLUDEDIR@
libpspsascoreinclude_HEADERS = pspsascore.h

lib_LIBRARIES = libpspsascore.a

libpspsascore_a_SOURCES = sceSasCore.S
libpspsascore_a_LIBADD = $(SASCORE_OBJS)

$(SASCORE_OBJS): sceSasCore.S
	$(AM_V_CPPAS)$(CPPASCOMPILE) -DF_$* $< -c -o $@
