cmake_minimum_required(VERSION 3.12)
project(luavm C)

set(CMAKE_C_STANDARD 90)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall -Wextra -DLUA_COMPAT_5_3")
set(SOURCES_CORE lapi.c lcode.c lctype.c ldebug.c ldo.c ldump.c lfunc.c lgc.c llex.c lmem.c lobject.c lopcodes.c lparser.c lstate.c lstring.c ltable.c ltm.c lundump.c lvm.c lzio.c)
set(SOURCES_LIB lauxlib.c lbaselib.c lcorolib.c ldblib.c liolib.c lmathlib.c loadlib.c loslib.c lstrlib.c ltablib.c lutf8lib.c linit.c)

add_library(${PROJECT_NAME} STATIC ${SOURCES_CORE} ${SOURCES_LIB})
target_compile_definitions(${PROJECT_NAME} PUBLIC -DLUA_USE_C89)

add_executable(luac luac.c)
target_link_libraries(luac PUBLIC ${PROJECT_NAME})
target_compile_definitions(luac PUBLIC -DLUA_USE_C89)

add_executable(lua lua.c)
target_link_libraries(lua PUBLIC ${PROJECT_NAME})
target_compile_definitions(lua PUBLIC -DLUA_USE_C89)