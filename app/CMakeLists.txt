## Executable
add_executable(Pokerbot src/main.cpp)

target_link_libraries(
  Pokerbot  
  ${DETECTIONLIB_NAME} 
  ${SHAREDLIB_NAME} 
  ${CAPTURELIB_NAME}
  ${GUILIB_NAME} 
  ${POKERLIB_NAME} 
  ${CONAN_LIBS}
  )

  target_include_directories( 
    Pokerbot PUBLIC  ${PROJECT_SOURCE_DIR}/app/include
  )