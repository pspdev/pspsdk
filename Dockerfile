# First stage
ARG BASE_DOCKER_IMAGE

FROM $BASE_DOCKER_IMAGE

COPY . /src

RUN apk add build-base autoconf automake zlib-dev
RUN cd /src && \
    ./bootstrap && \
    ./configure && \
    make -j $(getconf _NPROCESSORS_ONLN) clean && \
    make -j $(getconf _NPROCESSORS_ONLN) && \
    make -j $(getconf _NPROCESSORS_ONLN) install

## gcc needs to include libcglue libpthreadglue libpsputility libpsprtc libpspnet_inet libpspnet_resolver libpspsdk libpspmodinfo libpspuser libpspkernel
## from pspsdk to be able to build executables, because they are part of the standard libraries
RUN ln -sf "$PSPDEV/psp/sdk/lib/libcglue.a" "$PSPDEV/psp/lib/libcglue.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpthreadglue.a" "$PSPDEV/psp/lib/libpthreadglue.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpsputility.a" "$PSPDEV/psp/lib/libpsputility.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpsprtc.a" "$PSPDEV/psp/lib/libpsprtc.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpspnet_inet.a" "$PSPDEV/psp/lib/libpspnet_inet.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpspnet_resolver.a" "$PSPDEV/psp/lib/libpspnet_resolver.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpspsdk.a" "$PSPDEV/psp/lib/libpspsdk.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpspmodinfo.a" "$PSPDEV/psp/lib/libpspmodinfo.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpspuser.a" "$PSPDEV/psp/lib/libpspuser.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpspkernel.a" "$PSPDEV/psp/lib/libpspkernel.a" || { exit 1; }

# Second stage
FROM alpine:latest

ENV PSPDEV /usr/local/pspdev
ENV PATH $PATH:${PSPDEV}/bin

COPY --from=0 ${PSPDEV} ${PSPDEV}
RUN apk add --no-cache build-base bash acl sudo fakeroot curl patch gpgme-dev libarchive-tools libarchive-dev xz \
    openssl-dev git bison autoconf automake tcl-dev libtool cmake doxygen texinfo flex pkgconf libcrypto3
