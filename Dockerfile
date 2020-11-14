FROM dankovtsev.pro:5000/utils/cpp:latest

COPY . /app

WORKDIR /app

RUN cmake . && make

ENTRYPOINT ["/app/service-content"]
