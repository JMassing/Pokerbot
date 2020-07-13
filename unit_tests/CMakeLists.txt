function(add_gtest TEST_NAME SOURCE_FILE)
    set(TEST_EXECUTABLE ${TEST_NAME})
    add_executable(${TEST_EXECUTABLE} ${SOURCE_FILE})

    target_link_libraries(${TEST_EXECUTABLE} PRIVATE ${CONAN_LIBS_GTEST})
endfunction()

add_gtest(TestPoker TestPoker.cpp)
add_gtest(TestDetect TestDetect.cpp)

target_link_libraries(TestPoker PRIVATE PokerbotLib ${CONAN_LIBS_BOOST})
target_link_libraries(TestDetect PRIVATE PokerbotLib ${CONAN_LIBS_OPENCV} ${CONAN_LIBS_ZLIB} ${CONAN_LIBS_BOOST})