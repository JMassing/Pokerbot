function(add_gtest TEST_NAME SOURCE_FILE)
    set(TEST_EXECUTABLE ${TEST_NAME})
    add_executable(${TEST_EXECUTABLE} ${SOURCE_FILE})

    target_link_libraries(${TEST_EXECUTABLE} PRIVATE GTest::Main GTest::GTest)

endfunction()

add_gtest(TestPoker TestPoker.cpp)
add_gtest(TestDetect TestDetect.cpp)

target_link_libraries(TestPoker PRIVATE PokerbotLib)
target_link_libraries(TestDetect PRIVATE PokerbotLib)