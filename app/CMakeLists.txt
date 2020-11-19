## Executable
add_executable(Pokerbot src/main.cpp)

target_link_libraries(
  Pokerbot  PUBLIC
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

  ## Copy necessary config files to build directory for Pokerbot
  ## Train Images
  add_custom_command( 
    TARGET Pokerbot POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Card_Imgs/ $<TARGET_FILE_DIR:Pokerbot>/../Card_Imgs
    )
    
  # config.ini
  if(WIN32)
    set(CONFIG_FILE config_windows.ini)
  else()
    set(CONFIG_FILE config_linux.ini)
  endif()

  add_custom_command( 
    TARGET Pokerbot POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/app/${CONFIG_FILE} $<TARGET_FILE_DIR:Pokerbot>/../config.ini
    ) 
  
  # imgui.ini
  add_custom_command( 
    TARGET Pokerbot POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/app/imgui.ini $<TARGET_FILE_DIR:Pokerbot>/imgui.ini
    ) 