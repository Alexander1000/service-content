cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(service-content)

set(SRV_CONTENT_SOURCES
    src/main.cpp
    src/storage.cpp
    src/connection.cpp
    src/config.cpp
    src/api/save.cpp
    src/middleware/add_server.cpp
    src/middleware/chain.cpp
)

include_directories(
    include
    /usr/local/include
)

link_directories(
    /usr/local/lib/
    /usr/local/lib/postgresql/
)

find_library(LIBPQ libpq.so)
message(STATUS "Found libpq: ${LIBPQ}")

find_library(LIBPQXX libpqxx.so)
message(STATUS "Found libpqxx: ${LIBPQXX}")

find_library(JSON_STREAM_ANALYZER libjson-stream-analyzer.a)
message(STATUS "Found json-stream-analyzer library: ${JSON_STREAM_ANALYZER}")

find_library(IO_BUFFER libio-buffer.a)
message(STATUS "Found io-buffer library: ${IO_BUFFER}")

find_library(SOCKETER libsocketer.a)
message(STATUS "Found socketer library: ${SOCKETER}")

add_executable(
    ${PROJECT_NAME} src/main.cpp
    ${SRV_CONTENT_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${LIBPQ}
    ${LIBPQXX}
    ${JSON_STREAM_ANALYZER}
    ${IO_BUFFER}
    ${SOCKETER}
)
