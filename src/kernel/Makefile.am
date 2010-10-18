
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/user
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

EXCEPTION_OBJS = ExceptionManagerForKernel_0000.o ExceptionManagerForKernel_0001.o ExceptionManagerForKernel_0002.o ExceptionManagerForKernel_0003.o ExceptionManagerForKernel_0004.o ExceptionManagerForKernel_0005.o ExceptionManagerForKernel_0006.o ExceptionManagerForKernel_0007.o ExceptionManagerForKernel_0008.o 

KDEBUG_OBJS = KDebugForKernel_0000.o KDebugForKernel_0001.o KDebugForKernel_0002.o KDebugForKernel_0003.o KDebugForKernel_0004.o KDebugForKernel_0005.o KDebugForKernel_0006.o KDebugForKernel_0007.o KDebugForKernel_0008.o KDebugForKernel_0009.o KDebugForKernel_0010.o KDebugForKernel_0011.o KDebugForKernel_0012.o KDebugForKernel_0013.o KDebugForKernel_0014.o KDebugForKernel_0015.o KDebugForKernel_0016.o KDebugForKernel_0017.o KDebugForKernel_0018.o KDebugForKernel_0019.o KDebugForKernel_0020.o 

LOADCORE_OBJS = LoadCoreForKernel_0000.o LoadCoreForKernel_0001.o LoadCoreForKernel_0002.o LoadCoreForKernel_0003.o LoadCoreForKernel_0004.o LoadCoreForKernel_0005.o LoadCoreForKernel_0006.o LoadCoreForKernel_0007.o LoadCoreForKernel_0008.o LoadCoreForKernel_0009.o LoadCoreForKernel_0010.o LoadCoreForKernel_0011.o LoadCoreForKernel_0012.o LoadCoreForKernel_0013.o LoadCoreForKernel_0014.o LoadCoreForKernel_0015.o LoadCoreForKernel_0016.o LoadCoreForKernel_0017.o LoadCoreForKernel_0018.o LoadCoreForKernel_0019.o LoadCoreForKernel_0020.o LoadCoreForKernel_0021.o LoadCoreForKernel_0022.o LoadCoreForKernel_0023.o LoadCoreForKernel_0024.o LoadCoreForKernel_0025.o LoadCoreForKernel_0026.o LoadCoreForKernel_0027.o LoadCoreForKernel_0028.o LoadCoreForKernel_0029.o LoadCoreForKernel_0030.o 

IO_OBJS = IoFileMgrForKernel_0000.o IoFileMgrForKernel_0001.o IoFileMgrForKernel_0002.o IoFileMgrForKernel_0003.o IoFileMgrForKernel_0004.o IoFileMgrForKernel_0005.o IoFileMgrForKernel_0006.o IoFileMgrForKernel_0007.o IoFileMgrForKernel_0008.o IoFileMgrForKernel_0009.o IoFileMgrForKernel_0010.o IoFileMgrForKernel_0011.o IoFileMgrForKernel_0012.o IoFileMgrForKernel_0013.o IoFileMgrForKernel_0014.o IoFileMgrForKernel_0015.o IoFileMgrForKernel_0016.o IoFileMgrForKernel_0017.o IoFileMgrForKernel_0018.o IoFileMgrForKernel_0019.o IoFileMgrForKernel_0020.o IoFileMgrForKernel_0021.o IoFileMgrForKernel_0022.o IoFileMgrForKernel_0023.o IoFileMgrForKernel_0024.o IoFileMgrForKernel_0025.o IoFileMgrForKernel_0026.o IoFileMgrForKernel_0027.o IoFileMgrForKernel_0028.o IoFileMgrForKernel_0029.o IoFileMgrForKernel_0030.o IoFileMgrForKernel_0031.o IoFileMgrForKernel_0032.o IoFileMgrForKernel_0033.o IoFileMgrForKernel_0034.o IoFileMgrForKernel_0035.o IoFileMgrForKernel_0036.o IoFileMgrForKernel_0037.o IoFileMgrForKernel_0038.o IoFileMgrForKernel_0039.o IoFileMgrForKernel_0040.o IoFileMgrForKernel_0041.o IoFileMgrForKernel_0042.o 

