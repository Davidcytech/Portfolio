cmake_minimum_required(VERSION 4.3)
project(HexDumpC C)

set(CMAKE_C_STANDARD 11)

add_executable(HexDumpC main.c example.txt)
configure_file(
        example.txt
        example.txt
        COPYONLY
)
