cmake_minimum_required(VERSION 4.0)
project(simple_calculator C)

set(CMAKE_C_STANDARD 17)

add_executable(simple_calculator main.c
        stack.h
        stack.c)
