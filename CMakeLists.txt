cmake_minimum_required(VERSION 3.5)
project(Computer)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(MySimpleComputer)
add_subdirectory(MyTerm)

include_directories(${MySimpleComputer_SOURCE_DIR}/include)
include_directories(${MyTerm_SOURCE_DIR}/include)

add_executable(Computer main.c)
target_link_libraries(Computer MySimpleComputer MyTerm)