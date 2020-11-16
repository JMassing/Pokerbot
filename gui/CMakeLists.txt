# add executables
file(GLOB SOURCES_GUI "src/*.cpp")
file(GLOB SOURCES_WIDGETS "src/widgets/*.cpp")
file(GLOB SOURCES_INTERFACES "src/interfaces/*.cpp")
file(GLOB SOURCES_WINDOWS "src/windows/*.cpp")

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

add_library(
  ${GUILIB_NAME}  
  ${SOURCES_GUI}
  ${SOURCES_WIDGETS}
  ${SOURCES_INTERFACES}
  ${SOURCES_WINDOWS}
  ${imgui_files} ${imgui_impl_files} ${gl3w}
)

## add GLFW

if(WIN32)

  # include( ExternalProject )
  # ExternalProject_Add(
  # glfw PREFIX glfw
  # GIT_REPOSITORY https://github.com/glfw/glfw.git
  # GIT_TAG 3.3
  # CMAKE_ARGS
  #   "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
  #   "-DCMAKE_BUILD_TYPE=Release"
  #   "-DGLFW_BUILD_DOCS=OFF"
  #   "-DGLFW_BUILD_EXAMPLES=OFF"
  #   "-DGLFW_BUILD_TESTS=OFF"
  # )
  # ExternalProject_Get_Property( glfw INSTALL_DIR )
  # set( GLFW_DIR ${INSTALL_DIR} )
  # set( GLFW_INCLUDE_DIR ${GLFW_DIR}/include )
  # set( GLFW_LIBRARIES ${GLFW_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX} )

  target_link_libraries( 
      ${GUILIB_NAME} PUBLIC 
      ${DETECTIONLIB_NAME}  
      ${POKERLIB_NAME} 
      ${CAPTURELIB_NAME}
      ${GLFW_LIBRARIES} 
      ${OPENGL_LIBRARIES} 
      ${GLFWLIB_NAME}
      )

  target_include_directories(
    ${GUILIB_NAME} PUBLIC 
      ${PROJECT_SOURCE_DIR}/gui/include
      ${PROJECT_SOURCE_DIR}/gui/include/widgets
      ${PROJECT_SOURCE_DIR}/gui/include/windows
      ${PROJECT_SOURCE_DIR}/gui/include/interfaces
      ${IMGUI_DIR} 
      ${IMGUI_DIR}/examples 
      ${IMGUI_DIR}/examples/libs/gl3w
      )    

ELSE()
## find GLFW3
find_package( glfw3 3.3 REQUIRED )

target_link_libraries( 
    ${GUILIB_NAME} PUBLIC
    ${DETECTIONLIB_NAME}  
    ${POKERLIB_NAME} 
    ${CAPTURELIB_NAME}
    glfw
    ${OPENGL_LIBRARIES} 
    )

target_include_directories(
    ${GUILIB_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/gui/include
    ${PROJECT_SOURCE_DIR}/gui/include/widgets
    ${PROJECT_SOURCE_DIR}/gui/include/windows
    ${PROJECT_SOURCE_DIR}/gui/include/interfaces
    ${IMGUI_DIR} 
    ${IMGUI_DIR}/examples 
    ${IMGUI_DIR}/examples/libs/gl3w
    )

ENDIF()



