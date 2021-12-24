if(DEFINED ENV{PSPDEV})
    SET(PSPDEV $ENV{PSPDEV})
else()
    message(FATAL_ERROR "The environment variable PSPDEV needs to be defined.")
endif()

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR mips)
SET(CMAKE_C_COMPILER psp-gcc)
SET(CMAKE_CXX_COMPILER psp-g++)
SET(CMAKE_C_FLAGS_INIT "-I${PSPDEV}/psp/include -I${PSPDEV}/psp/sdk/include -DPSP -O2 -G0")
SET(CMAKE_CXX_FLAGS_INIT "-I${PSPDEV}/psp/include -I${PSPDEV}/psp/sdk/include -DPSP -O2 -G0")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-L${PSPDEV}/lib -L${PSPDEV}/psp/lib -L${PSPDEV}/psp/sdk/lib -Wl,-zmax-page-size=128")
#SET(CMAKE_SHARED_LINKER_FLAGS_INIT "...")
#SET(CMAKE_STATIC_LINKER_FLAGS_CONFIG_INIT "...")
#SET(CMAKE_STATIC_LINKER_FLAGS_INIT "...")
SET(CMAKE_INSTALL_PREFIX "${PSPDEV}/psp" CACHE PATH)

SET(CMAKE_FIND_ROOT_PATH ${PSPDEV} ${PSPDEV}/psp ${PSPDEV}/psp/sdk)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

## Add Default PSPSDK Libraries according to build.mak and add stdc++ for C++ builds so this doesn't need to be done manually later
include_directories(${PSPDEV}/psp/include ${PSPDEV}/psp/sdk/include)
link_directories( ${PSPDEV}/lib ${PSPDEV}/psp/lib ${PSPDEV}/psp/sdk/lib)

add_definitions("-D__PSP__")
add_definitions("-DPSP")
SET(PLATFORM_PSP TRUE)
SET(PSP TRUE)

include("${PSPDEV}/psp/share/CreatePBP.cmake")
