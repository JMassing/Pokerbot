cmake_minimum_required(VERSION 3.10)

project(Pokerbot VERSION 0.1.0)

# Bring all headers into the project
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/detection/include
    ${CMAKE_CURRENT_SOURCE_DIR}/visualization/include
    ${CMAKE_CURRENT_SOURCE_DIR}/poker/include
    ${CMAKE_CURRENT_SOURCE_DIR}/templates/classes
    ${CMAKE_CURRENT_SOURCE_DIR}/templates/functions  
    ${CMAKE_CURRENT_SOURCE_DIR}/globals/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dataClasses/include
    ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/utilities/HelperClasses
    ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/utilities/HelperFunctions)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# add executables
file(GLOB SOURCES_DETECTION "detection/src/*.cpp")
file(GLOB SOURCES_VISULIZATION "visualization/src/*.cpp")
file(GLOB SOURCES_POKER "poker/src/*.cpp")
file(GLOB SOURCES_SIGNALS "dataClasses/src/*.cpp")
file(GLOB SOURCES_PARAMETERS "globals/src/*.cpp")



add_library( PokerbotLib 
${SOURCES_VISULIZATION}
${SOURCES_DETECTION}
${SOURCES_POKER} 
${SOURCES_SIGNALS}
${SOURCES_PARAMETERS})

## find gtest
find_package(GTest REQUIRED)

## find OpenGL
find_package( OpenGL REQUIRED )

## tests
#add_subdirectory(unit_tests)

## add imgui

find_package( Git )
execute_process(
  COMMAND ${GIT_EXECUTABLE} clone "https://github.com/ocornut/imgui.git" -b v1.72b
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
set( IMGUI_DIR ${CMAKE_CURRENT_BINARY_DIR}/imgui )

set( imgui_files
  ${IMGUI_DIR}/imconfig.h
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui.h
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_internal.h
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/imstb_rectpack.h
  ${IMGUI_DIR}/imstb_textedit.h
  ${IMGUI_DIR}/imstb_truetype.h
)

set( imgui_impl_files
  ${IMGUI_DIR}/examples/imgui_impl_glfw.h
  ${IMGUI_DIR}/examples/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/examples/imgui_impl_opengl3.h
  ${IMGUI_DIR}/examples/imgui_impl_opengl3.cpp
)

set( gl3w
  ${IMGUI_DIR}/examples/libs/gl3w/GL/gl3w.c
)

add_executable(Pokerbot ${imgui_files} ${imgui_impl_files} ${gl3w} main.cpp)

## add GLFW

include( ExternalProject )
ExternalProject_Add(
  glfw PREFIX glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3
  CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
    "-DCMAKE_BUILD_TYPE=Release"
    "-DGLFW_BUILD_DOCS=OFF"
    "-DGLFW_BUILD_EXAMPLES=OFF"
    "-DGLFW_BUILD_TESTS=OFF"
)
ExternalProject_Get_Property( glfw INSTALL_DIR )
set( GLFW_DIR ${INSTALL_DIR} )
set( GLFW_INCLUDE_DIR ${GLFW_DIR}/include )
set( GLFW_LIBRARIES   ${GLFW_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX} )
add_dependencies( Pokerbot glfw )

if( OPENGL_FOUND )
    target_link_libraries(Pokerbot PokerbotLib ${CONAN_LIBS})
    include_directories( ${IMGUI_DIR} )
    include_directories( ${IMGUI_DIR}/examples )
    include_directories( ${IMGUI_DIR}/examples/libs/gl3w )
    include_directories( ${OPENGL_INCLUDE_DIR} )
    include_directories( ${GLFW_INCLUDE_DIR} )
  
    target_link_libraries( Pokerbot ${OPENGL_LIBRARIES} )
    target_link_libraries( Pokerbot ${GLFW_LIBRARIES} )
endif()



