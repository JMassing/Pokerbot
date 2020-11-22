# add executables
file(GLOB SOURCES_SHARED "src/*.cpp")

add_library( ${SHAREDLIB_NAME} ${SOURCES_SHARED} )

target_include_directories( 
    ${SHAREDLIB_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/shared/include
    )


