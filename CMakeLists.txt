cmake_minimum_required(VERSION 3.27.8)
project(Rover_Run_Project C)

set(CMAKE_C_STANDARD 11)

add_executable(main
        main.c
        project_function.c
        map.c
        loc.c
        stack.c
        queue.c
        moves.c)
