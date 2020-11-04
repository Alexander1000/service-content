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

add_executable(
    ${PROJECT_NAME} src/main.cpp
    ${SRV_CONTENT_SOURCES}
)
