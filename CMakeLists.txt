cmake_minimum_required(VERSION 2.8.4)
project(Futoshiki)

set(DEBUG OFF)

option(DEBUG "Activate the debug mode (more print)")
option(VERBOSE "Activate the full verbose mode")

IF(DEBUG)
    message("-- DEBUG : ON")
    add_definitions(-DDEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3")
ENDIF()

IF(VERBOSE)
    message("-- VERBOSE : ON")
    add_definitions(-DVERBOSE)
ENDIF()

IF(NOT DEBUG)
    message("-- RELEASE : ON")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
ENDIF()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -W -std=c99 -pedantic -I.")
set(SOURCE_FILES main.c)
set(FILES {
    util.h
    constraint.h
    initTest.h
    file.h
    domain.h
})

add_executable(Futoshiki.out ${SOURCE_FILES})