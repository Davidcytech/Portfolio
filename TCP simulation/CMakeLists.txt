cmake_minimum_required(VERSION 4.3)
project(TCP C)

set(CMAKE_C_STANDARD 11)

add_executable(server server.c)
add_executable(client Client.c)