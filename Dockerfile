FROM debian:latest AS base
RUN set -ex;                                                                      \
    apt-get update;                                                               \
    apt-get install -y g++ curl libcurl4 libcurl4-openssl-dev cmake;             \
    apt-get upgrade -y

FROM base AS builder
RUN set -ex;                                                                      \
    mkdir -p /usr/src/cloudflareDDNS

COPY . /usr/src/cloudflareDDNS

RUN set -ex;                                                                      \
    cd /usr/src/cloudflareDDNS;                                                   \
    rm -rf build;                                                                 \
    cmake -H. -Bbuild;                                                            \
    cd build;                                                                     \
    make all                                                                     

FROM base AS runtime

COPY --from=builder /usr/src/cloudflareDDNS/build /cloudflareDDNS/build

CMD cd cloudflareDDNS/build && ./updater