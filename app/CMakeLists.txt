## Executable
add_executable(Pokerbot src/main.cpp)

target_link_libraries(
  Pokerbot  
  DetectionLib 
  SharedLib 
  CaptureLib 
  GuiLib 
  PokerLib 
  ${CONAN_LIBS}
  )

  target_include_directories( 
    Pokerbot PUBLIC  ${PROJECT_SOURCE_DIR}/app/include
  )