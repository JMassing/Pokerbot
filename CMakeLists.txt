cmake_minimum_required(VERSION 3.10)

project(Pokerbot VERSION 0.1.0)

# Bring all headers into the project
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/detection/include
    ${CMAKE_CURRENT_SOURCE_DIR}/visualization/include
    ${CMAKE_CURRENT_SOURCE_DIR}/poker/include
    ${CMAKE_CURRENT_SOURCE_DIR}/templates/classes
    ${CMAKE_CURRENT_SOURCE_DIR}/templates/functions  
    ${CMAKE_CURRENT_SOURCE_DIR}/globals/include)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# add executables
file(GLOB SOURCES_DETECTION "detection/src/*.cpp")
file(GLOB SOURCES_VISULIZATION "visualization/src/*.cpp")
file(GLOB SOURCES_POKER "poker/src/*.cpp")


add_library( PokerbotLib 
${SOURCES_VISULIZATION}
${SOURCES_DETECTION}
${SOURCES_POKER} )

## find gtest
find_package(GTest REQUIRED)

## tests
add_subdirectory(unit_tests)

add_executable(Pokerbot main.cpp)

target_link_libraries(Pokerbot PokerbotLib ${CONAN_LIBS})




