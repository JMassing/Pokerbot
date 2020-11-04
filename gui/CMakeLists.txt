# add executables
file(GLOB SOURCES_GUI "src/*.cpp")
file(GLOB SOURCES_WIDGETS "src/widgets/*.cpp")
file(GLOB SOURCES_INTERFACES "src/interfaces/*.cpp")
file(GLOB SOURCES_WINDOWS "src/windows/*.cpp")

## add imgui

find_package( Git )
execute_process(
  COMMAND ${GIT_EXECUTABLE} clone "https://github.com/ocornut/imgui.git" -b v1.72b
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
set( IMGUI_DIR ${PROJECT_BINARY_DIR}/imgui )

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

add_library( GuiLib 
${SOURCES_GUI}
${SOURCES_WIDGETS}
${SOURCES_INTERFACES}
${SOURCES_WINDOWS}
${imgui_files} ${imgui_impl_files} ${gl3w}
)

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
set( GLFW_LIBRARIES X11 Xrandr Xi Xxf86vm GLEW::GLEW ${GLFW_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX} )

target_link_libraries( 
    GuiLib 
    DetectionLib 
    PokerLib
    CaptureLib
    ${GLFW_LIBRARIES} 
    ${OPENGL_LIBRARIES} 
    )

target_include_directories(
    GuiLib PUBLIC 
    ${PROJECT_SOURCE_DIR}/gui/include
    ${PROJECT_SOURCE_DIR}/gui/include/widgets
    ${PROJECT_SOURCE_DIR}/gui/include/windows
    ${PROJECT_SOURCE_DIR}/gui/include/interfaces
    ${IMGUI_DIR} 
    ${IMGUI_DIR}/examples 
    ${IMGUI_DIR}/examples/libs/gl3w
    ${GLFW_INCLUDE_DIR}
    ${GLFW_LIBRARIES}
    )



