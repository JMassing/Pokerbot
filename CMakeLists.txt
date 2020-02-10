cmake_minimum_required(VERSION 3.10)


project(Pokerbot VERSION 0.1.0)


set(OpenCV_DIR "C:/Users/julim/Desktop/vs_dev_lib/opencv/build/include")
set(Boost_DIR "C:/Users/julim/Desktop/vs_dev_lib/boost_1_72_0")
set(OpenCV_LIBS "C:/Users/julim/Desktop/vs_dev_lib/opencv/build/x64/vc14/lib/opencv_world420d.lib")

# Bring all headers into the project
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_DIR}
    ${Boost_DIR}
    )

# add executables
file(GLOB SOURCES "src/*.cpp")
add_executable(Pokerbot main.cpp ${SOURCES})

target_link_libraries(Pokerbot ${OpenCV_LIBS})
link_libraries(${OpenCV_LIBS})



