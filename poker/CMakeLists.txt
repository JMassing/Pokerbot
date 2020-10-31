# add executables
file(GLOB SOURCES_POKER "src/*.cpp")

add_library( PokerLib ${SOURCES_POKER} )

target_link_libraries(PokerLib DetectionLib SharedLib)

target_include_directories( PokerLib PUBLIC
    ${PROJECT_SOURCE_DIR}/poker/include
    ${PROJECT_SOURCE_DIR}/poker/include/interfaces
)


