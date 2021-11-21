cmake_minimum_required(VERSION 3.20)
project(hw2 C)

set(CMAKE_C_STANDARD 11)

add_executable(hw2 main.c lib/static/serial_ranking.c lib/static/serial_ranking.h io.c io.h)
