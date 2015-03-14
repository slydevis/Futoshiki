cmake_minimum_required(VERSION 2.8.4)
project(Futoshiki)

set(DEBUG OFF)

option(DEBUG "Activate the debug mode (more print)")

IF(DEBUG)
    message("-- DEBUG : ON")
    add_definitions(-DDEBUG)
ENDIF()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -W -std=c99 -pedantic -I.")
set(SOURCE_FILES main.c)
set(FILES {
    util.h
    constraint.h
    initTest.h
    file.h
})

add_executable(Futoshiki.out ${SOURCE_FILES})