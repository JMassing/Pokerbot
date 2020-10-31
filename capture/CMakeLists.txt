# add executables
file(GLOB SOURCES_CAPTURE "src/*.cpp")

add_library( CaptureLib ${SOURCES_CAPTURE} )

target_link_libraries(CaptureLib SharedLib)

target_include_directories( 
    CaptureLib PUBLIC
    ${PROJECT_SOURCE_DIR}/capture/include
    ${PROJECT_SOURCE_DIR}/capture/include/interfaces
    )

