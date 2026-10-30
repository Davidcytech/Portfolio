cmake_minimum_required(VERSION 4.3)
project(HTTPServerC C)

set(CMAKE_C_STANDARD 11)

add_executable(HTTPServerC main.c
        http.c
        http.h)