STDIO_OBJS = StdioForKernel_0000.o StdioForKernel_0001.o StdioForKernel_0002.o StdioForKernel_0003.o StdioForKernel_0004.o StdioForKernel_0005.o StdioForKernel_0006.o StdioForKernel_0007.o StdioForKernel_0008.o StdioForKernel_0009.o StdioForKernel_0010.o StdioForKernel_0011.o StdioForKernel_0012.o StdioForKernel_0013.o StdioForKernel_0014.o StdioForKernel_0015.o 

SYSREG_OBJS = sceSysreg_driver_0000.o sceSysreg_driver_0001.o sceSysreg_driver_0002.o sceSysreg_driver_0003.o sceSysreg_driver_0004.o sceSysreg_driver_0005.o sceSysreg_driver_0006.o sceSysreg_driver_0007.o sceSysreg_driver_0008.o sceSysreg_driver_0009.o sceSysreg_driver_0010.o sceSysreg_driver_0011.o sceSysreg_driver_0012.o sceSysreg_driver_0013.o sceSysreg_driver_0014.o sceSysreg_driver_0015.o sceSysreg_driver_0016.o sceSysreg_driver_0017.o sceSysreg_driver_0018.o sceSysreg_driver_0019.o sceSysreg_driver_0020.o sceSysreg_driver_0021.o sceSysreg_driver_0022.o sceSysreg_driver_0023.o sceSysreg_driver_0024.o sceSysreg_driver_0025.o sceSysreg_driver_0026.o sceSysreg_driver_0027.o sceSysreg_driver_0028.o sceSysreg_driver_0029.o sceSysreg_driver_0030.o sceSysreg_driver_0031.o sceSysreg_driver_0032.o sceSysreg_driver_0033.o sceSysreg_driver_0034.o sceSysreg_driver_0035.o sceSysreg_driver_0036.o sceSysreg_driver_0037.o sceSysreg_driver_0038.o sceSysreg_driver_0039.o sceSysreg_driver_0040.o sceSysreg_driver_0041.o sceSysreg_driver_0042.o sceSysreg_driver_0043.o sceSysreg_driver_0044.o sceSysreg_driver_0045.o sceSysreg_driver_0046.o sceSysreg_driver_0047.o sceSysreg_driver_0048.o sceSysreg_driver_0049.o sceSysreg_driver_0050.o sceSysreg_driver_0051.o sceSysreg_driver_0052.o sceSysreg_driver_0053.o sceSysreg_driver_0054.o sceSysreg_driver_0055.o sceSysreg_driver_0056.o sceSysreg_driver_0057.o sceSysreg_driver_0058.o sceSysreg_driver_0059.o sceSysreg_driver_0060.o sceSysreg_driver_0061.o sceSysreg_driver_0062.o sceSysreg_driver_0063.o sceSysreg_driver_0064.o sceSysreg_driver_0065.o sceSysreg_driver_0066.o sceSysreg_driver_0067.o sceSysreg_driver_0068.o sceSysreg_driver_0069.o sceSysreg_driver_0070.o sceSysreg_driver_0071.o sceSysreg_driver_0072.o sceSysreg_driver_0073.o sceSysreg_driver_0074.o sceSysreg_driver_0075.o sceSysreg_driver_0076.o sceSysreg_driver_0077.o sceSysreg_driver_0078.o sceSysreg_driver_0079.o sceSysreg_driver_0080.o sceSysreg_driver_0081.o sceSysreg_driver_0082.o sceSysreg_driver_0083.o sceSysreg_driver_0084.o sceSysreg_driver_0085.o sceSysreg_driver_0086.o sceSysreg_driver_0087.o sceSysreg_driver_0088.o sceSysreg_driver_0089.o sceSysreg_driver_0090.o sceSysreg_driver_0091.o sceSysreg_driver_0092.o sceSysreg_driver_0093.o sceSysreg_driver_0094.o sceSysreg_driver_0095.o sceSysreg_driver_0096.o sceSysreg_driver_0097.o sceSysreg_driver_0098.o sceSysreg_driver_0099.o sceSysreg_driver_0100.o sceSysreg_driver_0101.o sceSysreg_driver_0102.o sceSysreg_driver_0103.o sceSysreg_driver_0104.o sceSysreg_driver_0105.o sceSysreg_driver_0106.o sceSysreg_driver_0107.o sceSysreg_driver_0108.o sceSysreg_driver_0109.o sceSysreg_driver_0110.o sceSysreg_driver_0111.o sceSysreg_driver_0112.o sceSysreg_driver_0113.o sceSysreg_driver_0114.o sceSysreg_driver_0115.o sceSysreg_driver_0116.o sceSysreg_driver_0117.o sceSysreg_driver_0118.o sceSysreg_driver_0119.o sceSysreg_driver_0120.o sceSysreg_driver_0121.o sceSysreg_driver_0122.o sceSysreg_driver_0123.o sceSysreg_driver_0124.o sceSysreg_driver_0125.o sceSysreg_driver_0126.o sceSysreg_driver_0127.o sceSysreg_driver_0128.o sceSysreg_driver_0129.o sceSysreg_driver_0130.o sceSysreg_driver_0131.o sceSysreg_driver_0132.o sceSysreg_driver_0133.o sceSysreg_driver_0134.o sceSysreg_driver_0135.o sceSysreg_driver_0136.o sceSysreg_driver_0137.o sceSysreg_driver_0138.o sceSysreg_driver_0139.o sceSysreg_driver_0140.o sceSysreg_driver_0141.o sceSysreg_driver_0142.o sceSysreg_driver_0143.o sceSysreg_driver_0144.o sceSysreg_driver_0145.o sceSysreg_driver_0146.o sceSysreg_driver_0147.o sceSysreg_driver_0148.o sceSysreg_driver_0149.o sceSysreg_driver_0150.o sceSysreg_driver_0151.o 

