
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

IO_OBJS = IoFileMgrForUser_0000.o IoFileMgrForUser_0001.o IoFileMgrForUser_0002.o IoFileMgrForUser_0003.o IoFileMgrForUser_0004.o IoFileMgrForUser_0005.o IoFileMgrForUser_0006.o IoFileMgrForUser_0007.o IoFileMgrForUser_0008.o IoFileMgrForUser_0009.o IoFileMgrForUser_0010.o IoFileMgrForUser_0011.o IoFileMgrForUser_0012.o IoFileMgrForUser_0013.o IoFileMgrForUser_0014.o IoFileMgrForUser_0015.o IoFileMgrForUser_0016.o IoFileMgrForUser_0017.o IoFileMgrForUser_0018.o IoFileMgrForUser_0019.o IoFileMgrForUser_0020.o IoFileMgrForUser_0021.o IoFileMgrForUser_0022.o IoFileMgrForUser_0023.o IoFileMgrForUser_0024.o IoFileMgrForUser_0025.o IoFileMgrForUser_0026.o IoFileMgrForUser_0027.o IoFileMgrForUser_0028.o IoFileMgrForUser_0029.o IoFileMgrForUser_0030.o IoFileMgrForUser_0031.o IoFileMgrForUser_0032.o IoFileMgrForUser_0033.o IoFileMgrForUser_0034.o IoFileMgrForUser_0035.o IoFileMgrForUser_0036.o 

KERNEL_OBJS = Kernel_Library_0000.o Kernel_Library_0001.o Kernel_Library_0002.o Kernel_Library_0003.o Kernel_Library_0004.o Kernel_Library_0005.o 

MODMGR_OBJS = ModuleMgrForUser_0000.o ModuleMgrForUser_0001.o ModuleMgrForUser_0002.o ModuleMgrForUser_0003.o ModuleMgrForUser_0004.o ModuleMgrForUser_0005.o ModuleMgrForUser_0006.o ModuleMgrForUser_0007.o ModuleMgrForUser_0008.o ModuleMgrForUser_0009.o ModuleMgrForUser_0010.o ModuleMgrForUser_0011.o

STDIO_OBJS = StdioForUser_0000.o StdioForUser_0001.o StdioForUser_0002.o StdioForUser_0003.o StdioForUser_0004.o StdioForUser_0005.o StdioForUser_0006.o StdioForUser_0007.o StdioForUser_0008.o StdioForUser_0009.o 

SUSPEND_OBJS = sceSuspendForUser_0000.o sceSuspendForUser_0001.o sceSuspendForUser_0002.o sceSuspendForUser_0003.o sceSuspendForUser_0004.o sceSuspendForUser_005.o sceSuspendForUser_0006.o

SYSMEM_OBJS = SysMemUserForUser_0000.o SysMemUserForUser_0001.o SysMemUserForUser_0002.o SysMemUserForUser_0003.o SysMemUserForUser_0004.o SysMemUserForUser_0005.o SysMemUserForUser_0006.o SysMemUserForUser_0007.o

THREADMAN_OBJS = ThreadManForUser_0000.o ThreadManForUser_0001.o ThreadManForUser_0002.o ThreadManForUser_0003.o ThreadManForUser_0004.o ThreadManForUser_0005.o ThreadManForUser_0006.o ThreadManForUser_0007.o ThreadManForUser_0008.o ThreadManForUser_0009.o ThreadManForUser_0010.o ThreadManForUser_0011.o ThreadManForUser_0012.o ThreadManForUser_0013.o ThreadManForUser_0014.o ThreadManForUser_0015.o ThreadManForUser_0016.o ThreadManForUser_0017.o ThreadManForUser_0018.o ThreadManForUser_0019.o ThreadManForUser_0020.o ThreadManForUser_0021.o ThreadManForUser_0022.o ThreadManForUser_0023.o ThreadManForUser_0024.o ThreadManForUser_0025.o ThreadManForUser_0026.o ThreadManForUser_0027.o ThreadManForUser_0028.o ThreadManForUser_0029.o ThreadManForUser_0030.o ThreadManForUser_0031.o ThreadManForUser_0032.o ThreadManForUser_0033.o ThreadManForUser_0034.o ThreadManForUser_0035.o ThreadManForUser_0036.o ThreadManForUser_0037.o ThreadManForUser_0038.o ThreadManForUser_0039.o ThreadManForUser_0040.o ThreadManForUser_0041.o ThreadManForUser_0042.o ThreadManForUser_0043.o ThreadManForUser_0044.o ThreadManForUser_0045.o ThreadManForUser_0046.o ThreadManForUser_0047.o ThreadManForUser_0048.o ThreadManForUser_0049.o ThreadManForUser_0050.o ThreadManForUser_0051.o ThreadManForUser_0052.o ThreadManForUser_0053.o ThreadManForUser_0054.o ThreadManForUser_0055.o ThreadManForUser_0056.o ThreadManForUser_0057.o ThreadManForUser_0058.o ThreadManForUser_0059.o ThreadManForUser_0060.o ThreadManForUser_0061.o ThreadManForUser_0062.o ThreadManForUser_0063.o ThreadManForUser_0064.o ThreadManForUser_0065.o ThreadManForUser_0066.o ThreadManForUser_0067.o ThreadManForUser_0068.o ThreadManForUser_0069.o ThreadManForUser_0070.o ThreadManForUser_0071.o ThreadManForUser_0072.o ThreadManForUser_0073.o ThreadManForUser_0074.o ThreadManForUser_0075.o ThreadManForUser_0076.o ThreadManForUser_0077.o ThreadManForUser_0078.o ThreadManForUser_0079.o ThreadManForUser_0080.o ThreadManForUser_0081.o ThreadManForUser_0082.o ThreadManForUser_0083.o ThreadManForUser_0084.o ThreadManForUser_0085.o ThreadManForUser_0086.o ThreadManForUser_0087.o ThreadManForUser_0088.o ThreadManForUser_0089.o ThreadManForUser_0090.o ThreadManForUser_0091.o ThreadManForUser_0092.o ThreadManForUser_0093.o ThreadManForUser_0094.o ThreadManForUser_0095.o ThreadManForUser_0096.o ThreadManForUser_0097.o ThreadManForUser_0098.o ThreadManForUser_0099.o ThreadManForUser_0100.o ThreadManForUser_0101.o ThreadManForUser_0102.o ThreadManForUser_0103.o ThreadManForUser_0104.o ThreadManForUser_0105.o ThreadManForUser_0106.o ThreadManForUser_0107.o ThreadManForUser_0108.o ThreadManForUser_0109.o ThreadManForUser_0110.o ThreadManForUser_0111.o ThreadManForUser_0112.o ThreadManForUser_0113.o ThreadManForUser_0114.o ThreadManForUser_0115.o ThreadManForUser_0116.o ThreadManForUser_0117.o ThreadManForUser_0118.o ThreadManForUser_0119.o ThreadManForUser_0120.o ThreadManForUser_0121.o ThreadManForUser_0122.o ThreadManForUser_0123.o ThreadManForUser_0124.o ThreadManForUser_0125.o ThreadManForUser_0126.o 

