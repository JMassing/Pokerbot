cmake_minimum_required(VERSION 3.10)


project(Pokerbot VERSION 0.1.0)


# Bring all headers into the project
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/detection/include
    ${CMAKE_CURRENT_SOURCE_DIR}/visualization/include )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


# add executables
file(GLOB SOURCES_DETECTION "detection/src/*.cpp")
file(GLOB SOURCES_VISULIZATION "visualization/src/*.cpp")
add_executable(Pokerbot main.cpp ${SOURCES} ${SOURCES_DETECTION} ${SOURCES_VISULIZATION})

target_link_libraries(Pokerbot ${CONAN_LIBS})




