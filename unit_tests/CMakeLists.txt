function(add_gtest TEST_NAME SOURCE_FILE)
    set(TEST_EXECUTABLE ${TEST_NAME})
    add_executable(${TEST_EXECUTABLE} ${SOURCE_FILE})

    target_link_libraries(${TEST_EXECUTABLE} PRIVATE ${CONAN_LIBS_GTEST})
    add_test(NAME ${TEST_EXECUTABLE} COMMAND $<TARGET_FILE:${TEST_EXECUTABLE}>)
    
endfunction()



include_directories(
    ${PROJECT_SOURCE_DIR}/unit_tests/utilities/HelperFunctions
)

add_gtest(TestPoker TestPoker.cpp)
add_gtest(TestDetect TestDetect.cpp)
add_gtest(TestDM TestDM.cpp)


target_link_libraries(TestPoker PRIVATE PokerLib SharedLib ${CONAN_LIBS_BOOST})
target_link_libraries(TestDM PRIVATE PokerLib SharedLib ${CONAN_LIBS_BOOST})
target_link_libraries(TestDetect PRIVATE PokerLib DetectionLib SharedLib ${CONAN_LIBS_OPENCV} ${CONAN_LIBS_ZLIB} ${CONAN_LIBS_BOOST})