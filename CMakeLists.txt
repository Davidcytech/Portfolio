cmake_minimum_required(VERSION 4.3)
project(DataStructures C)

set(CMAKE_C_STANDARD 11)

add_executable(DataStructures LinkedLists.c
        main.c
        LinkedLists.h
        Stack.h
        Stack.c
        Queue.h
        Queue.c
        Process.h
        HashTable.h
        HashTable.c
        InputUtils.h
        InputUtils.c)
