include(GoogleTest)

add_executable(DataConversion_unittests)
target_sources(DataConversion_unittests
    PRIVATE
        DataGenerator_unittests.cpp
)
target_compile_features(DataConversion_unittests PRIVATE cxx_std_20)
target_include_directories(DataConversion_unittests
    PRIVATE
        "${GTEST_INCLUDE_DIRS}"
)
target_link_libraries(DataConversion_unittests
    GTest::gtest_main
    DataConversion
)