UTILS_OBJS = UtilsForUser_0000.o UtilsForUser_0001.o UtilsForUser_0002.o UtilsForUser_0003.o UtilsForUser_0004.o UtilsForUser_0005.o UtilsForUser_0006.o UtilsForUser_0007.o UtilsForUser_0008.o UtilsForUser_0009.o UtilsForUser_0010.o UtilsForUser_0011.o UtilsForUser_0012.o UtilsForUser_0013.o UtilsForUser_0014.o UtilsForUser_0015.o UtilsForUser_0016.o UtilsForUser_0017.o UtilsForUser_0018.o UtilsForUser_0019.o UtilsForUser_0020.o UtilsForUser_0021.o UtilsForUser_0022.o UtilsForUser_0023.o UtilsForUser_0024.o 

INTERRUPT_OBJS = InterruptManager_0000.o InterruptManager_0001.o InterruptManager_0002.o InterruptManager_0003.o InterruptManager_0004.o InterruptManager_0005.o InterruptManager_0006.o InterruptManager_0007.o InterruptManager_0008.o InterruptManager_0009.o 

LOADEXEC_OBJS = LoadExecForUser_0000.o LoadExecForUser_0001.o LoadExecForUser_0002.o LoadExecForUser_0003.o LoadExecForUser_0004.o 

IMPOSE_OBJS = sceImpose_0000.o sceImpose_0001.o sceImpose_0002.o sceImpose_0003.o sceImpose_0004.o sceImpose_0005.o sceImpose_0006.o sceImpose_0007.o sceImpose_0008.o sceImpose_0009.o sceImpose_0010.o sceImpose_0011.o sceImpose_0012.o sceImpose_0013.o sceImpose_0014.o sceImpose_0015.o 

libpspuserincludedir = @PSPSDK_INCLUDEDIR@
libpspuserinclude_HEADERS =	\
	pspiofilemgr.h		\
	pspiofilemgr_dirent.h	\
	pspiofilemgr_fcntl.h	\
	pspiofilemgr_stat.h	\
	pspkerneltypes.h	\
	pspkerror.h		\
	psploadexec.h		\
	pspmscm.h		\
	pspmoduleinfo.h		\
	pspmodulemgr.h		\
	pspsuspend.h    	\
	pspsysmem.h		\
	pspthreadman.h		\
	pspstdio.h		\
	pspuser.h		\
	psputils.h		\
	pspintrman.h		\
	pspmoduleexport.h

lib_LIBRARIES = libpspuser.a

libpspuser_a_SOURCES =	\
	IoFileMgrForUser.S	\
	InterruptManager.S	\
	Kernel_Library.S	\
	LoadExecForUser.S	\
	ModuleMgrForUser.S	\
	StdioForUser.S		\
	SysMemUserForUser.S	\
	ThreadManForUser.S	\
	UtilsForUser.S		\
	sceSuspendForUser.S	\
	pspintrman.c		\
	sceImpose.S

libpspuser_a_LIBADD = \
$(IO_OBJS) \
$(KERNEL_OBJS) \
$(MODMGR_OBJS) \
$(STDIO_OBJS) \
$(SUSPEND_OBJS) \
$(SYSMEM_OBJS) \
$(THREADMAN_OBJS) \
$(UTILS_OBJS) \
$(INTERRUPT_OBJS) \
$(LOADEXEC_OBJS) \
$(IMPOSE_OBJS)

$(IO_OBJS): IoFileMgrForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(KERNEL_OBJS): Kernel_Library.S
	$(COMPILE) -DF_$* $< -c -o $@

$(MODMGR_OBJS): ModuleMgrForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(STDIO_OBJS): StdioForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SUSPEND_OBJS): sceSuspendForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SYSMEM_OBJS): SysMemUserForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(THREADMAN_OBJS): ThreadManForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(UTILS_OBJS): UtilsForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(INTERRUPT_OBJS): InterruptManager.S
	$(COMPILE) -DF_$* $< -c -o $@

$(LOADEXEC_OBJS): LoadExecForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(IMPOSE_OBJS): sceImpose.S
	$(COMPILE) -DF_$* $< -c -o $@
