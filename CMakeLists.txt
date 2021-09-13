cmake_minimum_required(VERSION 3.19)
project(Project_5_Related_Files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project_5_Related_Files
        Dlist.h
        Instr.h
        sam.cpp
        sample.in
        sample.out
        sample_s.out
#        test.cpp
        DlistImpl.h
        )
