cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(service-content)

set(SRV_CONTENT_SOURCES
    src/main.cpp
)

include_directories(
    include
    /usr/local/include
)

find_library(LIBPQ libpq.a)
message(STATUS "Found libpq: ${LIBPQ}")

find_library(LIBPQXX libpqxx.a)
message(STATUS "Found libpqxx: ${LIBPQXX}")

add_executable(
    ${PROJECT_NAME} src/main.cpp
    ${SRV_CONTENT_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${LIBPQ}
    ${LIBPQXX}
)
