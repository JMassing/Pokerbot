# add executables
file(GLOB SOURCES_DETECTION "src/*.cpp")

add_library( DetectionLib ${SOURCES_DETECTION} )

target_include_directories( DetectionLib PUBLIC
${PROJECT_SOURCE_DIR}/detection/include
${PROJECT_SOURCE_DIR}/detection/include/interfaces
)

target_link_libraries(DetectionLib PokerLib SharedLib)


