cmake_minimum_required(VERSION 3.10)

project(Pokerbot VERSION 1.1.0)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD          11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# Set Up Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Bring templates into the project
include_directories(
    ${PROJECT_SOURCE_DIR}/templates/classes
    ${PROJECT_SOURCE_DIR}/templates/functions  
    )

## find gtest
find_package(GTest REQUIRED)

## find OpenGL
find_package( OpenGL REQUIRED )

IF(UNIX)
## find GLEW
find_package( GLEW REQUIRED )
ENDIF()

## set up unit testing
include(CTest)

## shared
add_subdirectory(shared)

## gui
add_subdirectory(gui)

## capture
add_subdirectory(capture)

## detection
add_subdirectory(detection)

## poker
add_subdirectory(poker)

## tests
add_subdirectory(unit_tests)

## app
add_subdirectory(app)





