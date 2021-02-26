cmake_minimum_required(VERSION 3.12)
project(c_luavm C)

set(CMAKE_C_STANDARD 90)

include_directories(luavm)

add_subdirectory(luavm)

add_executable(${PROJECT_NAME}_tests c_src/luavm_tests.c)
target_link_libraries(${PROJECT_NAME}_tests luavm)
