# First stage
ARG BASE_DOCKER_IMAGE

FROM $BASE_DOCKER_IMAGE

COPY . /src

RUN apk add build-base autoconf automake zlib-dev bash git && \
    /src/build-and-install.sh

# Second stage
FROM alpine:latest

ENV PSPDEV /usr/local/pspdev
ENV PATH $PATH:${PSPDEV}/bin

COPY --from=0 ${PSPDEV} ${PSPDEV}
RUN apk add --no-cache build-base bash acl sudo fakeroot curl patch gpgme-dev libarchive-tools libarchive-dev xz \
    openssl-dev git bison autoconf automake tcl-dev libtool cmake doxygen texinfo flex pkgconf libcrypto3
