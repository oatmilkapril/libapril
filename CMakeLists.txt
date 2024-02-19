cmake_minimum_required(VERSION 3.15)
project(libapril C)

set(CMAKE_C_STANDARD 99)

add_library(april STATIC
        src/sys/process.c
        src/sys/io.c
        src/error.c
        src/data/linked_list.c
        src/sys/signal.c
        src/sio.c)
target_include_directories(april PUBLIC include)

add_subdirectory(examples)

