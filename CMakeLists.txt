cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(service-content)

set(SRV_CONTENT_SOURCES
    src/main.cpp
    src/storage/init.cpp
    src/storage/save_page.cpp
    src/storage/save_content.cpp
    src/storage/get_view_by_slug.cpp
    src/connection.cpp
    src/config.cpp
    src/api/content/save.cpp
    src/api/content/parse_request.cpp
    src/api/content/request_save.cpp
    src/api/content/error_response.cpp
    src/api/page/save.cpp
    src/api/page/error_response.cpp
    src/api/page/request_save.cpp
    src/api/page/parse_request.cpp
    src/api/view/handler.cpp
    src/api/view/error_response.cpp
    src/api/view/parse_request.cpp
    src/middleware/add_server.cpp
    src/models/content.cpp
    src/models/view.cpp
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