UTILS_OBJS = UtilsForKernel_0000.o UtilsForKernel_0001.o UtilsForKernel_0002.o UtilsForKernel_0003.o UtilsForKernel_0004.o UtilsForKernel_0005.o UtilsForKernel_0006.o UtilsForKernel_0007.o UtilsForKernel_0008.o UtilsForKernel_0009.o UtilsForKernel_0010.o UtilsForKernel_0011.o UtilsForKernel_0012.o UtilsForKernel_0013.o UtilsForKernel_0014.o UtilsForKernel_0015.o UtilsForKernel_0016.o UtilsForKernel_0017.o UtilsForKernel_0018.o UtilsForKernel_0019.o UtilsForKernel_0020.o UtilsForKernel_0021.o UtilsForKernel_0022.o UtilsForKernel_0023.o UtilsForKernel_0024.o UtilsForKernel_0025.o UtilsForKernel_0026.o UtilsForKernel_0027.o UtilsForKernel_0028.o UtilsForKernel_0029.o UtilsForKernel_0030.o UtilsForKernel_0031.o UtilsForKernel_0032.o UtilsForKernel_0033.o UtilsForKernel_0034.o UtilsForKernel_0035.o UtilsForKernel_0036.o UtilsForKernel_0037.o UtilsForKernel_0038.o UtilsForKernel_0039.o 

