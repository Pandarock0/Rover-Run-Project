cmake_minimum_required(VERSION 3.27)
project(Rover-Run-Project C)

set(CMAKE_C_STANDARD 11)

add_executable(Rover-Run-Project main.c
        loc.c
        loc.h
        moves.c
        moves.h
        map.c
        map.h
        queue.c
        queue.h
        stack.c
        stack.h)