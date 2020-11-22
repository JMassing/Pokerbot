# add executables
file(GLOB SOURCES_DETECTION "src/*.cpp")

add_library( ${DETECTIONLIB_NAME} ${SOURCES_DETECTION} )

target_include_directories(   
    ${DETECTIONLIB_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/detection/include
    ${PROJECT_SOURCE_DIR}/detection/include/interfaces
)

target_link_libraries(
    ${DETECTIONLIB_NAME} PUBLIC
    ${POKERLIB_NAME} 
    ${SHAREDLIB_NAME} 
    )


