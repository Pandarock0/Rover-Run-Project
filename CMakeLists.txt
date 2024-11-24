cmake_minimum_required(VERSION 3.30)
project(Rover_Run_Project C)

set(CMAKE_C_STANDARD 11)

add_executable(Rover_Run_Project main.c
        loc.c
        loc.h
        map.c
        map.h
        project_function.c
        project_function.h
        moves.c
        moves.h
        stack.c
        stack.h
        queue.c
        queue.h)
