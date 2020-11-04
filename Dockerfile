FROM debian:buster-20201012

RUN apt-get update \
    && apt-get install -y \
        g++ \
        cmake \
        make \
        libevent-dev \
        libevent-2.1-6 \
        libevent-core-2.1-6

COPY . /app

WORKDIR /app

RUN cmake . && make

ENTRYPOINT ["/app/service-content"]
