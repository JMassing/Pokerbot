# add executables
file(GLOB SOURCES_POKER "src/*.cpp")

add_library(${POKERLIB_NAME} ${SOURCES_POKER} )

target_link_libraries( ${POKERLIB_NAME} ${DETECTIONLIB_NAME} ${SHAREDLIB_NAME})

target_include_directories( 
    ${POKERLIB_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/poker/include
    ${PROJECT_SOURCE_DIR}/poker/include/interfaces
)


