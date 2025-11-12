cmake_minimum_required(VERSION 3.16)
project(REALLAY)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(
    source/test
)

add_executable(
    ${PROJECT_NAME}
    source/main.cpp
    source/comp/relay.cpp
    source/computer.cpp
)