cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

project(glPlay VERSION 0.1 DESCRIPTION "OpenGL PlayGround")

option(BUILD_DEMO "build demo" ON)

if(BUILD_DEMO)
    message("option BUILD_DEMO: ON")
    add_subdirectory(demo)
endif()

if(NOT BUILD_DEMO)
    message("option BUILD_DEMO: OFF")
endif()
