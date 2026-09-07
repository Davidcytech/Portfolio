cmake_minimum_required(VERSION 4.3)
project(FileParser C)

set(CMAKE_C_STANDARD 11)

add_executable(FileParser main.c
        EndianTranslator.c
        EndianTranslator.h)
