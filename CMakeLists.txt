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

find_library(LIBEVENT libevent.a)
message(STATUS "Found libevent library: ${LIBEVENT}")

find_library(LIBEVENT_CORE libevent_core.a)
message(STATUS "Found libevent-core library: ${LIBEVENT_CORE}")

add_executable(
    ${PROJECT_NAME} src/main.cpp
    ${SRV_CONTENT_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${LIBEVENT}
    ${LIBEVENT_CORE}
)
