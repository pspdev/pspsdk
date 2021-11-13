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

## gcc needs to include libpsplibc libpsputility libpspnet_inet libpspnet_resolver libpspuser libpspkernel
## from pspsdk to be able to build executables, because they are part of the standard libraries
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpsplibc.a" "$PSPDEV/psp/lib/libpsplibc.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpsputility.a" "$PSPDEV/psp/lib/libpsputility.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpspnet_inet.a" "$PSPDEV/psp/lib/libpspnet_inet.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpspnet_resolver.a" "$PSPDEV/psp/lib/libpspnet_resolver.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpspuser.a" "$PSPDEV/psp/lib/libpspuser.a" || { exit 1; }
RUN ln -sf "$PSPDEV/psp/sdk/lib/libpspkernel.a" "$PSPDEV/psp/lib/libpspkernel.a" || { exit 1; }

# Second stage
FROM alpine:latest

ENV PSPDEV /usr/local/pspdev
ENV PATH $PATH:${PSPDEV}/bin

COPY --from=0 ${PSPDEV} ${PSPDEV}
