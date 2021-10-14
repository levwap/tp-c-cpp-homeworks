cmake_minimum_required(VERSION 3.20)
project(hw1)

set(CMAKE_C_STANDARD 11)

set(LIB_SOURCE_FILES src/ship.c)
add_library(ship STATIC src/ship.c)

add_executable(hw1 src/main.c)
target_link_libraries(hw1 ship)



enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(ship_test src/ship_test.cpp)
target_link_libraries(ship_test ${GTEST_LIBRARIES} pthread ship)

#cmake_minimum_required(VERSION 3.20)
#project(hw1 C)
#
#set(CMAKE_C_STANDARD 11)
#
#
#add_executable(hw1 main.c ship.c)
