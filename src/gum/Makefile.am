
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel -I$(top_srcdir)/src/display \
	-I$(top_srcdir)/src/ge -I$(top_srcdir)/src/user -I$(top_srcdir)/src/vfpu
CFLAGS =  @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

libpspgumincludedir = @PSPSDK_INCLUDEDIR@
libpspguminclude_HEADERS = pspgum.h

lib_LIBRARIES = libpspgum.a libpspgum_vfpu.a

noinst_HEADERS = gumInternal.h

PSPGUM_SHARED_OBJS =  gumLoadMatrix.o gumOrtho.o gumPerspective.o \
                      gumLookAt.o gumRotateXYZ.o gumRotateZYX.o gumFullInverse.o \
                      gumCrossProduct.o gumDotProduct.o gumNormalize.o \
                      sceGumDrawArray.o sceGumDrawArrayN.o sceGumDrawBezier.o sceGumDrawSpline.o \
                      sceGumRotateXYZ.o sceGumRotateZYX.o

PSPGUM_FPU_OBJS =     sceGumLoadIdentity.o sceGumLoadMatrix.o sceGumMatrixMode.o \
                      sceGumMultMatrix.o sceGumOrtho.o sceGumPerspective.o sceGumPopMatrix.o \
                      sceGumPushMatrix.o sceGumScale.o sceGumTranslate.o sceGumUpdateMatrix.o \
                      sceGumStoreMatrix.o sceGumLookAt.o sceGumRotateX.o sceGumRotateY.o \
                      sceGumRotateZ.o sceGumFullInverse.o sceGumFastInverse.o sceGumBeginObject.o \
                      sceGumEndObject.o gumScale.o gumTranslate.o gumLoadIdentity.o gumFastInverse.o \
                      gumMultMatrix.o gumRotateX.o gumRotateY.o gumRotateZ.o gumInit.o

PSPGUM_VFPU_OBJS =    sceGumLoadIdentity_vfpu.o sceGumLoadMatrix_vfpu.o sceGumMatrixMode_vfpu.o \
                      sceGumMultMatrix_vfpu.o sceGumOrtho_vfpu.o sceGumPerspective_vfpu.o \
                      sceGumPopMatrix_vfpu.o sceGumPushMatrix_vfpu.o sceGumScale_vfpu.o \
                      sceGumTranslate_vfpu.o sceGumUpdateMatrix_vfpu.o sceGumStoreMatrix_vfpu.o \
                      sceGumLookAt_vfpu.o sceGumRotateX_vfpu.o sceGumRotateY_vfpu.o \
                      sceGumRotateZ_vfpu.o sceGumFullInverse_vfpu.o sceGumFastInverse_vfpu.o \
                      sceGumBeginObject_vfpu.o sceGumEndObject_vfpu.o gumScale_vfpu.o \
                      gumTranslate_vfpu.o gumLoadIdentity_vfpu.o gumFastInverse_vfpu.o \
                      gumMultMatrix_vfpu.o gumRotateX_vfpu.o gumRotateY_vfpu.o gumRotateZ_vfpu.o \
		      gumInit_vfpu.o

libpspgum_a_SOURCES = gumInternal.c pspgum.c
libpspgum_a_LIBADD = $(PSPGUM_FPU_OBJS) $(PSPGUM_SHARED_OBJS)

libpspgum_vfpu_a_SOURCES = gumInternal.c pspgum.c pspgum_vfpu.c
libpspgum_vfpu_a_LIBADD = $(PSPGUM_VFPU_OBJS) $(PSPGUM_SHARED_OBJS)

$(PSPGUM_SHARED_OBJS): pspgum.c
	$(COMPILE) -DF_$* $< -c -o $@

$(PSPGUM_FPU_OBJS): pspgum.c
	$(COMPILE) -DF_$* $< -c -o $@

$(PSPGUM_VFPU_OBJS): pspgum_vfpu.c
	$(COMPILE) -DF_$* $< -c -o $@
