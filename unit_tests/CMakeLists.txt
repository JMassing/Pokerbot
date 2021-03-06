function(add_gtest TEST_NAME SOURCE_FILE)
    set(TEST_EXECUTABLE ${TEST_NAME})
    add_executable(${TEST_EXECUTABLE} ${SOURCE_FILE})

    target_link_libraries(${TEST_EXECUTABLE} PRIVATE ${CONAN_LIBS_GTEST})
    target_link_libraries(${TEST_EXECUTABLE} INTERFACE ${TEMPLATELIB_NAME})
    add_test(NAME ${TEST_EXECUTABLE} COMMAND $<TARGET_FILE:${TEST_EXECUTABLE}>)
    target_compile_options(${TEST_NAME} PUBLIC ${TEST_FLAGS})
    
endfunction()

include_directories(
    ${PROJECT_SOURCE_DIR}/unit_tests/utilities/HelperFunctions
    ${PROJECT_SOURCE_DIR}/unit_tests/utilities/HelperClasses
)

# Test Flags
if(WIN32)
    set(TEST_FLAGS "/Od")
elseif(UNIX)
    set(TEST_FLAGS "-O0;-g")
endif()

add_gtest(TestCardBuffer TestCardBuffer.cpp)
add_gtest(TestDM TestDM.cpp)
add_gtest(TestCamController TestCamController.cpp)
add_gtest(TestPerspectiveCorrector TestPerspectiveCorrector.cpp)
add_gtest(TestCardDetector TestCardDetector.cpp)
add_gtest(TestHandDeckHandBuilder TestHandDeckHandBuilder.cpp)
add_gtest(TestPoker TestPoker.cpp)
add_gtest(TestGameSubClasses TestGameSubClasses.cpp)
add_gtest(TestGame TestGame.cpp)

target_link_libraries(TestPoker PRIVATE  ${POKERLIB_NAME} ${SHAREDLIB_NAME} ${CONAN_LIBS})
target_link_libraries(TestDM PRIVATE  ${POKERLIB_NAME} ${SHAREDLIB_NAME} ${CONAN_LIBS})
target_link_libraries(TestCardBuffer PRIVATE  ${POKERLIB_NAME} ${DETECTIONLIB_NAME} ${SHAREDLIB_NAME} ${CONAN_LIBS})
target_link_libraries(TestCamController PRIVATE ${CAPTURELIB_NAME} ${CONAN_LIBS})
target_link_libraries(TestPerspectiveCorrector PRIVATE ${DETECTIONLIB_NAME}  ${SHAREDLIB_NAME} ${CONAN_LIBS})
target_link_libraries(TestCardDetector PRIVATE ${DETECTIONLIB_NAME}  ${SHAREDLIB_NAME} ${CONAN_LIBS})
target_link_libraries(TestHandDeckHandBuilder PRIVATE  ${POKERLIB_NAME} ${SHAREDLIB_NAME} ${CONAN_LIBS})
target_link_libraries(TestGameSubClasses PRIVATE  ${POKERLIB_NAME} ${SHAREDLIB_NAME} ${CONAN_LIBS})
target_link_libraries(TestGame PRIVATE  ${POKERLIB_NAME} ${DETECTIONLIB_NAME} ${SHAREDLIB_NAME} ${CONAN_LIBS})


## Copy utilities to unit_tests folder
add_custom_command( 
    TARGET TestPoker POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/unit_tests/utilities/ $<TARGET_FILE_DIR:TestPoker>/unit_tests/utilities
)

if(ENABLE_CODE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(COVERAGE_MAIN "Code_Coverage")
        set(COVERAGE_LCOV_EXCLUDES
            "${PROJECT_SOURCE_DIR}/app/*"
            "${PROJECT_SOURCE_DIR}/external/*"
            "${PROJECT_SOURCE_DIR}/unit_tests/*"
            "${CONAN_GTEST_ROOT}/*"
            "${CONAN_BOOST_ROOT}/*"
            "${CONAN_OPENCV_ROOT}/*"
            "/usr/*"
            )        
        setup_target_for_coverage_lcov(
            NAME ${COVERAGE_MAIN}
            EXECUTABLE ctest
            DEPENDENCIES 
                TestPoker 
                TestCardBuffer 
                TestDM 
                TestCamController 
                TestPerspectiveCorrector
                TestCardDetector
                TestHandDeckHandBuilder
                TestGameSubClasses
                TestGame
            ) 
    endif()
endif()