SYSCON_OBJS = sceSyscon_driver_0000.o sceSyscon_driver_0001.o sceSyscon_driver_0002.o sceSyscon_driver_0003.o sceSyscon_driver_0004.o sceSyscon_driver_0005.o sceSyscon_driver_0006.o sceSyscon_driver_0007.o sceSyscon_driver_0008.o sceSyscon_driver_0009.o sceSyscon_driver_0010.o sceSyscon_driver_0011.o sceSyscon_driver_0012.o sceSyscon_driver_0013.o sceSyscon_driver_0014.o sceSyscon_driver_0015.o sceSyscon_driver_0016.o sceSyscon_driver_0017.o sceSyscon_driver_0018.o sceSyscon_driver_0019.o sceSyscon_driver_0020.o sceSyscon_driver_0021.o sceSyscon_driver_0022.o sceSyscon_driver_0023.o sceSyscon_driver_0024.o sceSyscon_driver_0025.o sceSyscon_driver_0026.o sceSyscon_driver_0027.o sceSyscon_driver_0028.o sceSyscon_driver_0029.o sceSyscon_driver_0030.o sceSyscon_driver_0031.o sceSyscon_driver_0032.o sceSyscon_driver_0033.o sceSyscon_driver_0034.o sceSyscon_driver_0035.o sceSyscon_driver_0036.o sceSyscon_driver_0037.o sceSyscon_driver_0038.o sceSyscon_driver_0039.o sceSyscon_driver_0040.o sceSyscon_driver_0041.o sceSyscon_driver_0042.o sceSyscon_driver_0043.o sceSyscon_driver_0044.o sceSyscon_driver_0045.o sceSyscon_driver_0046.o sceSyscon_driver_0047.o sceSyscon_driver_0048.o sceSyscon_driver_0049.o sceSyscon_driver_0050.o sceSyscon_driver_0051.o sceSyscon_driver_0052.o sceSyscon_driver_0053.o sceSyscon_driver_0054.o sceSyscon_driver_0055.o sceSyscon_driver_0056.o sceSyscon_driver_0057.o sceSyscon_driver_0058.o sceSyscon_driver_0059.o sceSyscon_driver_0060.o sceSyscon_driver_0061.o sceSyscon_driver_0062.o sceSyscon_driver_0063.o sceSyscon_driver_0064.o sceSyscon_driver_0065.o sceSyscon_driver_0066.o sceSyscon_driver_0067.o sceSyscon_driver_0068.o sceSyscon_driver_0069.o sceSyscon_driver_0070.o sceSyscon_driver_0071.o sceSyscon_driver_0072.o sceSyscon_driver_0073.o sceSyscon_driver_0074.o sceSyscon_driver_0075.o sceSyscon_driver_0076.o sceSyscon_driver_0077.o sceSyscon_driver_0078.o sceSyscon_driver_0079.o sceSyscon_driver_0080.o sceSyscon_driver_0081.o sceSyscon_driver_0082.o sceSyscon_driver_0083.o sceSyscon_driver_0084.o sceSyscon_driver_0085.o sceSyscon_driver_0086.o sceSyscon_driver_0087.o sceSyscon_driver_0088.o sceSyscon_driver_0089.o sceSyscon_driver_0090.o sceSyscon_driver_0091.o sceSyscon_driver_0092.o sceSyscon_driver_0093.o sceSyscon_driver_0094.o sceSyscon_driver_0095.o sceSyscon_driver_0096.o sceSyscon_driver_0097.o sceSyscon_driver_0098.o sceSyscon_driver_0099.o sceSyscon_driver_0100.o sceSyscon_driver_0101.o sceSyscon_driver_0102.o sceSyscon_driver_0103.o sceSyscon_driver_0104.o sceSyscon_driver_0105.o sceSyscon_driver_0106.o sceSyscon_driver_0107.o sceSyscon_driver_0108.o sceSyscon_driver_0109.o sceSyscon_driver_0110.o sceSyscon_driver_0111.o sceSyscon_driver_0112.o sceSyscon_driver_0113.o 

INTR_OBJS = InterruptManagerForKernel_0000.o InterruptManagerForKernel_0001.o InterruptManagerForKernel_0002.o InterruptManagerForKernel_0003.o InterruptManagerForKernel_0004.o InterruptManagerForKernel_0005.o InterruptManagerForKernel_0006.o InterruptManagerForKernel_0007.o InterruptManagerForKernel_0008.o InterruptManagerForKernel_0009.o InterruptManagerForKernel_0010.o InterruptManagerForKernel_0011.o InterruptManagerForKernel_0012.o InterruptManagerForKernel_0013.o InterruptManagerForKernel_0014.o InterruptManagerForKernel_0015.o InterruptManagerForKernel_0016.o InterruptManagerForKernel_0017.o InterruptManagerForKernel_0018.o InterruptManagerForKernel_0019.o InterruptManagerForKernel_0020.o InterruptManagerForKernel_0021.o InterruptManagerForKernel_0022.o InterruptManagerForKernel_0023.o InterruptManagerForKernel_0024.o InterruptManagerForKernel_0025.o InterruptManagerForKernel_0026.o InterruptManagerForKernel_0027.o InterruptManagerForKernel_0028.o InterruptManagerForKernel_0029.o InterruptManagerForKernel_0030.o InterruptManagerForKernel_0031.o InterruptManagerForKernel_0032.o InterruptManagerForKernel_0033.o InterruptManagerForKernel_0034.o InterruptManagerForKernel_0035.o InterruptManagerForKernel_0036.o InterruptManagerForKernel_0037.o InterruptManagerForKernel_0038.o InterruptManagerForKernel_0039.o InterruptManagerForKernel_0040.o InterruptManagerForKernel_0041.o InterruptManagerForKernel_0042.o InterruptManagerForKernel_0043.o InterruptManagerForKernel_0044.o 

