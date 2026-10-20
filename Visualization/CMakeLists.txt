add_library(Visualization
    Visualization.cpp
)

target_include_directories(Visualization
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(Visualization PUBLIC cxx_std_20)