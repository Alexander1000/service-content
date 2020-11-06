FROM dankovtsev.pro:5000/utils/cpp:latest

RUN apt-get install -y \
        libpqxx-6.2 \
        libpqxx-dev \
        libpqxx-doc \
        libpq-dev

COPY . /app

WORKDIR /app

RUN cmake . && make

ENTRYPOINT ["/app/service-content"]
