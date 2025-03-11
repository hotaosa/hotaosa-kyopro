cmake_minimum_required(VERSION 3.22)
project(hotaosa)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring Debug build")
    add_compile_options(
        -g
        -O0
        -Wall -Wextra -Wpedantic
        -Wshadow -Wconversion
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring Release build")
    add_compile_options(
        -O3
        -march=native
        -flto
        -DNDEBUG
    )
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(a.out main.cc)