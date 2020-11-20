# add executables
file(GLOB SOURCES_GUI "src/*.cpp")
file(GLOB SOURCES_WIDGETS "src/widgets/*.cpp")
file(GLOB SOURCES_INTERFACES "src/interfaces/*.cpp")
file(GLOB SOURCES_WINDOWS "src/windows/*.cpp")

## Add ImGui files from Submodule 
## ImGui is designed to be compiled together with you application and not as a seperate library
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/external/imgui )

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
  ${IMGUI_DIR}/backends/imgui_impl_glfw.h
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.h
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set(gl3w ${IMGUI_DIR}/examples/libs/gl3w/GL/gl3w.c)

# add GuiLib

add_library(
  ${GUILIB_NAME}  
  ${SOURCES_GUI}
  ${SOURCES_WIDGETS}
  ${SOURCES_INTERFACES}
  ${SOURCES_WINDOWS}
  ${imgui_files} ${imgui_impl_files} ${gl3w}
)

if(WIN32)

  target_link_libraries( 
      ${GUILIB_NAME} PUBLIC 
      ${DETECTIONLIB_NAME}  
      ${POKERLIB_NAME} 
      ${CAPTURELIB_NAME}
      ${OPENGL_LIBRARIES} 
      ${GLFWLIB_NAME}
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
    GLEW::GLEW
    )

ENDIF()

target_include_directories(
    ${GUILIB_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/gui/include
    ${PROJECT_SOURCE_DIR}/gui/include/widgets
    ${PROJECT_SOURCE_DIR}/gui/include/windows
    ${PROJECT_SOURCE_DIR}/gui/include/interfaces
    ${IMGUI_DIR} 
    ${IMGUI_DIR}/backends 
    ${IMGUI_DIR}/examples/libs/gl3w
    )    

