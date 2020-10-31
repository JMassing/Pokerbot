# add executables
file(GLOB SOURCES_SHARED "src/*.cpp")

add_library( SharedLib ${SOURCES_SHARED} )

target_include_directories( 
    SharedLib PUBLIC
    ${PROJECT_SOURCE_DIR}/shared/include
    )


