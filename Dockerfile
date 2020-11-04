FROM debian:buster-20201012

RUN apt-get update \
    && apt-get install -y \
        g++ \
        cmake \
        make

COPY . /app

WORKDIR /app

RUN cmake . && make

ENTRYPOINT ["/app/service-content"]
