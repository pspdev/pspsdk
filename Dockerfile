# First stage
FROM pspdev/psptoolchain:latest

COPY . /src

RUN apk add build-base autoconf automake zlib-dev
RUN cd /src && ./bootstrap && ./configure && make all install clean

# Second stage
FROM alpine:latest

ENV PSPDEV /usr/local/pspdev
ENV PATH $PATH:${PSPDEV}/bin

COPY --from=0 ${PSPDEV} ${PSPDEV}