THREAD_OBJS = ThreadManForKernel_0000.o ThreadManForKernel_0001.o ThreadManForKernel_0002.o ThreadManForKernel_0003.o ThreadManForKernel_0004.o ThreadManForKernel_0005.o ThreadManForKernel_0006.o ThreadManForKernel_0007.o ThreadManForKernel_0008.o ThreadManForKernel_0009.o ThreadManForKernel_0010.o ThreadManForKernel_0011.o ThreadManForKernel_0012.o ThreadManForKernel_0013.o ThreadManForKernel_0014.o ThreadManForKernel_0015.o ThreadManForKernel_0016.o ThreadManForKernel_0017.o ThreadManForKernel_0018.o ThreadManForKernel_0019.o ThreadManForKernel_0020.o ThreadManForKernel_0021.o ThreadManForKernel_0022.o ThreadManForKernel_0023.o ThreadManForKernel_0024.o ThreadManForKernel_0025.o ThreadManForKernel_0026.o ThreadManForKernel_0027.o ThreadManForKernel_0028.o ThreadManForKernel_0029.o ThreadManForKernel_0030.o ThreadManForKernel_0031.o ThreadManForKernel_0032.o ThreadManForKernel_0033.o ThreadManForKernel_0034.o ThreadManForKernel_0035.o ThreadManForKernel_0036.o ThreadManForKernel_0037.o ThreadManForKernel_0038.o ThreadManForKernel_0039.o ThreadManForKernel_0040.o ThreadManForKernel_0041.o ThreadManForKernel_0042.o ThreadManForKernel_0043.o ThreadManForKernel_0044.o ThreadManForKernel_0045.o ThreadManForKernel_0046.o ThreadManForKernel_0047.o ThreadManForKernel_0048.o ThreadManForKernel_0049.o ThreadManForKernel_0050.o ThreadManForKernel_0051.o ThreadManForKernel_0052.o ThreadManForKernel_0053.o ThreadManForKernel_0054.o ThreadManForKernel_0055.o ThreadManForKernel_0056.o ThreadManForKernel_0057.o ThreadManForKernel_0058.o ThreadManForKernel_0059.o ThreadManForKernel_0060.o ThreadManForKernel_0061.o ThreadManForKernel_0062.o ThreadManForKernel_0063.o ThreadManForKernel_0064.o ThreadManForKernel_0065.o ThreadManForKernel_0066.o ThreadManForKernel_0067.o ThreadManForKernel_0068.o ThreadManForKernel_0069.o ThreadManForKernel_0070.o ThreadManForKernel_0071.o ThreadManForKernel_0072.o ThreadManForKernel_0073.o ThreadManForKernel_0074.o ThreadManForKernel_0075.o ThreadManForKernel_0076.o ThreadManForKernel_0077.o ThreadManForKernel_0078.o ThreadManForKernel_0079.o ThreadManForKernel_0080.o ThreadManForKernel_0081.o ThreadManForKernel_0082.o ThreadManForKernel_0083.o ThreadManForKernel_0084.o ThreadManForKernel_0085.o ThreadManForKernel_0086.o ThreadManForKernel_0087.o ThreadManForKernel_0088.o ThreadManForKernel_0089.o ThreadManForKernel_0090.o ThreadManForKernel_0091.o ThreadManForKernel_0092.o ThreadManForKernel_0093.o ThreadManForKernel_0094.o ThreadManForKernel_0095.o ThreadManForKernel_0096.o ThreadManForKernel_0097.o ThreadManForKernel_0098.o ThreadManForKernel_0099.o ThreadManForKernel_0100.o ThreadManForKernel_0101.o ThreadManForKernel_0102.o ThreadManForKernel_0103.o ThreadManForKernel_0104.o ThreadManForKernel_0105.o ThreadManForKernel_0106.o ThreadManForKernel_0107.o ThreadManForKernel_0108.o ThreadManForKernel_0109.o ThreadManForKernel_0110.o ThreadManForKernel_0111.o ThreadManForKernel_0112.o ThreadManForKernel_0113.o ThreadManForKernel_0114.o ThreadManForKernel_0115.o ThreadManForKernel_0116.o ThreadManForKernel_0117.o ThreadManForKernel_0118.o ThreadManForKernel_0119.o ThreadManForKernel_0120.o ThreadManForKernel_0121.o ThreadManForKernel_0122.o ThreadManForKernel_0123.o ThreadManForKernel_0124.o ThreadManForKernel_0125.o ThreadManForKernel_0126.o ThreadManForKernel_0127.o ThreadManForKernel_0128.o ThreadManForKernel_0129.o ThreadManForKernel_0130.o ThreadManForKernel_0131.o ThreadManForKernel_0132.o ThreadManForKernel_0133.o ThreadManForKernel_0134.o ThreadManForKernel_0135.o 

