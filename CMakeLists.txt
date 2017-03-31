cmake_minimum_required(VERSION 3.5)
project(Computer)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(MySimpleComputer)
add_subdirectory(MyTerm)
add_subdirectory(MyBigChars)
add_subdirectory(MyReadKey)

include_directories(${MySimpleComputer_SOURCE_DIR}/include)
include_directories(${MyTerm_SOURCE_DIR}/include)
include_directories(${MyBigChars_SOURCE_DIR}/include)
include_directories(${MyReadKey_SOURCE_DIR}/include)

set(CF_HEADERS draw_interface.h)
set(CF_SOURCES main.c draw_interface.c)

add_executable(${PROJECT_NAME} ${CF_HEADERS} ${CF_SOURCES})
target_link_libraries(${PROJECT_NAME} MySimpleComputer MyTerm MyBigChars MyReadKey)