cmake_minimum_required(VERSION 3.10)

project(Pokerbot VERSION 1.0.0)

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

## Executable
add_executable(Pokerbot main.cpp)

target_link_libraries(
  Pokerbot  
  DetectionLib 
  SharedLib 
  CaptureLib 
  GuiLib 
  PokerLib 
  ${CONAN_LIBS}
  )