SYSCLIB_OBJS = SysclibForKernel_0000.o SysclibForKernel_0001.o SysclibForKernel_0002.o SysclibForKernel_0003.o SysclibForKernel_0004.o SysclibForKernel_0005.o SysclibForKernel_0006.o SysclibForKernel_0007.o SysclibForKernel_0008.o SysclibForKernel_0009.o SysclibForKernel_0010.o SysclibForKernel_0011.o SysclibForKernel_0012.o SysclibForKernel_0013.o SysclibForKernel_0014.o SysclibForKernel_0015.o SysclibForKernel_0016.o SysclibForKernel_0017.o SysclibForKernel_0018.o SysclibForKernel_0019.o SysclibForKernel_0020.o SysclibForKernel_0021.o SysclibForKernel_0022.o SysclibForKernel_0023.o SysclibForKernel_0024.o SysclibForKernel_0025.o SysclibForKernel_0026.o SysclibForKernel_0027.o SysclibForKernel_0028.o SysclibForKernel_0029.o SysclibForKernel_0030.o SysclibForKernel_0031.o SysclibForKernel_0032.o SysclibForKernel_0033.o SysclibForKernel_0034.o SysclibForKernel_0035.o SysclibForKernel_0036.o SysclibForKernel_0037.o SysclibForKernel_0038.o SysclibForKernel_0039.o SysclibForKernel_0040.o SysclibForKernel_0041.o SysclibForKernel_0042.o 

LOADEXEC_OBJS = LoadExecForKernel_0000.o LoadExecForKernel_0001.o LoadExecForKernel_0002.o LoadExecForKernel_0003.o LoadExecForKernel_0004.o LoadExecForKernel_0005.o LoadExecForKernel_0006.o LoadExecForKernel_0007.o LoadExecForKernel_0008.o LoadExecForKernel_0009.o LoadExecForKernel_0010.o LoadExecForKernel_0011.o LoadExecForKernel_0012.o LoadExecForKernel_0013.o LoadExecForKernel_0014.o LoadExecForKernel_0015.o LoadExecForKernel_0016.o LoadExecForKernel_0017.o LoadExecForKernel_0018.o LoadExecForKernel_0019.o LoadExecForKernel_0020.o LoadExecForKernel_0021.o LoadExecForKernel_0022.o LoadExecForKernel_0023.o LoadExecForKernel_0024.o LoadExecForKernel_0025.o LoadExecForKernel_0026.o 

