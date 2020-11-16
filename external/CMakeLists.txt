## add imgui

find_package( Git )
execute_process(
  COMMAND ${GIT_EXECUTABLE} clone "https://github.com/ocornut/imgui.git" -b v1.72b
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/imgui
)

add_subdirectory(glfw)
add_library(${GLFWLIB_NAME} ALIAS celero)

