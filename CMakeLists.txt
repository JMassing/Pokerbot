cmake_minimum_required(VERSION 3.10)

project(Pokerbot VERSION 1.1.2)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

## Set lib names
set(POKERLIB_NAME         "PokerLib")
set(DETECTIONLIB_NAME     "DetectionLib")
set(SHAREDLIB_NAME        "SharedLib")
set(CAPTURELIB_NAME       "CaptureLib")
set(GUILIB_NAME           "GuiLib")
set(TEMPLATELIB_NAME      "TemplateLib")
set(GLFWLIB_NAME          "glfw")

#options
option(ENABLE_CODE_COVERAGE "Enable a Code Coverage build." OFF)

# Include own cmake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(Documentation)
if(ENABLE_CODE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        include(CodeCoverage)
    else()
        message("You must use a GNU or Clang Compiler for CodeCoverage!")
    endif()
endif()


# Set Up Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

## find OpenGL
find_package(OpenGL REQUIRED)

if(UNIX)
    ## find GLEW
    find_package(GLEW REQUIRED)
endif()

## set up unit testing
include(CTest)

## shared
add_subdirectory(shared)

## templates
add_subdirectory(templates)

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

## external libraries
add_subdirectory(external)





