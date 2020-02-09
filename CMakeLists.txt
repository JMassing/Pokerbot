cmake_minimum_required(VERSION 3.10)

project(Pokerbot VERSION 0.1.0)


# Bring all headers into the project
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# add executables
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(pokerbot main.cpp ${SOURCES})


