
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel -I$(top_srcdir)/src/display -I$(top_srcdir)/src/ge -I$(top_srcdir)/src/user -I$(top_srcdir)/src/debug
CFLAGS =  @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

libpspguincludedir = @PSPSDK_INCLUDEDIR@
libpspguinclude_HEADERS = pspgu.h

lib_LIBRARIES = libpspgu.a

noinst_HEADERS = guInternal.h

libpspgu_a_SOURCES = callbackFin.c callbackSig.c guInternal.c resetValues.c sceGuAlphaFunc.c sceGuAmbient.c \
	sceGuAmbientColor.c sceGuBeginObject.c sceGuBlendFunc.c sceGuBoneMatrix.c sceGuBreak.c sceGuCallList.c \
	sceGuCallMode.c sceGuCheckList.c sceGuClear.c sceGuClearColor.c sceGuClearDepth.c sceGuClearStencil.c \
	sceGuClutLoad.c sceGuClutMode.c sceGuColor.c sceGuColorFunc.c sceGuColorMaterial.c sceGuContinue.c \
	sceGuCopyImage.c sceGuDepthBuffer.c sceGuDepthFunc.c sceGuDepthMask.c sceGuDepthOffset.c \
	sceGuDepthRange.c sceGuDisable.c sceGuDispBuffer.c sceGuDisplay.c sceGuDrawArray.c sceGuDrawArrayN.c \
	sceGuDrawBezier.c sceGuDrawBuffer.c sceGuDrawBufferList.c sceGuDrawSpline.c sceGuEnable.c sceGuEndObject.c \
	sceGuFinish.c sceGuFog.c sceGuFrontFace.c sceGuGetAllStatus.c sceGuGetMemory.c sceGuGetStatus.c sceGuInit.c \
	sceGuLight.c sceGuLightAtt.c sceGuLightColor.c sceGuLightMode.c sceGuLightSpot.c sceGuLogicalOp.c \
	sceGuMaterial.c sceGuModelColor.c sceGuMorphWeight.c sceGuOffset.c sceGuPatchDivide.c sceGuPatchFrontFace.c \
	sceGuPatchPrim.c sceGuPixelMask.c sceGuScissor.c sceGuSendCommandf.c sceGuSendCommandi.c sceGuSendList.c \
	sceGuSetAllStatus.c sceGuSetCallback.c sceGuSetDither.c sceGuSetMatrix.c sceGuSetStatus.c sceGuShadeModel.c \
	sceGuSignal.c sceGuSpecular.c sceGuStart.c sceGuStencilFunc.c sceGuStencilOp.c \
	sceGuSwapBuffers.c sceGuSync.c sceGuTerm.c sceGuTexEnvColor.c sceGuTexFilter.c sceGuTexFlush.c sceGuTexFunc.c \
	sceGuTexImage.c sceGuTexLevelMode.c sceGuTexMapMode.c sceGuTexMode.c sceGuTexOffset.c sceGuTexProjMapMode.c \
	sceGuTexScale.c sceGuTexSlope.c sceGuTexSync.c sceGuTexWrap.c sceGuViewport.c sendCommand.c