SYSMEM_OBJS = SysMemForKernel_0000.o SysMemForKernel_0001.o SysMemForKernel_0002.o SysMemForKernel_0003.o SysMemForKernel_0004.o SysMemForKernel_0005.o SysMemForKernel_0006.o SysMemForKernel_0007.o SysMemForKernel_0008.o SysMemForKernel_0009.o SysMemForKernel_0010.o SysMemForKernel_0011.o SysMemForKernel_0012.o SysMemForKernel_0013.o SysMemForKernel_0014.o SysMemForKernel_0015.o SysMemForKernel_0016.o SysMemForKernel_0017.o SysMemForKernel_0018.o SysMemForKernel_0019.o SysMemForKernel_0020.o SysMemForKernel_0021.o SysMemForKernel_0022.o SysMemForKernel_0023.o SysMemForKernel_0024.o SysMemForKernel_0025.o SysMemForKernel_0026.o SysMemForKernel_0027.o SysMemForKernel_0028.o SysMemForKernel_0029.o SysMemForKernel_0030.o SysMemForKernel_0031.o SysMemForKernel_0032.o SysMemForKernel_0033.o SysMemForKernel_0034.o SysMemForKernel_0035.o SysMemForKernel_0036.o SysMemForKernel_0037.o SysMemForKernel_0038.o SysMemForKernel_0039.o SysMemForKernel_0040.o SysMemForKernel_0041.o SysMemForKernel_0042.o SysMemForKernel_0043.o SysMemForKernel_0044.o SysMemForKernel_0045.o SysMemForKernel_0046.o SysMemForKernel_0047.o SysMemForKernel_0048.o SysMemForKernel_0049.o SysMemForKernel_0050.o SysMemForKernel_0051.o SysMemForKernel_0052.o SysMemForKernel_0053.o SysMemForKernel_0054.o SysMemForKernel_0055.o SysMemForKernel_0056.o SysMemForKernel_0057.o SysMemForKernel_0058.o SysMemForKernel_0059.o SysMemForKernel_0060.o SysMemForKernel_0061.o SysMemForKernel_0062.o SysMemForKernel_0063.o SysMemForKernel_0064.o SysMemForKernel_0065.o SysMemForKernel_0066.o SysMemForKernel_0067.o SysMemForKernel_0068.o

MODULE_OBJS = ModuleMgrForKernel_0000.o ModuleMgrForKernel_0001.o ModuleMgrForKernel_0002.o ModuleMgrForKernel_0003.o ModuleMgrForKernel_0004.o ModuleMgrForKernel_0005.o ModuleMgrForKernel_0006.o ModuleMgrForKernel_0007.o ModuleMgrForKernel_0008.o ModuleMgrForKernel_0009.o ModuleMgrForKernel_0010.o ModuleMgrForKernel_0011.o ModuleMgrForKernel_0012.o ModuleMgrForKernel_0013.o ModuleMgrForKernel_0014.o ModuleMgrForKernel_0015.o ModuleMgrForKernel_0016.o ModuleMgrForKernel_0017.o ModuleMgrForKernel_0018.o ModuleMgrForKernel_0019.o ModuleMgrForKernel_0020.o ModuleMgrForKernel_0021.o ModuleMgrForKernel_0022.o 

IDSTORAGE_OBJS = sceIdStorage_driver_0000.o sceIdStorage_driver_0001.o sceIdStorage_driver_0002.o sceIdStorage_driver_0003.o sceIdStorage_driver_0004.o sceIdStorage_driver_0005.o sceIdStorage_driver_0006.o sceIdStorage_driver_0007.o sceIdStorage_driver_0008.o sceIdStorage_driver_0009.o sceIdStorage_driver_0010.o sceIdStorage_driver_0011.o sceIdStorage_driver_0012.o sceIdStorage_driver_0013.o sceIdStorage_driver_0014.o sceIdStorage_driver_0015.o sceIdStorage_driver_0016.o sceIdStorage_driver_0017.o sceIdStorage_driver_0018.o sceIdStorage_driver_0019.o sceIdStorage_driver_0020.o 

SYSTIMER_OBJS = SysTimerForKernel_0000.o SysTimerForKernel_0001.o SysTimerForKernel_0002.o SysTimerForKernel_0003.o SysTimerForKernel_0004.o SysTimerForKernel_0005.o SysTimerForKernel_0006.o SysTimerForKernel_0007.o SysTimerForKernel_0008.o SysTimerForKernel_0009.o 

SYSEVENT_OBJS = sceSysEventForKernel_0000.o sceSysEventForKernel_0001.o sceSysEventForKernel_0002.o sceSysEventForKernel_0003.o sceSysEventForKernel_0004.o sceSysEventForKernel_0005.o 

IMPOSE_OBJS = sceImpose_driver_0000.o sceImpose_driver_0001.o sceImpose_driver_0002.o sceImpose_driver_0003.o sceImpose_driver_0004.o sceImpose_driver_0005.o sceImpose_driver_0006.o sceImpose_driver_0007.o sceImpose_driver_0008.o sceImpose_driver_0009.o sceImpose_driver_0010.o sceImpose_driver_0011.o sceImpose_driver_0012.o sceImpose_driver_0013.o sceImpose_driver_0014.o sceImpose_driver_0015.o sceImpose_driver_0016.o sceImpose_driver_0017.o sceImpose_driver_0018.o sceImpose_driver_0019.o sceImpose_driver_0020.o sceImpose_driver_0021.o sceImpose_driver_0022.o sceImpose_driver_0023.o 

