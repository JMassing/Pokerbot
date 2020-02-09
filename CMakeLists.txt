cmake_minimum_required(VERSION 3.10)

project(Pokerbot VERSION 0.1.0)

# Bring all headers into the project
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(OpenCV_LIB_DIR "C:\Users\julim\Desktop\vs_dev_lib\opencv")
set(BOOST_LIB_DIR "C:\Users\julim\Desktop\vs_dev_lib\boost_1_72_0")

link_directories(${OpenCV_LIB_DIR} ${BOOST_LIB_DIR})
# add executables
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(pokerbot main.cpp ${SOURCES})


