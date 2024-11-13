cmake_minimum_required(VERSION 3.27)
project(MARC_master__1_ C)

set(CMAKE_C_STANDARD 11)

include_directories(MARC-master)

add_executable(MARC_master__1_
        MARC-master/loc.c
        MARC-master/loc.h
        MARC-master/main.c
        MARC-master/map.c
        MARC-master/map.h
        MARC-master/moves.c
        MARC-master/moves.h
        MARC-master/queue.c
        MARC-master/queue.h
        MARC-master/stack.c
        MARC-master/stack.h
        MARC-master/random.c
        MARC-master/random.h)
