# add executables
file(GLOB SOURCES_CAPTURE "src/*.cpp")

add_library( ${CAPTURELIB_NAME} ${SOURCES_CAPTURE} )

target_link_libraries(${CAPTURELIB_NAME} ${SHAREDLIB_NAME})

target_include_directories( 
    ${CAPTURELIB_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/capture/include
    ${PROJECT_SOURCE_DIR}/capture/include/interfaces
    )

