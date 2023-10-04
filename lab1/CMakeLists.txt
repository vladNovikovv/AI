cmake_minimum_required(VERSION 3.25)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

# Установка размера стека
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,20971520")

add_executable(lab1 main.cpp Node.cpp Node.h Tree.cpp Tree.h)
