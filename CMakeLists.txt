cmake_minimum_required(VERSION 3.13)
project(Assembler)

set(CMAKE_CXX_STANDARD 11)

add_executable(Assembler main.cpp binary_convert.cpp binary_convert.h)