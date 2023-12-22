cmake_minimum_required(VERSION 3.24)
project(cc C)

set(CMAKE_C_STANDARD 17)

add_executable(cc main.c compiler.c cprocess.c utils/vector.h utils/vector.c utils/buffer.h utils/buffer.c lexing_process.c lexer.c)
