include(GoogleTest)

add_library(TestData
    testData.cpp
)

target_include_directories(TestData
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(TestData PUBLIC cxx_std_20)

target_link_libraries(TestData
    PUBLIC
        DataConversion
)

add_executable(DataConversion_unittests)
target_sources(DataConversion_unittests
    PRIVATE
        DataConversion_unittests.cpp
)
target_compile_features(DataConversion_unittests PRIVATE cxx_std_20)
target_include_directories(DataConversion_unittests
    PRIVATE
        "${GTEST_INCLUDE_DIRS}"
)
target_link_libraries(DataConversion_unittests
    GTest::gtest_main
    DataConversion
    TestData
)

gtest_discover_tests(DataConversion_unittests)
