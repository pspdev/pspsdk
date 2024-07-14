#!/bin/bash

## Fail script if an error happens
set -e

## Enter the pspsdk directory.
cd "$(dirname "$0")" || { echo "ERROR: Could not enter the pspsdk directory."; exit 1; }

## Make sure PSPDEV is set
if [ -z "${PSPDEV}" ]; then
    echo "The PSPDEV environment variable has not been set"
    exit 1
fi

## Build pspsdk
./bootstrap
./configure
make clean
make -j $(getconf _NPROCESSORS_ONLN)

## Install pspsdk
make install

## gcc needs to include libcglue libpthreadglue libpspprof libpsputility libpsprtc libpspnet_inet libpspnet_resolver libpspsdk libpspmodinfo libpspuser libpspkernel
## from pspsdk to be able to build executables, because they are part of the standard libraries
cd "$PSPDEV/psp/lib"
ln -sf "../sdk/lib/libcglue.a" "libcglue.a" || { exit 1; }
ln -sf "../sdk/lib/libpthreadglue.a" "libpthreadglue.a" || { exit 1; }
ln -sf "../sdk/lib/libpspprof.a" "libpspprof.a" || { exit 1; }
ln -sf "../sdk/lib/libpsputility.a" "libpsputility.a" || { exit 1; }
ln -sf "../sdk/lib/libpsprtc.a" "libpsprtc.a" || { exit 1; }
ln -sf "../sdk/lib/libpspnet_inet.a" "libpspnet_inet.a" || { exit 1; }
ln -sf "../sdk/lib/libpspnet_resolver.a" "libpspnet_resolver.a" || { exit 1; }
ln -sf "../sdk/lib/libpspsdk.a" "libpspsdk.a" || { exit 1; }
ln -sf "../sdk/lib/libpspmodinfo.a" "libpspmodinfo.a" || { exit 1; }
ln -sf "../sdk/lib/libpspuser.a" "libpspuser.a" || { exit 1; }
ln -sf "../sdk/lib/libpspkernel.a" "libpspkernel.a" || { exit 1; }
cd -

## Store build information
BUILD_FILE="${PSPDEV}/build.txt"
if [[ -f "${BUILD_FILE}" ]]; then
  sed -i'' '/^pspsdk /d' "${BUILD_FILE}"
fi
git log -1 --format="pspsdk %H %cs %s" >> "${BUILD_FILE}"
