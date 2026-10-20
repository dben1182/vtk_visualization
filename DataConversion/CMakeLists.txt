add_library(DataConversion
    DataConversion.cpp
)

target_include_directories(DataConversion
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(DataConversion PUBLIC cxx_std_20)