INIT_OBJS = InitForKernel_0000.o InitForKernel_0001.o InitForKernel_0002.o InitForKernel_0003.o InitForKernel_0004.o InitForKernel_0005.o InitForKernel_0006.o InitForKernel_0007.o InitForKernel_0008.o InitForKernel_0009.o InitForKernel_0010.o InitForKernel_0011.o

AUDIOROUTING_OBJS = sceAudioRouting_driver_0000.o sceAudioRouting_driver_0001.o sceAudioRouting_driver_0002.o sceAudioRouting_driver_0003.o sceAudioRouting_driver_0004.o

libpspkernelincludedir = @PSPSDK_INCLUDEDIR@

libpspkernelinclude_HEADERS =	\
	pspiofilemgr_kernel.h	\
	pspkernel.h		\
	psploadcore.h		\
	psploadexec_kernel.h	\
	pspstdio_kernel.h	\
	pspsysreg.h		\
	psputilsforkernel.h	\
	pspkdebug.h		\
	pspintrman_kernel.h	\
	pspmodulemgr_kernel.h	\
	pspsystimer.h		\
	pspsysmem_kernel.h	\
	pspthreadman_kernel.h	\
	pspsyscon.h		\
	pspsysevent.h		\
	pspidstorage.h		\
	pspexception.h 		\
	pspsysclib.h		\
	pspimpose_driver.h	\
	pspinit.h			\
	pspaudiorouting.h

lib_LIBRARIES = libpspkernel.a

libpspkernel_a_SOURCES =	\
	ExceptionManagerForKernel.S \
	KDebugForKernel.S	\
	LoadCoreForKernel.S	\
	IoFileMgrForKernel.S	\
	StdioForKernel.S	\
	sceSyscon_driver.S	\
	sceSysreg_driver.S	\
	UtilsForKernel.S	\
	InterruptManagerForKernel.S \
	ThreadManForKernel.S	\
	SysclibForKernel.S	\
	LoadExecForKernel.S	\
	SysMemForKernel.S 	\
	SysTimerForKernel.S 	\
	sceSysEventForKernel.S	\
	ModuleMgrForKernel.S	\
	sceIdStorage_driver.S	\
	sceImpose_driver.S	\
	InitForKernel.S		\
	sceAudioRouting_driver.S

libpspkernel_a_LIBADD = $(EXCEPTION_OBJS) $(KDEBUG_OBJS) $(LOADCORE_OBJS) $(IO_OBJS) \
						$(STDIO_OBJS) $(SYSREG_OBJS) $(UTILS_OBJS) $(SYSCON_OBJS) $(INTR_OBJS) \
						$(THREAD_OBJS) $(SYSCLIB_OBJS) $(LOADEXEC_OBJS) $(SYSMEM_OBJS) $(MODULE_OBJS) \
						$(IDSTORAGE_OBJS) $(SYSTIMER_OBJS) $(SYSEVENT_OBJS) $(IMPOSE_OBJS) $(INIT_OBJS) \
						$(AUDIOROUTING_OBJS)

$(EXCEPTION_OBJS): ExceptionManagerForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(KDEBUG_OBJS): KDebugForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(LOADCORE_OBJS): LoadCoreForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(IO_OBJS): IoFileMgrForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(STDIO_OBJS): StdioForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SYSREG_OBJS): sceSysreg_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

$(UTILS_OBJS): UtilsForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SYSCON_OBJS): sceSyscon_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

$(INTR_OBJS): InterruptManagerForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(THREAD_OBJS): ThreadManForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SYSCLIB_OBJS): SysclibForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(LOADEXEC_OBJS): LoadExecForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SYSMEM_OBJS): SysMemForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(MODULE_OBJS): ModuleMgrForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(IDSTORAGE_OBJS): sceIdStorage_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SYSTIMER_OBJS): SysTimerForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SYSEVENT_OBJS): sceSysEventForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(IMPOSE_OBJS): sceImpose_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

$(INIT_OBJS): InitForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(AUDIOROUTING_OBJS): sceAudioRouting_driver.S
	$(COMPILE) -DF_$* $< -c -o $@
