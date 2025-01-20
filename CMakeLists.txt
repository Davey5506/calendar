cmake_minimum_required(VERSION 3.30)
project(calendar C)

set(CMAKE_C_STANDARD 11)

add_executable(calendar main.c
        calendartools.c
        calendartools.h)
